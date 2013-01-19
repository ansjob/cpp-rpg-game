#ifndef CONSUMABLE_ITEM_H
#define CONSUMABLE_ITEM_H

#include <string>
#include <functional>

#include "item.h"

using namespace std;

namespace rpg {

class actor;

class consumable_item : public item {
protected:
	function<bool (ostream &os, actor * ap)> m_function;

public:
	/**
	 *	Create a new consumable item
	 *	@param n Name of the consumable item
	 *	@param desc Description of the consumable item
	 *	@param vol Item volume
	 *	@param val Value of the consumable_item
	 *	@param fun Lambda function for the use action of this item
	 */
	consumable_item(string n = "Dummy consumable_item", string desc = "Dummy consumable_item description", int vol = 0, int val = 0, function<bool (ostream &os, actor*)> fun = [] {}) :
		item(n, desc, vol, val), m_function(fun) {}

	/**
	 *	Use the consumable item.
	 *	@param actor The actor who should use the consumable item
	 */
	virtual void use(ostream& os, actor*);

	/** Construct item from a ptree */
	static game_object * from_ptree(game *g, boost::property_tree::ptree tree);
};

};

#endif
