#include <map>
#include <string>
#include <locale>
#include <utility>
#include <iostream>
#include <algorithm>
#include <boost/regex.hpp>

#include "npc.h"
#include "game.h"
#include "utils.h"
#include "adverb.h"
#include "player.h"
#include "talk_action.h"
#include "solar_system.h"

using namespace std;
using namespace boost;

namespace rpg {

talk_action::talk_action(game &ref) : action(ref) {};

int talk_action::operator()(ostream &os, string args) {
	string pattern("[\\s]*(?:to[\\s]+)?((?:(?:\\w \\w)|\\w)+)(?:\\s)*");
	regex expr;
	expr = regex(pattern, regex::icase);

	smatch m;
	if (regex_search(args, m, expr)) {
		string target = m[1];
		// Because the map we're making the lookup in is in lower case
		target = utils::tolower(target);
		solar_system& loc = g.m_player->location();
		auto it = loc.actors.find(target);
		if (it != loc.actors.end()) {
			os << it->second->talk() << endl;
			return 1;
		}
		os << "There's nobody by that name here" << endl;
	}
	else {
		os << "Could not understand the name of the person you wanted to talk to" << endl;
	}
	return 0;
};

ostream& talk_action::print_short_help(ostream& os) {
	os << "Talk to characters in the current solar system. Example use: talk to john";
	return os;
};

ostream& talk_action::print_long_help(ostream& os) {
	os << "The talk command is used to talk to characters in the game.\n"
		<< "The 'to' keyword is optional.";
	return os;
}

};
