#ifndef GALAXY_H
#define GALAXY_H

#include <string>
#include <boost/property_tree/ptree.hpp>

#include "game_object.h"

using namespace std;

namespace rpg {

class galaxy : public game_object {
private:

public:
	galaxy(string name) : game_object(name) {}
	static game_object * from_ptree(game *g, boost::property_tree::ptree tree);

	virtual void init(game*, boost::property_tree::ptree);
};

};

#endif
