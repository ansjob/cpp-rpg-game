#include <sstream>
#include <string>

#include "actor.h"
#include "adverb.h"
#include "initializers.h"
#include "consumable_item.h"

using namespace std;

namespace rpg {

extern initializer initializers;

void consumable_item::use(ostream& os, actor* a) {
	bool consume;
	os << a->name() << " used " << name() << endl;
	consume = this->m_function(os, a);

	/* Don't consume items that are reusable */
	if (!consume)
		return;

	/* Delete the item (it is consumed) */
	remove();
	delete this;
}; 

game_object * consumable_item::from_ptree(game *g, boost::property_tree::ptree tree) {
	using boost::property_tree::ptree;

	/* Find the fields and construct the item */
	string name = tree.get<string>("name");
	string desc = tree.get<string>("m_desc");
	int volume = tree.get<int>("m_volume");
	int value = tree.get<int>("m_value");
	game_object * itam = new consumable_item(name, desc, volume, value,
		/* TODO: fix this */
		[](ostream &os, actor* user) { return true; }
	);

	/* Parse its children */
	ptree childs = tree.get_child("children");
	for (auto it = childs.begin(); it != childs.end(); ++it) {
		game_object * child = initializers[it->first](g, it->second);
		child->move_to(*itam);
	}

	return itam;
}

};
