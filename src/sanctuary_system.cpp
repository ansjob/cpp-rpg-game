#include <set>
#include <cassert>

#include "actor.h"
#include "police.h"
#include "initializers.h"
#include "sanctuary_system.h"

namespace rpg {

extern initializer initializers;

sanctuary_system::sanctuary_system(string n, string desc) : solar_system(n, desc) {};

void sanctuary_system::tick(ostream& os) {
	/* Do regular things a solar system does */
	solar_system::tick(os);

	/* Spawn more police patrols if none exist */
};

void sanctuary_system::add_patrol(police *p) {
	auto ret = patrols.insert(p);
	assert(ret.second);
};

void sanctuary_system::remove_patrol(police *p) {
	size_t ret = patrols.erase(p);
	assert(ret > 0);
};

void sanctuary_system::on_actor_attacked(ostream &os, actor *attacker, actor *victim) {
	/* Don't do anything if attacker is not set */
	if (attacker == NULL)
		return;

	/* Police patrols are allowed to attack (don't react) */
	if (patrols.find(attacker) != patrols.end())
		return;

	/* If insufficient patrols, spawn more! */
	if (patrols.size() < 2) {
		os << "Due to aggression, authorities in " << name() << " issues its police patrols"
			<< " to enforce the system's no-violence policy!" << endl;
		while (patrols.size() < 2) {
			stringstream ss;
			ss << name() << " police patrol " << patrols.size() + 1;
			police *p = new police(ss.str(), "A patrolling policeman", this);
			p->move_to(*this);
		}
	}

	/* Set all patrols hostile towards attacker */
	for (auto p : patrols) {
		police *pol = dynamic_cast<police *>(p);
		assert(pol != NULL);
		pol->make_hostile_against(attacker);
	}
};

game_object * sanctuary_system::from_ptree(game *g, boost::property_tree::ptree tree) {
	using boost::property_tree::ptree;

	/* Find the name and construct solar system */
	string name = tree.get<string>("name");
	string desc = tree.get<string>("m_desc");
	game_object * sys = new sanctuary_system(name, desc);

	sys->init(g, tree);

	return sys;
};

void sanctuary_system::init(game *g, boost::property_tree::ptree tree) {
	solar_system::init(g, tree);

	for (game_object * child : children) {
		police *p = dynamic_cast<police*>(child);
		if (p != NULL) {
			add_patrol(p);
		}
	}
}

};
