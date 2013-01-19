#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "shield.h"
#include "weapon.h"
#include "miner.h"

using namespace std;

namespace rpg {

miner::miner(string name, string desc) : annoyed_npc(name, desc) {
/*
	shield * cur_shield = new shield("Ultrasonic Buffer",
		"A basic shield used by miners to protect them from Sonic the Hedgehog",
		50, 400, 5, 10, 35);
	stringstream dummy;
	cur_shield->move_to(*this);
	cur_shield->use(dummy, this);

	weapon * cur_weap = new weapon("Mining Laser",
		"A Laser used by miners to blast holes in mountains.",
		400, 300, 3, 7, 0.5);

	cur_weap->move_to(*this);
	cur_weap->use(dummy, this);
*/

};

miner * miner::from_ptree(game *g, boost::property_tree::ptree tree) {
	using boost::property_tree::ptree;

	miner *actor = new miner(tree.get<string>("name"), tree.get<string>("m_desc"));
	actor->init(g, tree);
	return actor;
}



};

