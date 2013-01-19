#ifndef POISONED_SYSTEM_H
#define POISONED_SYSTEM_H

#include <map>
#include <string>
#include <iostream>

#include "solar_system.h"

using namespace std;

namespace rpg {

class actor;

class poisoned_system : public solar_system {
private:

public:
	poisoned_system(string n, string d = "A poisoned solar system, it causes all occupants to lose between 5-10% of their hp every turn."); 

	virtual void tick(ostream &os);
	static poisoned_system * from_ptree(game * g, boost::property_tree::ptree);
};

};

#endif
