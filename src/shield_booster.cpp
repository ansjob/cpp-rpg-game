#include <sstream>
#include <string>

#include "actor.h"
#include "adverb.h"
#include "initializers.h"
#include "shield_booster.h"
#include "consumable_item.h"

using namespace std;

namespace rpg {

extern initializer initializers;

auto fun = [](ostream &os, actor *user) {
	if (user->current_shield() == NULL) {
		os << "Nothing happens." << endl;
		return false;
	}
	user->current_shield()->recharge(os, 50);
	return true;
};

shield_booster::shield_booster() : consumable_item("Shield booster",
	"A one time item to recharge shields instantly.", 5, 50, fun) {};

game_object * shield_booster::from_ptree(game *g, boost::property_tree::ptree tree) {

	shield_booster *p = new shield_booster;

	return p;
}

};
