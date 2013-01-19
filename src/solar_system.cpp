#include "actor.h"
#include "adverb.h"
#include "weapon.h"
#include "shield.h"
#include "solar_system.h"
#include "initializers.h"
#include "consumable_item.h"
#include "utils.h"

using namespace std;

namespace rpg {

extern initializer initializers;

solar_system::solar_system(string n, string d) : game_object(n, d) {}

bool solar_system::accepts(player& player) {
	return true;
}

void solar_system::print_deny_message(ostream& os) {
	os << "One does not " << random_adverb() << "go into " << m_name << " just yet." << endl;
}

void solar_system::print_enter_message(ostream& os) {
	os << "You " << random_adverb() << " enter " << m_name << endl;
}

void solar_system::tick(ostream &os) {
	/* Clear the echo of this turn */
	echo.str("");
}

void solar_system::on_actor_attacked(ostream &os, actor *attacker, actor *victim) {
	/* Do nothing for base implementation of solar system */
	return;
}

multimap<string, item*> & solar_system::items() {
	return m_items;
}

const multimap<string, item*> & solar_system::items() const {
	return m_items;
}

game_object * solar_system::from_ptree(game *g, boost::property_tree::ptree tree) {
	using boost::property_tree::ptree;

	string name = tree.get<string>("name");
	/* Find the name and construct solar system */
	solar_system * sys = new solar_system(name);
	sys->init(g,tree);
	return sys;
};

boost::property_tree::ptree solar_system::to_ptree() const {

	using boost::property_tree::ptree;

	ptree my_tree = game_object::to_ptree();

	ptree neighbour_tree;

	for ( pair<string, solar_system*> neighbour : neighbours) {
		ptree entry;
		entry.add("direction", neighbour.first);
		entry.add("system-name", neighbour.second->name());
		neighbour_tree.add_child("neighbour", entry);
	}

	my_tree.add_child("neighbours", neighbour_tree);

	return my_tree;

};

void solar_system::init(game * g, boost::property_tree::ptree tree) {
	game_object::init(g, tree);

	/* Initializing actors/items maps! */
	for (game_object * child : children) {
		actor * a = dynamic_cast<actor*>(child);
		if (a != NULL) {
			actors.insert({
				utils::tolower(a->name()),
				a
			});
		} else {
			item * itm = dynamic_cast<item*>(child);
			if (itm != NULL) {
				m_items.insert( {
					utils::tolower(itm->name()),
					itm
				});
			}
		}
	}
}

};
