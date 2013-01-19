#ifndef TALK_ACTION_H
#define TALK_ACTION_H

#include <string>
#include <iostream>

#include "action.h"

using namespace std;
namespace rpg {

class game;

class talk_action : public action {
public:

	talk_action(game &ref);

	virtual int operator()(ostream &os, string args = "");
	virtual ostream& print_short_help(ostream& os);
	virtual ostream& print_long_help(ostream& os);

};

};
#endif
