#include "alias_action.h"

using namespace std;

namespace rpg {

	alias_action::alias_action(game& ref, const string& orig, action* real_command): 
		action(ref), impl(real_command), orig_name(orig) {};

	int alias_action::operator()(ostream &os, string args) {
		return impl->operator()(os, args);
	};

	ostream& alias_action::print_short_help(ostream& os) {
		os << "Alias for " << orig_name;
		return os;
	}

	ostream& alias_action::print_long_help(ostream& os) {
		os << "This command is an alias for " << orig_name << "." << endl
			<< "This means you can use these either one that you prefer." << endl 
			<< "For more information, type 'help " << orig_name << "'.";
		return os;
	}

};
