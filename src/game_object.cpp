#include <typeinfo>
#include <iostream>

#include "game_object.h"
#include "initializers.h"

using namespace std;

namespace rpg {

extern initializer initializers;

game_object::game_object(string name, string desc) : parent(NULL), m_name(name), m_desc(desc), id(0) {
}

void game_object::move_to(game_object &ref) {

	/* Delete us from previous parent (if exists). */
	game_object::remove();

	/* Add us to new parent */
	ref.children.insert(this);
	parent = &ref;

};

void game_object::remove() {
	/* Do nothing if no parent. */
	if (parent == NULL)
		return;

	int ret = parent->children.erase(this);
	assert(ret == 1);

	/* Set parent to NULL! */
	parent = NULL;
};

game_object::~game_object() {
	for (auto childp : children) {
		delete childp;
	}
};

using boost::property_tree::ptree;

ptree game_object::to_ptree() const {
	ptree pt;

	/* Add fields */
	pt.put("name", name());
	pt.put("m_desc", m_desc);
	pt.put("id", (unsigned long)this);

	/* Add children */
	ptree childs;
	for (game_object * child : children) {
		childs.add_child(typeid(*child).name(), child->to_ptree());
	}
	pt.add_child("children", childs);

	/* Finalize result */
	return pt;
};

game_object * game_object::from_ptree(game* g, ptree tree) {
	game_object * obj = new game_object;

	obj->init(g, tree);

	return obj;
};

void game_object:: init(game *g, ptree tree) {

	this->m_name = tree.get<string>("name");
	this->m_desc = tree.get<string>("m_desc");
	this->id = tree.get<unsigned long>("id");

	ptree childs = tree.get_child("children");
	for (auto it = childs.begin(); it != childs.end(); ++it) {
		game_object * child = initializers[it->first](g, it->second);
		child->move_to(*this);
	}

};

};
