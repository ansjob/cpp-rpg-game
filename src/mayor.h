#ifndef MAYOR_H
#define MAYOR_H

#include <string>
#include <sstream>

#include "npc.h"
#include "item.h"

using namespace std;

namespace rpg {

class game;

class mayor : public npc {
	bool talked_to;
	game *m_game;

public:
	mayor(string name, string desc, game *g);

	virtual string talk();
	virtual void tick(ostream& os);

	static game_object * from_ptree(game *g, boost::property_tree::ptree tree);
};
};

#endif
