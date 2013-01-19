#include <string>
#include <sstream>
#include <iomanip>

#include "actor.h"
#include "utils.h"
#include "weapon.h"
#include "adverb.h"
#include "initializers.h"
#include "solar_system.h"

using namespace std;

namespace rpg {

extern initializer initializers;

void weapon::use(ostream& os, actor* a) {
	weapon * equipped = a->current_weapon();
	if (equipped != NULL) {
		int e_v = equipped->volume();
		if (e_v > a->avail_cargo() + this->volume()) {
			os << "There is not enough room in your cargo to make the weapon swap." << endl;
			return;
		}
		else {
			a->items().insert(make_pair(utils::tolower(equipped->name()), equipped));
			a->set_weapon(NULL);
		}
	}
	a->set_weapon(this);
	for (auto it = a->items().begin(); it != a->items().end(); ++it) {
		if (it->second == this) {
			a->items().erase(it);
			break;
		}
	}
	os << "Equipped " << name() << " " << random_adverb() << endl; 
}; 

void weapon::attack(ostream& os, actor* target) {
	os << parent->name() << " " << random_adverb() << " fired " << name() << " at " << target->name() << "!" << endl;
	if ((double(random()) / RAND_MAX) <= accuracy()) {
		os << "It's a hit!" << endl;
		int damage = min_damage() + (random() % (1 + max_damage() - min_damage()));
		target->take_damage(os, (actor *)parent, damage);
	}
	else {
		os << "It's a miss!" << endl;
		target->take_damage(os, (actor *)parent, 0);
	}
};

int weapon::min_damage() const {
	return m_min_damage;
}

int weapon::max_damage() const {
	return m_max_damage;
}

double weapon::accuracy() const {
	return m_accuracy;
}

string weapon::desc() const {
	stringstream ss;

	ss << m_desc << "\n";
	ss << "Properties:\n";

	ss << "\tDamage: " << m_min_damage << "-" << m_max_damage << "\n";
	ss << "\tAccuracy: " << fixed << setprecision(1) << (100.0 * m_accuracy) << "%\n";

	return ss.str();
}

item * weapon::copy() const {
	item *p = new weapon(*this);
	return p;
}

using boost::property_tree::ptree;

ptree weapon::to_ptree() const {
	using boost::property_tree::ptree;
	ptree pt = item::to_ptree();

	pt.put("m_accuracy", m_accuracy);
	pt.put("m_min_damage", m_min_damage);
	pt.put("m_max_damage", m_max_damage);

	return pt;
};

weapon * weapon::from_ptree(game * g, ptree tree) {

	weapon * w = new weapon;

	w->init(g, tree);

	return w;
}

void weapon::init(game * g, ptree tree) {
	item::init(g, tree);

	m_accuracy = tree.get<double>("m_accuracy");
	m_min_damage = tree.get<int>("m_min_damage");
	m_max_damage = tree.get<int>("m_max_damage");

}

};
