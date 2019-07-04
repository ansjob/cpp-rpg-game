#ifndef MERCHANT_H
#define MERCHANT_H

#include <string>
#include <sstream>
#include <vector>

#include "npc.h"
#include "item.h"

using namespace std;

namespace rpg {

class merchant : public npc {
protected:
	vector<item *> possible_items;
	virtual void add_random_item();

public:
	merchant(string name, string desc, vector<item*> possible_items);
	virtual ~merchant();

	virtual void tick(ostream &os);

	/** Returns a formatted list of the things this merchant has for sale */
	virtual string talk();

	virtual boost::property_tree::ptree to_ptree() const;

	static merchant * from_ptree(game * g, boost::property_tree::ptree);

};
};

#endif
