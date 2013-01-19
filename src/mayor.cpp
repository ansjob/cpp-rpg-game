#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "item.h"
#include "shield.h"
#include "adverb.h"
#include "mayor.h"

using namespace std;

namespace rpg {

mayor::mayor(string name, string desc, game *g) : npc(name, desc), talked_to(false), m_game(g) {

	shield * cur_shield = new shield("Mayoral Shield",
		"A fine Shield to protect the mayor",
		10, 5000, 1, 15, 300);
	stringstream ss;
	cur_shield->move_to(*this);
	cur_shield->use(ss, this);

};

string mayor::talk() {
	stringstream os;

	os << name() << " (" << random_adverb() << "): Thank you for getting rid of " <<
	"that gangster. I'm quite sure he has fled and will not return.";
	talked_to = true;

	return os.str();
};

void mayor::tick(ostream& os) {
	if (talked_to) {
		os << "Congratulations! You have beaten the game. Now do something productive!" << endl;
		m_game->exit();
	}
};

game_object * mayor::from_ptree(game *g, boost::property_tree::ptree tree) {
	using boost::property_tree::ptree;

	string name = tree.get<string>("name");
	string desc = tree.get<string>("m_desc");
	mayor *actor = new mayor(name, desc, g);
	actor->init(g, tree);
	return actor;
}

};

