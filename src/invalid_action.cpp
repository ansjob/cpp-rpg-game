#include "invalid_action.h"

using namespace std;
namespace rpg {

	invalid_action::invalid_action(game& ref): action(ref) {};

	
	int invalid_action::operator()(ostream &os, string args) {
		os << "Invalid command!" << endl;
		return 0;
	};

	ostream& invalid_action::print_short_help(ostream& os) {
		os << "N/A";
		return os;
	}

	ostream& invalid_action::print_long_help(ostream& os) {
		os << "N/A";
		return os;
	}


};
