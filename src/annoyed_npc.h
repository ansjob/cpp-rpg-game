#ifndef ANNOYED_NPC_H
#define ANNOYED_NPC_H

#include <string>
#include <sstream>

#include "npc.h"
#include "solar_system.h"

using namespace std;

namespace rpg {

class solar_system;

class annoyed_npc : public npc {

public:
	annoyed_npc(string name, string desc);

	/** Returns a taunt at the player. */
	virtual string talk();

	static annoyed_npc * from_ptree (game *, boost::property_tree::ptree);
};
};

#endif
