#include <sstream>

#include "game.h"
#include "utils.h"
#include "alias_action.h"
#include "create_alias_action.h"

using namespace std;

namespace rpg {

	create_alias_action::create_alias_action(game& ref): action(ref) {};
	
	int create_alias_action::operator()(ostream &os, string args) {
		string target;
		string alias;
		stringstream ss(args);
		ss >> alias;
		ss >> target;
		auto it = g.actions().find(target); 
		if (it == g.actions().end()) {
			os << "No such command to alias" << endl;
		}
		else if (g.actions().find(alias) != g.actions().end()) {
			os << "A command by that name already exists!" << endl;
		}
		else {
			g.actions()[utils::tolower(alias)] = new alias_action(g, target, g.actions()[target]);
			os << "Added alias '" << alias << "' for command '" << target << "'." << endl;
		}
		return 0;
	};

	ostream& create_alias_action::print_short_help(ostream& os) {
		os << "Create an alias for a command. Example use: alias cd move";
		return os;
	}

	ostream& create_alias_action::print_long_help(ostream& os) {
		os << "N/A";
		return os;
	}
};
