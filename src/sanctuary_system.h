#ifndef SANCTUARY_SYSTEM_H
#define SANCTUARY_SYSTEM_H

#include <set>
#include <string>
#include <iostream>

#include "solar_system.h"

using namespace std;

namespace rpg {

class actor;
class police;

class sanctuary_system : public solar_system {
protected:
	set<actor *>	patrols;

public:
	sanctuary_system(string n, string d); 

	virtual void tick(ostream &os);

	/** Add a given police unit to the patroller list of this system */
	virtual void add_patrol(police *);

	/** Remove a given police unit from the patroller list of this system */
	virtual void remove_patrol(police *);

	/** Launch or issue police patrols on agressors! */
	virtual void on_actor_attacked(ostream &os, actor *attacker, actor *victim);

	static game_object * from_ptree(game *g, boost::property_tree::ptree tree);
	virtual void init(game *g, boost::property_tree::ptree tree);
};

};

#endif
