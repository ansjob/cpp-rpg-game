#include <iostream>
#include <string>

#include "action.h"
#include "game.h"

using namespace std;

namespace rpg {

/**
 * A command to print the help messages provided by
 * each of the available commands.
 */
class help_action : public action {

	public:
	help_action(game& ref);
	virtual int operator()(ostream& os, string args = "");
	virtual ostream& print_short_help(ostream& os);
	virtual ostream& print_long_help(ostream& os);
};

};
