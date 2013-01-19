#ifndef ALIAS_ACTION_H
#define ALIAS_ACTION_H

#include <string>
#include <iostream>

#include "action.h"

using namespace std;

namespace rpg {

class game;

class alias_action : public action {

	/** The actual action to carry out */
	action * impl;
	/** Name of the actual action */
	string orig_name;

public:

	/**
	 *	Construct a new alias action for the specified command and its action.
	 *	@param orig Name of the action or command the alias refers to.
	 *	@param real_command Pointer to the actual action to execute.
	 */
	alias_action(game& ref, const string& orig, action* real_command) ;

	virtual int operator()(ostream &os, string args = "");
	virtual ostream& print_short_help(ostream& os);
	virtual ostream& print_long_help(ostream& os);
	virtual ~alias_action() {};
};

};
#endif
