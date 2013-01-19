#include "poisoned_system.h"
#include "initializers.h"
#include "actor.h"

namespace rpg {

extern initializer initializers;

poisoned_system::poisoned_system(string n, string desc) : solar_system(n, desc) {};

void poisoned_system::tick(ostream& os) {
	/* Do regular things a solar system does */
	solar_system::tick(os);
	for (pair<string, actor *> entry : actors) {
		actor * occupant = entry.second;
		int sum = occupant->hp() + occupant->shield_hp();
		int percents_damage = 5 + (random() % 5);
		int damage = (sum * percents_damage) / 100;
		echo << "The poison in " << name() << " causes " << damage << " damage to " <<
			occupant->name() << endl;
		occupant->take_damage(echo, NULL, damage);
	}

};

poisoned_system * poisoned_system::from_ptree(game * g, boost::property_tree::ptree tree) {
	string name = tree.get<string>("name");
	poisoned_system * res = new poisoned_system(name);
	res->init(g, tree);
	return res;
};

};

