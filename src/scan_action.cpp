#include <string>
#include <iostream>
#include <algorithm>
#include <boost/regex.hpp>

#include "game.h"
#include "utils.h"
#include "adverb.h"
#include "player.h"
#include "scan_action.h"
#include "solar_system.h"

using namespace std;
using namespace boost;

namespace rpg {

scan_action::scan_action(game &ref) : action(ref) {};

int scan_action::operator()(ostream &os, string args) {
	auto player = g.m_player;
	if (args == "") {
		/* General scan */
		os << "The short range scanners " << random_adverb() << " indicate the existance of:\n";
		for (auto obj : player->location().children) {
			os << "\t" << obj->name() << "\n";
		}

		os << "\nLong range scanners " << random_adverb() << " reveal the neighbouring systems:\n";
		for (auto sys : player->location().neighbours) {
			os << "\t" << sys.second->name() << " (" << sys.first << ")\n";
		}
		os << "\n";
	} else {
		/* Specific scan */
		string pattern = action::item_regexp();
		regex expr;
		expr = regex(pattern, regex::icase);

		smatch m;
		if (regex_search(args, m, expr)) {
			string obj = m[1];
			game_object *it = NULL;

			/* Search neighbouring solar systems */
			for (auto sys : player->location().neighbours) {
				if (utils::tolower(sys.second->name()) == utils::tolower(obj)) {
					it = sys.second;
					break;
				}
			}

			/* Search in current solar system */
			if (it == NULL) {
				for (auto child : player->parent->children) {
					if (utils::tolower(child->name()) == utils::tolower(obj)) {
						it = child;
						break;
					}
				}
			}

			/* Print found item descriptions or error message */
			if (it == NULL) {
				os << "Scanners " << random_adverb() << " indicate it cannot find "
					<< "'" << obj << "'" << endl;
			} else {
				os << "Scanners " << random_adverb() << " give you the following "
					"description of the entity:\n" << it->desc() << endl;
			}
		} else {
			os << "No such entity!" << endl;
		}
	}
	return 0;
};

ostream& scan_action::print_short_help(ostream& os) {
	os << "scans the current solar system. Example use: scan";
	return os;
};

ostream& scan_action::print_long_help(ostream& os) {
	os << "The scan command is used to scan the current solar system, listing its items, ships, planets etc.\n";
	return os;
}

};
