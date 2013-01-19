#include "game.h"
#include "adverb.h"
#include "quit_action.h"

using namespace std;

namespace rpg {

	quit_action::quit_action(game& ref): action(ref) {};

	int quit_action::operator()(ostream &os, string args) {
		g.exit();
		return 0;
	};

	ostream& quit_action::print_short_help(ostream& os) {
		os << "Exits the game";
		return os;
	}

	ostream& quit_action::print_long_help(ostream& os) {
		os << "The quit command exits the game";
		return os;
	}
};
