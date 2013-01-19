#ifndef POLICE_H
#define POLICE_H

#include <string>
#include <sstream>

#include "npc.h"
#include "sanctuary_system.h"

using namespace std;

namespace rpg {

class police : public npc {

protected:
	sanctuary_system * patrol_system;

public:
	police(string name, string desc, sanctuary_system *patrol_system);
	police(string name, string desc);

	virtual void tick(ostream &os);
	virtual void die(ostream &os);
	virtual string talk();

	/** Construct from ptree */
	static game_object * from_ptree(game *g, boost::property_tree::ptree tree);
};
};

#endif
