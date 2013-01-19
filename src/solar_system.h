#ifndef SOLARSYSTEM_H
#define SOLARSYSTEM_H

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <boost/property_tree/ptree.hpp>

#include "game_object.h"
#include "item_carrier.h"

using namespace std;

namespace rpg {

class player;
class actor;
class item;

class solar_system : public game_object, public item_carrier {
protected:
	multimap<string, item*> m_items;

public:
	stringstream echo;
	solar_system(string n, string d = "Dummy solar system"); 
	map<string, solar_system*> neighbours;
	map<string, actor*> actors;

	virtual void tick(ostream &os);

	/** Returns whether the player can currently enter this system */
	virtual bool accepts(player& player); 

	/** Print to ostream the reason why the player cannot currently enter this system */
	virtual void print_deny_message(ostream& os);

	/** Print to ostream a message for when the player enters the system */
	virtual void print_enter_message(ostream& os);

	/** A hook for when actors attack each other in the system */
	virtual void on_actor_attacked(ostream &os, actor *attacker, actor *victim);

	virtual multimap<string, item*> & items();
	virtual const multimap<string, item*> & items() const;

	static game_object * from_ptree(game *g, boost::property_tree::ptree tree);
	virtual void init(game * g, boost::property_tree::ptree tree);

	virtual boost::property_tree::ptree to_ptree() const;
};

};

#endif
