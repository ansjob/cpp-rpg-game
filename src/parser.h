#ifndef PARSER_H
#define PARSER_H

#include <map>

#include "action.h"

using namespace std;

namespace rpg {

class parser {
private:
	action* invalid_action;
	map<string, action*> & actions;
	ostream &os;

public:
	parser(action* inv, map<string, action*> & a, ostream &s) : invalid_action(inv), actions(a), os(s) {}

	/**
	 *	Parse and execute a command string.
	 *	@param line String with the command and its arguments.
	 */
	int parse_exec(string line);
};

};
#endif
