#include <sstream>

#include "wait_action.h"

using namespace std;

namespace rpg {

	wait_action::wait_action(game& ref): action(ref) {};

	
	int wait_action::operator()(ostream &os, string args) {
		stringstream ss(args);
		int turns = 1;
		ss >> turns;
		if (turns > 0) {
			os << "You sit and wait for " << turns << " turn" << ((turns > 1) ? "s" : "") << "." << endl;
			return turns;
		}
		os << "That's not a legal amount of time to wait!" << endl;
		return 0;
	};

	ostream& wait_action::print_short_help(ostream& os) {
		os << "Wait for a number of turns. Example use: wait 5";
		return os;
	}

	ostream& wait_action::print_long_help(ostream& os) {
		os << "N/A";
		return os;
	}


};
