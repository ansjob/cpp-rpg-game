#ifndef GAME_H
#define GAME_H

#include <ios>
#include <map>
#include <string>
#include <iostream>

#include "parser.h"
#include "game_object.h"
#include "invalid_action.h"

using namespace std;

namespace rpg {

class player;
class action;
class game_object;

class game {
private:
	//Private members
	istream& is;
	ostream& os;
	invalid_action m_inv;
	map<string, action*> m_actions; 
	parser m_parser;
	bool exit_issued;

	//Private methods
	map<string, action*> load_commands();
	game& operator=(const game& g) = delete;
	game(const game& g) = delete;

public : 
	//Public members
	player * m_player;
	game_object *universe;

	//Public constructor
	game(istream& in, ostream& out);

	//Destructor is public, obviously
	~game();

	//Public methods
	int run();
	void load_universe(const string filename = "univ.xml");
	map<string, action*> & actions();
	void exit();
	void load_savefile(const string filename);
	void print_intro();

};
};
#endif
