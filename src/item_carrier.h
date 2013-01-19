#ifndef ITEM_CARRIER_H
#define ITEM_CARRIER_H

#include <map>
#include <string>

#include "item.h"

using namespace std;

namespace rpg {

/**
 *	A class/interface of objects that carries items in some way.
 */
class item_carrier {
public:
	virtual multimap<string, item *> & items() = 0;
	virtual const multimap<string, item *> & items() const = 0;
};

};

#endif
