#include <string>
#include <iostream>
#include <algorithm>
#include <boost/regex.hpp>

#include "game.h"
#include "utils.h"
#include "adverb.h"
#include "player.h"
#include "solar_system.h"
#include "inventory_action.h"

using namespace std;
using namespace boost;

namespace rpg {

inventory_action::inventory_action(game &ref) : action(ref) {};

int inventory_action::operator()(ostream &os, string args) {
	auto player = g.m_player;
	if (args == "") {
		/* General inventory */
		if (player->items().size() > 0) {
			os << "Your inventory robot " << random_adverb() << " report of these items in you cargo area:\n";
			for (auto obj : player->items()) {
				os << "\t" << obj.second->name() << "\n";
			}
		} else {
			os << "Your inventory robot report that your cargo area is " << random_adverb() << " empty.\n";
		}
		os << "\n";

		os << "Hull status: " << player->hp() << "/" << player->max_hp() << "\n\n";

		os << "Ship monitors " << random_adverb();
		os << " indicate the following mounted equipment:\n";
		auto w = player->current_weapon();
		os << "Weapon: " << (w==NULL?"No weapon equipped!":w->name()) << "\n";
		auto s = player->current_shield();
		os << "Shield: " << (s==NULL?"No shield equipped!":s->name()) << "\n\n";
	} else {
		/* Specific inventory */
		string pattern = action::item_regexp();
		regex expr;
		expr = regex(pattern, regex::icase);

		smatch m;
		if (regex_search(args, m, expr)) {
			string obj = m[1];
			game_object *it = NULL;

			/* Search inventory */
			for (auto child : player->items()) {
				if (child.first == utils::tolower(obj)) {
					it = child.second;
					break;
				}
			}

			/* Check weapon slot */
			if (it == NULL && player->current_weapon() != NULL) {
				if (utils::tolower(player->current_weapon()->name()) == utils::tolower(obj))
					it = player->current_weapon();
			}

			/* Check shield slot */
			if (it == NULL && player->current_shield() != NULL) {
				if (utils::tolower(player->current_shield()->name()) == utils::tolower(obj))
					it = player->current_shield();
			}

			if (it == NULL) {
				os << "The inventory robot " << random_adverb() << 
				" reports she cannot find anything called "
					<< "'" << obj << "' in your cargo bay.\n" <<
				"She will sulk " << random_adverb() << 
				" in the corner until you have further orders." << endl;
			} else {
				os << it->desc() << endl;
			}
		} else {
			os << "No such entity!" << endl;
		}
	}
	return 0;
};

ostream& inventory_action::print_short_help(ostream& os) {
	os << "Lists or inspects items in your inventory";
	return os;
};

ostream& inventory_action::print_long_help(ostream& os) {
	os << "The inventory command is used to either list the items in your cargo bay," <<
		" or read the description of a specified item.\n" <<
		"Example use #1: inventory \n" << 
		"Example use #2: inventory apple\n" <<
		"See also: inv";
	return os;
}

};
