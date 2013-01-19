#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "utils.h"
#include "police.h"
#include "shield.h"
#include "weapon.h"
#include "initializers.h"

using namespace std;

namespace rpg {

extern initializer initializers;

police::police(string name, string desc, sanctuary_system *patrol_sys) : npc(name, desc), patrol_system(patrol_sys) {
	stringstream dummy;

	/* Equip actor */
	shield * cur_shield = new shield("Light Police Shield",
		"A basic shield that offers low protection but quick regeneration, making it ideal for the agile requirements of space polices.",
		10, 3000, 1, 100, 300);
	cur_shield->move_to(*this);
	cur_shield->use(dummy, this);

	weapon * cur_weap = new weapon("Police Ion Beam",
		"A reliable Ion Beam designed to bring quick and certain destruction to the police's foe. ",
		10, 2500, 85, 100, 0.95);
	cur_weap->move_to(*this);
	cur_weap->use(dummy, this);

	/* Police patrols are not merchants */
	selling = false;

	/* Add police unit to its patrol system if specified */
	if (patrol_system != NULL) {
		patrol_system->add_patrol(this);
	}
};

police::police(string name, string desc) : npc(name, desc) {
	/* Police patrols are not merchants */
	selling = false;
}

void police::die(ostream &os) {
	/* Remove police unit from patrol duty */
	if (patrol_system != NULL) {
		patrol_system->remove_patrol(this);
	}

	/* Die as usual */
	npc::die(os);
}

string police::talk() {
	stringstream os;
	os << name() << ": No problems here!\n";
	return os.str();
};

void police::tick(ostream &os) {
	/* Act as a regular NPC */
	npc::tick(os);
}

game_object * police::from_ptree(game *g, boost::property_tree::ptree tree) {
	using boost::property_tree::ptree;

	string name = tree.get<string>("name");
	string desc = tree.get<string>("m_desc");
	police *actor = new police(name, desc, NULL);
	actor->init(g, tree);
	return actor;
}



};

