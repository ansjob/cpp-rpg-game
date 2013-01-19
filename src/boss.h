#ifndef BOSS_H
#define BOSS_H

#include <string>
#include <sstream>

#include "hunter.h"
#include "solar_system.h"

using namespace std;

namespace rpg {

class solar_system;

class boss : public hunter {

public:
	boss(string name, string desc);

	virtual void die(ostream& os);

	virtual int max_hp() const;

	virtual string talk();

	/** Construct from ptree */
	static game_object * from_ptree(game *g, boost::property_tree::ptree tree);
};
};

#endif
