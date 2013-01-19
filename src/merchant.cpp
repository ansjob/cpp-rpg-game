#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "item.h"
#include "shield.h"
#include "adverb.h"
#include "merchant.h"
#include "initializers.h"

using namespace std;

namespace rpg {

extern initializer initializers;

merchant::~merchant() {
	for (item * i : possible_items) {
		delete i;
	}
}

merchant::merchant(string name, string desc, vector<item *> possible) : npc(name, desc), possible_items(possible) {
	selling = true;
};

string merchant::talk() {
	stringstream os;
	os << name() << " (" << random_adverb() << "): I have the following items in stock for you:" << endl;
	int i = 0;
	os << "\t" << right << setw(5) << "No. " <<
	left << setw(30) << "Item name" << 
	setw(20) << "Price" << endl;

	for (auto it : items()) {
		os << "\t" << right << setw(3) << i++ << ". " <<
		left << setw(30) << it.second->name() << 
		setw(20) << it.second->value() << endl;
	}
	os << endl;

	return os.str();
};

void merchant::tick(ostream &os) {
	/* Do basic NPC stuff */
	npc::tick(os);

	if (m_hp == 0) return;

	/* Restock items at random times */
	if (items().size() < 10 && (random() % 100) < 10) {
		add_random_item();
	}
};

void merchant::add_random_item() {
	if (possible_items.size() == 0)
		return;

	item* new_item = possible_items[random()%possible_items.size()]->copy();
	new_item->move_to(*this);
};

boost::property_tree::ptree merchant::to_ptree() const {
	using boost::property_tree::ptree;
	ptree pt = npc::to_ptree();


	ptree possible_tree;
	for (item * pitem : possible_items) {
		possible_tree.add_child(typeid(*pitem).name(), pitem->to_ptree());
	}
	pt.add_child("possible_items", possible_tree);

	return pt;
};

using boost::property_tree::ptree;
extern initializer initializers;

merchant * merchant::from_ptree(game * g, ptree tree) {

	vector<item*> possible_items;

	ptree itm_tree = tree.get_child("possible_items");

	for (pair<string, ptree> itm_entry : itm_tree) {
		possible_items.push_back((item*)initializers[itm_entry.first](g, itm_entry.second));
	}

	merchant * m = new merchant(tree.get<string>("name"), tree.get<string>("m_desc"), possible_items);

	m->init(g, tree);

	return m;

};

};
