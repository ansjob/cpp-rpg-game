#include "game.h"
#include "adverb.h"
#include "load_action.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace std;

namespace rpg {

	load_action::load_action(game& ref): action(ref) {};

	int load_action::operator()(ostream &os, string args) {
		stringstream ss(args);
		string filename;
		if (ss >> filename) {
			using boost::property_tree::ptree;
			delete g.universe;
			g.load_universe(filename);
		}
		else {
			os << "No file name given" << endl;
		}
		return 0;
	};

	ostream& load_action::print_short_help(ostream& os) {
		os << "Loads a previously saved game";
		return os;
	}

	ostream& load_action::print_long_help(ostream& os) {
		os << "The load command loads the game from file. Example use: load mygame.loadfile.\n"
		<< "To save a game to load later, type 'save [filename]'.";
		return os;
	}
};
