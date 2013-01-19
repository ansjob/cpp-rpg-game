#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "item.h"
#include "shield.h"
#include "weapon.h"
#include "hunter.h"
#include "initializers.h"
#include "utils.h"

using namespace std;

namespace rpg {

extern initializer initializers;

void hunter::setup() {
/*
	shield * cur_shield = new shield("Light Hunter Shield",
		"A basic shield that offers low protection but quick regeneration, making it ideal for the agile requirements of space hunters.",
		10, 3000, 1, 100, 300);
	stringstream dummy;
	cur_shield->move_to(*this);
	cur_shield->use(dummy, this);

	weapon * cur_weap = new weapon("Hunter Ion Beam",
		"A reliable Ion Beam designed to bring quick and certain destruction to the hunter's foe. ",
		10, 2500, 85, 100, 0.95);

	cur_weap->move_to(*this);
	cur_weap->use(dummy, this);
*/

	selling = false;
}

hunter::hunter(string name, string desc, actor * target) : npc(name, desc) {
	setup();
	if (target != NULL) {
		hostile_map[target->name()] = true;
	}
};

hunter::hunter(string name, string desc, string target) : npc(name, desc) {
	setup();
	hostile_map[target] = true;
};

string hunter::talk() {
	stringstream os;
	os << name() << ": You ugly dog!\n";
	return os.str();
};

void hunter::tick(ostream &os) {
	game_object * before = parent;

	/* Do basic NPC stuff */
	npc::tick(os);

	if (m_hp == 0) return;

	bool moved = parent != before;

	/* Try to pick up a weapon if there is one in the current location */
	weapon * local_weapon = NULL;
	for (auto it = location().items().begin(); it != location().items().end(); ++it) {
		local_weapon = dynamic_cast<weapon*>(it->second);
		
		if (local_weapon != NULL) {
			location().echo << name() << " found " << local_weapon->name() << endl;
			local_weapon->move_to(*this);
			stringstream dummy;
			local_weapon->use(dummy, this);
			return;
		}
	}

	/* Hunters with no weapons sit and wait for someone to drop one */
	if (current_weapon() == NULL || moved) return;

	/* Do not pursue sometimes */
	if (random() % 100 < 25) return;

	for (pair<string, solar_system*> loc_entry : location().neighbours) {
		for (pair<string, actor*> actor_entry : loc_entry.second->actors) {
			if (hostile_against(actor_entry.second)) {
				move_to(*(loc_entry.second));
				loc_entry.second->echo << name() << " entered." << endl;
				return;
			}
		}
	}
};

game_object * hunter::from_ptree(game *g, boost::property_tree::ptree tree) {
	using boost::property_tree::ptree;

	hunter *actor = new hunter(tree.get<string>("name"), tree.get<string>("m_desc"), NULL);
	actor->init(g, tree);
	return actor;
}

};

