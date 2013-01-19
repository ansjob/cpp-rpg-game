#include <map>
#include <locale>
#include <string>
#include <utility>
#include <iostream>
#include <algorithm>
#include <boost/regex.hpp>

#include "npc.h"
#include "game.h"
#include "utils.h"
#include "player.h"
#include "adverb.h"
#include "buy_action.h"
#include "solar_system.h"

using namespace std;
using namespace boost;

namespace rpg {

buy_action::buy_action(game &ref) : action(ref) {};

int buy_action::operator()(ostream &os, string args) {
	string pattern("[\\s]*([0-9]+)[\\s]+(?:from[\\s]+)?((?:(?:\\w \\w)|\\w)+)(?:\\s)*");
	regex expr;
	expr = regex(pattern, regex::icase);

	smatch m;
	if (regex_search(args, m, expr)) {
		string target = m[2];
		// Because the map we're making the lookup in is in lower case
		target = utils::tolower(target);
		solar_system& loc = g.m_player->location();
		auto it = loc.actors.find(target);
		if (it != loc.actors.end()) {
			if (it->second->selling) {
				try {
					int item_no = stoi(m[1]);
					return it->second->buy(os, g.m_player, unsigned(item_no));
				} catch (...) {
					os << "Nobody has that many things to sell" << endl;
					return 0;
				}
			}
			else {
				os << it->second->name() << " is not selling anything!" << endl;
				return 0;
			}
		}
		os << "There's nobody by that name here" << endl;
	}
	else {
		os << "Invalid usage! Type 'help buy' for more info." << endl;
	}
	return 0;
};

ostream& buy_action::print_short_help(ostream& os) {
	os << "Buy items from merchants in the current solar system. Example use: buy 4 from john";
	return os;
};

ostream& buy_action::print_long_help(ostream& os) {
	os << "The buy command is used to buy items from characters.\n"
		<< "The 'from' keyword is optional.\n" 
		<< "A character that sells items will list their items when you talk to them.";
	return os;
}

};
