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
#include "solar_system.h"
#include "attack_action.h"

using namespace std;
using namespace boost;

namespace rpg {

attack_action::attack_action(game &ref) : action(ref) {};

int attack_action::operator()(ostream &os, string args) {
	string pattern("[\\s]*((?:(?:\\w \\w)|\\w)+)(?:\\s)*");
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
			g.m_player->attack(os, it->second);
			return 1;
		}
		os << "There's nobody by that name here" << endl;
		return 0;
	}
	else {
		os << "Could not understand the name of the person you wanted to attack" << endl;
		return 0;
	}
};

ostream& attack_action::print_short_help(ostream& os) {
	os << "Attack someone in the current solar system. Example use: attack john";
	return os;
};

ostream& attack_action::print_long_help(ostream& os) {
	os << "The attack command is used to attack characters in the game.\n";
	return os;
}

};
