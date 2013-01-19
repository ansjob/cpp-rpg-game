#ifndef NPC_H
#define NPC_H

#include <string>
#include <sstream>

#include "actor.h"

using namespace std;

namespace rpg {

class npc : public actor {
protected:
	map<string, bool> hostile_map;

public:
	npc(string name, string desc);

	/**
	 *	Returns whether or not the NPC is hostile towards the given actor.
	 */
	virtual bool hostile_against(actor *target);

	virtual void make_hostile_against(actor *target);

	/**
	 *	Basic intelligence for NPCs.
	 */
	virtual void tick(ostream &os);

	virtual void take_damage(ostream &os, actor *attacker, int damage);

	virtual boost::property_tree::ptree to_ptree() const;

	static npc * from_ptree(game * g, boost::property_tree::ptree);

	virtual void init(game * g, boost::property_tree::ptree);

};

};

#endif
