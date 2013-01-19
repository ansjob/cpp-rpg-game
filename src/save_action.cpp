#include "game.h"
#include "adverb.h"
#include "save_action.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace std;

namespace rpg {

	save_action::save_action(game& ref): action(ref) {};

	int save_action::operator()(ostream &os, string args) {
		stringstream ss(args);
		string filename;
		if (ss >> filename) {
			using boost::property_tree::ptree;
			ptree pt = g.universe->to_ptree();
			ptree save_file;
			save_file.add_child(typeid(game_object).name(), pt);
			write_xml(filename, save_file);
			os << "Game saved..." << endl;
		}
		else {
			os << "No file name given" << endl;
		}
		return 0;
	};

	ostream& save_action::print_short_help(ostream& os) {
		os << "Saves the game to be resumed later";
		return os;
	}

	ostream& save_action::print_long_help(ostream& os) {
		os << "The save command saves the game to file. Example use: save mygame.savefile.\n"
		<< "To restart the game run the game with the name of the savefile as a parameter: ./game mygame.savefile";
		return os;
	}
};
