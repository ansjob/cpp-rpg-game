#include <sstream>
#include <stdexcept>

#include "galaxy.h"
#include "solar_system.h"
#include "initializers.h"

using namespace std;
using boost::property_tree::ptree;
namespace rpg {

extern initializer initializers;

game_object * galaxy::from_ptree(game *g, boost::property_tree::ptree tree) {

	string name = tree.get<string>("name");
	galaxy * result = new galaxy(name);

	result->init(g, tree);

	return result;
};

void galaxy::init(game * g, boost::property_tree::ptree tree) {

	//Call to super first!
	game_object::init(g, tree);


	//Let's connect the solar systems (this will run in O(n^3), but that's OK!)
	for (game_object * child : children) {
		solar_system * as_system = dynamic_cast<solar_system*>(child);
		if (child != NULL) {

			//Now we need to find this solar system in the ptree, and it's neighbours
			for (pair<string, ptree> tree_entry : tree.get_child("children")) {
				if (tree_entry.second.get<string>("name") == child->name()) {
					ptree neighbours_tree = tree_entry.second.get_child("neighbours");
					for (pair<string, ptree> neighbour_entry : neighbours_tree) {
						//Looking for the neighbour
						for (game_object * c : children) {
							solar_system* c_sys = dynamic_cast<solar_system*>(c);
							if (c_sys != NULL && c_sys->name() == neighbour_entry.second.get<string>("system-name")) {
								as_system->neighbours.insert({
									neighbour_entry.second.get<string>("direction"),
									c_sys
								});
							} else if (c_sys == NULL) {
								stringstream ss;
								ss << "Non-solar-system in galaxy! " << c->name() << " " << typeid(*c).name();
								throw runtime_error(ss.str());
							}
						}
					}
					break; // Look for neighbours of the next system
				}
			}
		} else {
			throw runtime_error("Galaxy contained something that was not a solar system!");
		}
	}
};

};
