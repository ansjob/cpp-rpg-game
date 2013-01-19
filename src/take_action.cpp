#include <string>
#include <iostream>
#include <algorithm>
#include <boost/regex.hpp>

#include "game.h"
#include "utils.h"
#include "adverb.h"
#include "player.h"
#include "take_action.h"
#include "solar_system.h"

using namespace std;
using namespace boost;

namespace rpg {

take_action::take_action(game &ref) : action(ref) {};

int take_action::operator()(ostream &os, string args) {

	if (args == "") {
		os << "Take what?" << endl;
		return 0;
	}

	string pattern = action::item_regexp();
	regex expr;
	expr = regex(pattern, regex::icase);

	smatch m;
	if (regex_search(args, m, expr)) {
		string obj = m[1];
		item *it = NULL;
		string obj_lower = utils::tolower(obj);
		for (auto item_pair : g.m_player->location().items()) {
			if (utils::tolower(item_pair.first) == obj_lower) {
				it = item_pair.second;
				break;
			}
		}
		if (it == NULL) {
			os << "Beaming Scanners " << random_adverb() << " indicate they cannot beam aboard "
				<< "'" << obj << "'" << endl;
		} else {
			if (g.m_player->avail_cargo() >= it->volume()) {
				it->move_to(*g.m_player);
				os << "You " << random_adverb() << " beamed aboard "
				  << it->name() << endl;
				return 1;
			}
			else {
				os << "While trying to " << random_adverb() << " beam aboard "
					<< it->name() << ", you " << random_adverb() <<
					" realize that its volume exceeds your current available cargo space." << endl;
			}
		}
	} else {
		throw runtime_error("No match?");
	}
	return 0;
};

ostream& take_action::print_short_help(ostream& os) {
	os << "takes an object in the current solar system. Example use: take apple";
	return os;
};

ostream& take_action::print_long_help(ostream& os) {
	os << "The take command is used to take items from the current solar system. \n"
	 << "Note that the item has to fit in your cargo bay in order to take it.\n";
	return os;
}

};
