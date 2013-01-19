#include <string>
#include <iostream>
#include <algorithm>
#include <boost/regex.hpp>

#include "game.h"
#include "utils.h"
#include "player.h"
#include "adverb.h"
#include "drop_action.h"
#include "solar_system.h"

using namespace std;
using namespace boost;

namespace rpg {

drop_action::drop_action(game &ref) : action(ref) {};

int drop_action::operator()(ostream &os, string args) {

	if (args == "") {
		os << "Drop what?" << endl;
		return 0;
	}

	string pattern("[\\s]*((?:(?:\\w \\w)|\\w)+)(?:\\s)*");
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
			os << "Your inventory robot " << random_adverb() << " indicate she cannot find "
				<< "anything called '" << obj << "'" << endl;
		} else {
			it->move_to(g.m_player->location());
			os << "You " << random_adverb() << " beamed "
			  << it->name() << " into the vastness of space" << endl;
			return 1;
		}
	} else {
		os << "Drop what?" << endl;
	}
	return 0;
};

ostream& drop_action::print_short_help(ostream& os) {
	os << "drops an object in the current solar system. Example use: drop apple";
	return os;
};

ostream& drop_action::print_long_help(ostream& os) {
	os << "The drop command is used to drop items from your inventory. \n"
		<< "The item will be dropped in the current solar system." << endl;
	return os;
}

};
