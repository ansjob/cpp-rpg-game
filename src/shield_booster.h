#ifndef SHIELD_BOOSTER_H
#define SHIELD_BOOSTER_H

#include <string>
#include <functional>

#include "item.h"
#include "consumable_item.h"

using namespace std;

namespace rpg {

class actor;

class shield_booster : public consumable_item {

public:
	/**
	 *	Create a new shield booster.
	 */
	shield_booster();

	/** Construct item from a ptree */
	static game_object * from_ptree(game *g, boost::property_tree::ptree tree);
};

};

#endif
