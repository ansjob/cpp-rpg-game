#ifndef HUNTER_H
#define HUNTER_H

#include <string>
#include <sstream>

#include "npc.h"
#include "solar_system.h"

using namespace std;

namespace rpg {

class solar_system;

class hunter : public npc {

private:
	/** Private initialization function */
	void setup();

public:
	hunter(string name, string desc, actor * target);
	hunter(string name, string desc, string target);

	/** If the player was in the system, the hunter will follow him/her with 
	 * a certain probability. */
	virtual void tick(ostream &os);

	/** Returns a taunt at the player. */
	virtual string talk();

	/** Construct from ptree */
	static game_object * from_ptree(game *g, boost::property_tree::ptree tree);
};
};

#endif
