#include <map>
#include <string>
#include <sstream>

#include "parser.h"

using namespace std;

namespace rpg {

int parser::parse_exec(string line) {
	stringstream ss(line);
	string command;

	/* Trim leading whitespace */
	while (ss.peek() == ' ')
		ss.ignore(1);

	/* Read command */
	ss >> command;

	/* Get parameters */
	string args;
	getline(ss, args, '\n');

	if (command == "")
		return 0;

	/* Execute corresponding action */
	auto it = actions.find(command);
	if (it == actions.end())
		return (*invalid_action)(os, line);
	else
		return (*(it->second))(os, args);

}

};
