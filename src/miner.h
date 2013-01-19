#ifndef MINER_H
#define MINER_H

#include <string>
#include <sstream>

#include "annoyed_npc.h"
#include "solar_system.h"

using namespace std;

namespace rpg {

class solar_system;

class miner : public annoyed_npc {

public:
	miner(string name, string desc);

	static miner* from_ptree(game *g, boost::property_tree::ptree tree);
};
};

#endif
