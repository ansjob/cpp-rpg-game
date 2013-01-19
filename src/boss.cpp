#include <string>
#include <sstream>
#include <iostream>

#include "shield.h"
#include "weapon.h"
#include "boss.h"
#include "player.h"
#include "mayor.h"
#include "adverb.h"
#include "initializers.h"
#include "annoyed_npc.h"

using namespace std;

namespace rpg {

extern initializer initializers;

boss::boss(string name, string desc) : hunter(name, desc, NULL) {

/*
	shield * cur_shield = new shield("Gangster Shield Generator",
		"A powerful shield used by gangster vessels",
		500, 4000, 1, 40, 200);
	stringstream dummy;
	cur_shield->move_to(*this);
	cur_shield->use(dummy, this);

	stringstream laser_desc;
	laser_desc << "A powerful Laser custom made for " << name;
	weapon * cur_weap = new weapon("Tommygun Laser",
		laser_desc.str(),
		350, 5000, 40, 100, 0.9);

	cur_weap->move_to(*this);
	cur_weap->use(dummy, this);
*/

};

void boss::die(ostream& os) {
	os << name() << "'s ship starts to tear apart, and you see a small escape pod " 
	<< "launch from the vessel just before it explodes. Over the radio you hear:\n" 
	<< name() << " (" << random_adverb() << "): You win this time! But i'll be back!" << endl;

	/* Find and "drop" mayor Paine */
	for (game_object * child : children) {
		mayor *p = dynamic_cast<mayor*>(child);
		if (p != NULL) {
			p->move_to(location());
			break;
		}
	}

	hunter::die(os);
};

int boss::max_hp() const {
	return 250;
}

string boss::talk() {
	player * p;
	for (pair<string, actor*> pr : location().actors) {
		actor * intruder = pr.second;
		p = dynamic_cast<player*>(intruder);
		if (p != NULL) {
			make_hostile_against(p);
			break;
		}
	}
	assert(p != NULL);
	return "I will eat you alive!!!";
}

game_object * boss::from_ptree(game *g, boost::property_tree::ptree tree) {
	using boost::property_tree::ptree;

	boss *actor = new boss(tree.get<string>("name"), tree.get<string>("m_desc"));
	actor->init(g, tree);
	return actor;
}

};

