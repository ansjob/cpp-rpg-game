#include <boost/property_tree/ptree.hpp>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>

#include "utils.h"
#include "actor.h"
#include "adverb.h"
#include "initializers.h"
#include "utils.h"
#include "weapon.h"
#include "solar_system.h"

using namespace std;
using boost::property_tree::ptree;
using boost::optional;

namespace rpg {

extern initializer initializers;

actor::actor(string name, string desc):
	game_object(name, desc),
	m_hp(max_hp()),
	cur_weapon(NULL),
	cur_shield(NULL),
	selling(false),
	credits(0)
	{}

solar_system & actor::location() {
	return *((solar_system*)parent);
};

void actor::move_to(solar_system &dest) {

	/* Remove from current location, if any */
	remove();

	/* Move to new location */
	string lower_name = utils::tolower(m_name);
	dest.actors[lower_name] = this;
	game_object::move_to(dest);
}

void actor::remove() {
	/* Don't remove if we don't have a parent */
	if (parent == NULL)
		return;

	solar_system *paren = dynamic_cast<solar_system*>(parent);
	if (paren != NULL) {

		/* Remove from actors map */
		string lower_name = utils::tolower(m_name);
		solar_system *cur = &location();
		auto it = cur->actors.find(lower_name);
		assert(it != cur->actors.end());
		cur->actors.erase(it);

	}

	/* Remove as usual */
	game_object::remove();
}

string actor::talk() {
	stringstream ss;
	ss << name() << ": Hi, my name is " << m_name << ".";
	return ss.str();
}

int actor::hp() const {
	return m_hp;
}

int actor::shield_hp() const {
	if (cur_shield == NULL)
		return 0;
	return cur_shield->hp();
}

int actor::max_hp() const {
	return 100;
}

int actor::max_shield() const {
	if (cur_shield == NULL)
		return 0;
	return cur_shield->max();
}

int actor::max_cargo() const {
	return 1000;
}

weapon * actor::current_weapon() const {
	return cur_weapon;
}

shield * actor::current_shield() const {
	return cur_shield;
}

void actor::set_shield(shield* s) {
	cur_shield = s;
}

int actor::avail_cargo() const {
	int max = max_cargo();
	for (auto item_pair : items()) {
		max -= item_pair.second->volume();
	}
	return max;
};

void actor::set_weapon(weapon* w) {
	cur_weapon = w;
}

void actor::take_damage(ostream& os, actor * attacker, int damage) {

	/* Do nothing if it's a miss */
	if (damage == 0) {
		return;
	}

	/* Deplete shield first */
	if (shield_hp() > 0) {
		cur_shield->take_damage(os, damage);
		return;
	}

	/* Do hull damage */
	int hull_damage = min(damage, hp());
	m_hp -= hull_damage;
	os << "Hull " << random_adverb() << " suffers " << hull_damage << " damage." << endl;

	/* Kill actor if it became dead */
	if (hp() == 0) {
		die(os);
	}
}

void actor::die(ostream &os) {
	os << name() << " destroyed." << endl;

	/* Drop equipped items */
	solar_system &loc = location();
	drop_shield();
	drop_weapon();

	/* Drop items */
	vector<item*> move_us;
	for (pair<string, item*> child : items()) {
		move_us.push_back(child.second);
	}
	for (item* itm : move_us)
		itm->move_to(loc);
	assert(items().size() == 0);
	game_object * tmp_parent = parent;
	remove();
	parent = tmp_parent; //This is pure evil!
	tmp_parent->children.insert(this);
}

void actor::attack(ostream& os, actor * target) {
	if (cur_weapon == NULL) {
		/* Print a nice error message */
		os << name() << " " << random_adverb()
			<< " tried to attack, but had no weapon equipped." << endl;
	}
	else {
		/* Make the weapon attack the target */
		cur_weapon->attack(os, target);

		/* Call the solar system hook */
		location().on_actor_attacked(os, this, target);
	}
};

int actor::buy(ostream& os, actor * buyer, unsigned int item_no) {
	assert(selling);
	if (item_no >= items().size()) {
		os << name() << ": 'I have no item by that number!'" << endl;
		return 0;
	}
	auto it = items().begin();
	advance(it, item_no);
	item *thing = it->second;
	if (buyer->credits < thing->value()) {
		os << name() << " (" << random_adverb()
			<< "): 'Sorry, you cannot afford that!'" << endl;
		return 0;
	};
	buyer->credits -= thing->value();
	thing->move_to((solar_system&)*parent);
	thing->move_to(*buyer);
	os << "You " << random_adverb() << " bought "
		<< thing->name() << " for only " << thing->value() << " credits." << endl;
	return 1;
};

void actor::drop_shield() {
	if (cur_shield == NULL) return;
	cur_shield->unequip();
	items().insert(make_pair(utils::tolower(cur_shield->name()), cur_shield));
	cur_shield->move_to(location());
}

void actor::drop_weapon() {
	if (cur_weapon == NULL) return;
	items().insert(make_pair(utils::tolower(cur_weapon->name()), cur_weapon));
	cur_weapon->move_to(location());
}

void actor::delete_weapon() {
	if (cur_weapon == NULL) return;
	for (auto it = children.begin(); it != children.end(); ++it) {
		if (*it == cur_weapon){
			children.erase(it);
			break;
		}
	}
	delete cur_weapon;
	cur_weapon = NULL;
}

multimap<string, item*> & actor::items() {
	return m_items;
}

const multimap<string, item*> & actor::items() const {
	return m_items;
}

boost::property_tree::ptree actor::to_ptree() const {
	ptree pt = game_object::to_ptree();
	pt.put("hp", m_hp);
	pt.put("selling", selling);
	pt.put("credits", credits);
	if (cur_weapon != NULL) {
		pt.put("weapon", (unsigned long)cur_weapon);
	}
	if (cur_shield != NULL) {
		pt.put("shield", (unsigned long)cur_shield);
	}

	return pt;
} 

void actor::init(game* g, ptree tree) {

	game_object::init(g, tree);

	credits = tree.get<int>("credits");
	m_hp = tree.get<int>("hp");
	selling = tree.get<bool>("selling");

	/* Generate item map */
	for (game_object *child : children) {
		item * itm = dynamic_cast<item*>(child);
		if (itm != NULL) {
			m_items.insert({
				utils::tolower(itm->name()),
				itm
			});
		}
	}

	auto wco = tree.get_optional<unsigned long>("weapon");
	if (wco) {
		for (auto child : children) {
			if (child->id == *wco) {
				cur_weapon = dynamic_cast<weapon*>(child);
				auto it = items().begin();
				for (; it != items().end(); ++it) {
					if (it->second->id == child->id) {
						items().erase(it);
						break;
					}
				}
				assert(it != items().end());
			}
		}
	}

	auto shield_opt = tree.get_optional<unsigned long>("shield");
 
	if (shield_opt) {
		for (auto child : children) {
			if (child->id == *shield_opt) {
				cur_shield = dynamic_cast<shield*>(child);
				auto it = items().begin();
				for (; it != items().end(); ++it) {
					if (it->second->id == child->id) {
						items().erase(it);
						break;
					}
				}
				assert(it != items().end());
			}
		}
	}
};

void actor::after_tick(ostream &os) {
	/* Delete us if dead */
	if (m_hp == 0) {
		for (auto it = parent->children.begin(); it != parent->children.end(); ++it) {
			if (*it == this) {
				parent->children.erase(it);
				break;
			}
		}
		delete this;
	}
}

};


