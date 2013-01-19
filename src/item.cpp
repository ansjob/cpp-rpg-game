#include <sstream>
#include <cassert>
#include <string>

#include "item.h"
#include "utils.h"
#include "actor.h"
#include "adverb.h"
#include "initializers.h"
#include "solar_system.h"
#include "item_carrier.h"

using namespace std;

namespace rpg {

extern initializer initializers;

void item::move_to(item_carrier &dest) {

	/* Remove from current location, if any */
	remove();

	/* Move to new location */
	string lower_name = utils::tolower(m_name);
	dest.items().insert(make_pair(lower_name, this));
	game_object *go = dynamic_cast<game_object*>(&dest);
	assert(go != NULL);
	game_object::move_to(*go);
};

void item::remove() {
	/* Don't remove if not attached to any parent */
	if (parent == NULL)
		return;

	/* Remove from the items map */
	string lower_name = utils::tolower(m_name);
	item_carrier *cur = dynamic_cast<item_carrier*>(parent);
	auto it = cur->items().find(lower_name);
	assert(it != cur->items().end());
	cur->items().erase(it);

	/* Remove as usual */
	game_object::remove();
}

void item::use(ostream& os, actor* a) {
	os << a->name() << " tried to " << random_adverb() << " use " << name() << ", but nothing happened." << endl;
}; 

item * item::copy() const {
	item *p = new item(*this);
	return p;
}

boost::property_tree::ptree item::to_ptree() const {
	using boost::property_tree::ptree;
	ptree pt = game_object::to_ptree();

	pt.put("m_volume", m_volume);
	pt.put("m_value", m_value);

	return pt;
}

void item::init(game *g, boost::property_tree::ptree tree) {
	game_object::init(g, tree);

	m_volume = tree.get<int>("m_volume");
	m_value = tree.get<int>("m_value");
}

item * item::from_ptree(game * g, boost::property_tree::ptree tree) {

	item * i = new item(
		tree.get<string>("name"),
		tree.get<string>("m_desc"),
		tree.get<int>("m_volume"),
		tree.get<int>("m_value")
	);
	i->init(g, tree);

	return i;
};

};
