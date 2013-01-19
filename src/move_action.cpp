#include <map>
#include <string>
#include <utility>
#include <iostream>
#include <boost/regex.hpp>

#include "game.h"
#include "adverb.h"
#include "player.h"
#include "move_action.h"
#include "solar_system.h"

using namespace std;
using namespace boost;

namespace rpg {

move_action::move_action(game &ref) : action(ref) {};

int move_action::operator()(ostream &os, string args) {
	string pattern("[\\s]*(?:to[\\s]+)?((?:(?:\\w \\w)|\\w)+)(?:\\s)*");
	regex expr;
	expr = regex(pattern, regex::icase);

	smatch m;
	if (regex_search(args, m, expr)) {
		string destination = m[1];
		typename map<string, solar_system*>::iterator it 
			= g.m_player->location().neighbours.find(destination);
		if (it == g.m_player->location().neighbours.end()) {
			os << "You " << random_adverb() << " realize that you cannot " <<
				random_adverb() << " move " << destination <<  " from here." << endl;
		}
		else {
			if (it->second->accepts(*g.m_player)) {
				g.m_player->move_to(*(it->second));
				it->second->print_enter_message(os);
				return 1;
			}
			else {
				it->second->print_deny_message(os);
			}
		}
	}
	else {
		os << "Invalid destination '" << args << "'!" << endl;
	}
	return 0;
};

ostream& move_action::print_short_help(ostream& os) {
	os << "move between different systems. Example use: move east";
	return os;
};

ostream& move_action::print_long_help(ostream& os) {
	os << "The move command is used to move between different systems within a galaxy.\n"
		<< "To find out the directions you can travel from your current; type 'scan'";
	return os;
}

};
