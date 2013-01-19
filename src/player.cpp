#include <string>
#include <sstream>

#include "game.h"
#include "player.h"
#include "adverb.h"
#include "initializers.h"
#include "solar_system.h"

using namespace std;

namespace rpg {
extern initializer initializers;

player::player(string n, game *g) : actor(n, "Your magnificient ship!"), m_game(g) {
	credits = 10000;
};

string player::talk() {
	stringstream ss;
	ss << "You talk angrily to yourself, and slowly drift into madness..." << endl;
	return ss.str();
};

void player::tick(ostream &os) {
	actor::tick(os);
}

void player::die(ostream &os) {
	os << "You " << random_adverb() << " die, how sad." << endl;
	m_game->exit();
}

void player::init(game * g, boost::property_tree::ptree tree){
	actor::init(g, tree);
	g->m_player = this;
};

player * player::from_ptree(game * g, boost::property_tree::ptree tree) {
	string name = tree.get<string>("name");
	player *p = new player(name, g);
	p->init(g, tree);
	return p;
}

void player::after_tick(ostream &os) {
	// Do nothing.
}

};
