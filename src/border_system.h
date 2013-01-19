#ifndef BORDERSYSTEM_H
#define BORDERSYSTEM_H

#include <map>
#include <string>
#include <iostream>
#include <sstream>

#include "solar_system.h"

using namespace std;

namespace rpg {

class player;
class actor;
class item;

class border_system : public solar_system {
public:
	border_system(string n, string d = "Dummy solar system"); 

	/** Returns whether the player can currently enter this system */
	virtual bool accepts(player& player); 

	/** Print to ostream the reason why the player cannot currently enter this system */
	virtual void print_deny_message(ostream& os);

	/** Print to ostream a message for when the player enters the system */
	virtual void print_enter_message(ostream& os);

	static border_system* from_ptree(game* g, boost::property_tree::ptree);

};

};

#endif
