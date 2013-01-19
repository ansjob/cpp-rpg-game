#include "adverb.h"
#include "player.h"
#include "initializers.h"
#include "border_system.h"

using namespace std;

namespace rpg {

extern initializer initializers;

border_system::border_system(string n, string d) : solar_system(n, d) {}

bool border_system::accepts(player& player) {
	return player.current_weapon() != NULL && player.current_shield() != NULL;
}

void border_system::print_deny_message(ostream& os) {
	os << "One does not simply enter " << name() << " without means to protect oneself." << endl;
}

void border_system::print_enter_message(ostream& os) {
	os << "You " << random_adverb() << " enter " << m_name << endl;
}


border_system* border_system::from_ptree(game* g, boost::property_tree::ptree tree) {

	using boost::property_tree::ptree;

	string name = tree.get<string>("name");
	border_system * res = new border_system(name);

	//Re-use the solar-system init for actors/items
	res->init(g, tree);

	return res;
}

};
