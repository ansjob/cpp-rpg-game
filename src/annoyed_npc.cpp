#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "shield.h"
#include "weapon.h"
#include "annoyed_npc.h"
#include "adverb.h"
#include "player.h"

using namespace std;

namespace rpg {

annoyed_npc::annoyed_npc(string name, string desc) : npc(name, desc) {
};

string annoyed_npc::talk() {
	stringstream os;
	player * p;
	for (pair<string, actor*> pr : location().actors) {
		actor * intruder = pr.second;
		p = dynamic_cast<player*>(intruder);
		if (p != NULL) {
			make_hostile_against(p);
			break;
		}
	}
	assert(p != NULL);
	os << name() << " (" << random_adverb() << "): Why are you disturbing me? Get outta here, you Canadian!" << endl;
	return os.str();
};

annoyed_npc * annoyed_npc::from_ptree(game * g, boost::property_tree::ptree tree) {
	annoyed_npc * a = new annoyed_npc(
		tree.get<string>("name"),
		tree.get<string>("m_desc")
	);
	a->init(g, tree);
	return a;
}

};
