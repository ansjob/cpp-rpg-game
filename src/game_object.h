#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <algorithm>
#include <cassert>
#include <set>
#include <iostream>
#include <functional>
#include <boost/property_tree/ptree.hpp>

#include "game.h"

using namespace std;

namespace rpg {

class game;

class game_object {

public:
	game_object		*parent;
	set<game_object*>	children;

protected:
	string m_name;
	string m_desc;

public:
	unsigned long id;


	game_object(string name = "generic object", string desc = "generic object description");
	virtual ~game_object();

	/** Empty function overridden by subclasses. */
	virtual void tick(ostream &os) {};

	/** Move this game object from current parent to specified parent. */
	virtual void move_to(game_object &ref) ;

	/** Remove this game object from current parent (if any). */
	virtual void remove();

	/** Return the name of the game object. */
	virtual string name() const {
		return m_name;
	}

	/** Set the name of the game object. (could be dangerous if it is contained somewhere!) */
	virtual void name(string str) {
		m_name = str;
	}

	/** Return the description of the game object. */
	virtual string desc() const {
		return m_desc;
	}

	/** Run a tick on self and children. */
	void on_tick(ostream &os) {
		tick(os);
		for (auto child = children.begin(); child != children.end();) {
			(*child++)->on_tick(os);
		}
		for (auto child = children.begin(); child != children.end();) {
			(*child++)->after_tick(os);
		}
	};

	virtual void after_tick(ostream &os) {
		// Do nothing.
	}

	/** Returns a ptree representation of this game object */
	virtual boost::property_tree::ptree to_ptree() const;

	/** Initializes the object from a ptree */
	virtual void init(game * g, boost::property_tree::ptree ptree);

	/** Allocates the game object on the heap, initializes it and all children, and returns the reference */
	static game_object * from_ptree(game *, boost::property_tree::ptree);
};

};
#endif
