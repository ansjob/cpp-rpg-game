#include <string>
#include <iostream>
#include <algorithm>
#include <boost/regex.hpp>

#include "game.h"
#include "utils.h"
#include "adverb.h"
#include "player.h"
#include "use_action.h"
#include "solar_system.h"

using namespace std;
using namespace boost;

namespace rpg {

use_action::use_action(game &ref) : action(ref) {};

int use_action::operator()(ostream &os, string args) {

	if (args == "") {
		os << "Use what?" << endl;
		return 0;
	}

	string pattern = action::item_regexp();
	regex expr;
	expr = regex(pattern, regex::icase);

	smatch m;
	if (regex_search(args, m, expr)) {
		string obj = m[1];
		item *it = NULL;
		for (auto item_pair : g.m_player->items()) {
			if (utils::tolower(item_pair.first) == utils::tolower(obj)) {
				it = item_pair.second;
				break;
			}
		}
		if (it == NULL) {
			os << "The inventory robot " << random_adverb() << " reports she cannot fetch any object called "
				<< "'" << obj << "' for you to use." << endl;
		} else {
			it->use(os, g.m_player);
			return 1;
		}
	} else {
		throw runtime_error("No match?");
	}
	return 0;
};

ostream& use_action::print_short_help(ostream& os) {
	os << "uses an object in your cargo bay. Example use: use apple";
	return os;
};

ostream& use_action::print_long_help(ostream& os) {
	os << "The use command is used to use items located in your cargo bay. \n";
	return os;
}

};
