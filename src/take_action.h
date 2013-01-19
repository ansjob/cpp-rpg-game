#ifndef TAKE_ACTION_H
#define TAKE_ACTION_H

#include <string>
#include <iostream>

#include "action.h"

using namespace std;
namespace rpg {

class game;

class take_action : public action {
public:

	take_action(game &ref);

	virtual int operator()(ostream &os, string args = "");
	virtual ostream& print_short_help(ostream& os);
	virtual ostream& print_long_help(ostream& os);

};

};
#endif
