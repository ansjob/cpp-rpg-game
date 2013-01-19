#include <sstream>
#include <iomanip>

#include "help_action.h"

namespace rpg {
	help_action::help_action(game& ref) : action(ref) {};

	int help_action::operator()(ostream& os, string args) {

		stringstream ss(args);
		string command;
		ss >> command;
		if (command != "") {
			auto m = g.actions();
			auto it = m.find(command);
			if (it == m.end()) {
				os << "help: cannot find command " << command << endl;
			}
			else {
				os << endl;
				it->second->print_long_help(os);
				os << endl << endl;
			}
		}
		else {
			os << "These are the commands available to you:" << endl << endl;
			for (auto pair : g.actions()) {
					os << "  " << setiosflags(ios::left) << setw(24) << pair.first;
				pair.second->print_short_help(os);
				os << endl;
			}
			os 	<< endl << "For help about each command. Type 'help COMMAND'," 
				<< " where COMMAND is the command you wish to know more about." << endl;
		}
		return 0;
	};

	ostream& help_action::print_short_help(ostream& os) {
		os << "Prints the help message for a command (or this message)";
		return os;
	};

	ostream& help_action::print_long_help(ostream& os) {
		os << "The help command is used to find out how to use other commands.\n"
			<< "\t Example: help move";
		return os;
	};

	
};
