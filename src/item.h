#ifndef ITEM_H
#define ITEM_H

#include <string>

#include "game_object.h"

using namespace std;

namespace rpg {

class item_carrier;
class solar_system;
class actor;

class item : public game_object {
protected:
	int m_volume;
	int m_value;

public:
	/**
	 *	Create a new item
	 *	@param n Name of the item
	 *	@param desc Description of the item
	 *	@param vol Item volume
	 *	@param val Value of the item
	 */
	item(string n = "Dummy item", string desc = "Dummy item description", int vol = 0, int val = 0) :
		game_object(n, desc), m_volume(vol), m_value(val) {}

	virtual void move_to(item_carrier &dest);

	/**	Return the volume of this item. */
	virtual int volume() {
		return m_volume;
	}

	/**	Return the value of this item.  */
	virtual int value() {
		return m_value;
	}

	/**
	 *	Use the item.
	 *	@param actor The actor who should use the item.
	 */
	virtual void use(ostream& os, actor*);

	/** Remove the item from its current parent */
	virtual void remove();

	/** Return a pointer to a copy of this object. (REMEMBER TO DELETE) */
	virtual item * copy() const;

	virtual boost::property_tree::ptree to_ptree() const;

	void init(game *g, boost::property_tree::ptree tree);
	static item * from_ptree(game * g, boost::property_tree::ptree);

};

};

#endif
