#include <map>
#include <string>
#include <sstream>

#include "npc.h"
#include "adverb.h"
#include "solar_system.h"
#include "initializers.h"

using namespace std;

namespace rpg {

extern initializer initializers;

npc::npc(string name, string desc) : actor(name, desc) {};

bool npc::hostile_against(actor * target) {
	auto it = hostile_map.find(target->name());
	if (it == hostile_map.end())
		return false;
	return it->second;
}

void npc::make_hostile_against(actor *target) {
	hostile_map[target->name()] = true;
}

void npc::take_damage(ostream &os, actor *attacker, int damage) {
	/* Mark the possible attacker as hostile! */
	if (attacker != NULL) {
		hostile_map[attacker->name()] = true;
	}

	/* Take damage as usual */
	actor::take_damage(os, attacker, damage);
}

void npc::tick(ostream &os) {

	if (m_hp == 0) return;

	/* Look at every actor in the current location */
	for (auto it : location().actors) {
		auto actorp = it.second;

		/* Don't act versus self */
		if (actorp == this)
			continue;

		/* See if we found someone we're hostile against */
		if (hostile_against(actorp)) {
			if (current_weapon() == NULL) {
				/* Pick a random neighbouring system and flee to it */
				auto it = location().neighbours.begin();
				int n = location().neighbours.size();
				if (n > 0)
					advance(it, random() % n);
				if (random() % 100 > 95) return;
				location().echo << name() << " " << random_adverb() << " moves through " << it->first << endl;
				move_to(*(it->second));
			} else {
				/* Fight hostile actor! */
				this->attack(os, actorp);
			}
			return;
		}
	}
}

boost::property_tree::ptree npc::to_ptree() const {
	using boost::property_tree::ptree;
	ptree pt = actor::to_ptree();

	ptree hostiles;
	for (auto entry : hostile_map) {
		if (entry.second)
			hostiles.put("entry", entry.first);
	}
	pt.add_child("hostiles", hostiles);

	return pt;
};

using boost::property_tree::ptree;

npc * npc::from_ptree(game * g, ptree tree) {
	npc * c = new npc(tree.get<string>("name"), tree.get<string>("m_desc"));

	c->init(g, tree);

	return c;

}

void npc::init(game * g, ptree tree) {

	actor::init(g, tree);

	/* Parse hostile map */
	ptree hostiles = tree.get_child("hostiles");
	for (auto entry : hostiles) {
		hostile_map[entry.second.get<string>("")] = true;
	}

}

};


