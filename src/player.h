#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <sstream>

#include "actor.h"

using namespace std;

namespace rpg {

class game;
class solar_system;

class player : public actor {
private:
	game *m_game;

public:
	player(string n, game *g);

	virtual string talk();
	virtual void tick(ostream &os);
	virtual void after_tick(ostream &os);
	virtual void die(ostream &os);

	virtual void set_name(string str){
		m_name = str;
	};

	virtual void init(game * g, boost::property_tree::ptree);
	static player * from_ptree(game * g, boost::property_tree::ptree);
};

};

#endif
