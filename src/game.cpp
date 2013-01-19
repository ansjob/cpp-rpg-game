#include <boost/property_tree/xml_parser.hpp>
#include <fstream>
#include <sstream>

#include "boss.h"
#include "game.h"
#include "item.h"
#include "miner.h"
#include "hunter.h"
#include "police.h"
#include "adverb.h"
#include "galaxy.h"
#include "player.h"
#include "actions.h"
#include "merchant.h"
#include "solar_system.h"
#include "border_system.h"
#include "poisoned_system.h"
#include "consumable_item.h"
#include "sanctuary_system.h"

#define PROMPT "> "

using namespace std;

namespace rpg {

game::game(istream& in, ostream& out):
	is(in), 
	os(out), 
	m_inv(*this),
	m_actions(load_commands()),
	m_parser(&m_inv, m_actions, os),
	exit_issued(false),
	m_player(NULL) {
};

int game::run() {
	while (is && !exit_issued) {
		int ticks;
		os << m_player->location().name() << PROMPT;
		string line;
		getline(is, line, '\n');
		ticks = m_parser.parse_exec(line);
		while (ticks-- > 0 && m_player->hp() != 0) {
			universe->on_tick(os);
			os << m_player->location().echo.str();
		}
	}
	os << "\nThank you for playing the game so " << random_adverb() << "!"<< endl;
	return 0;
};

void game::load_universe(const string filename) {
	load_savefile(filename);
};

map<string, action*> game::load_commands() {
		map<string, action*> m;

		move_action *move = new move_action(*this);
		m["move"] = move;
		m["mv"] = new alias_action(*this, "move", move);

		m["help"] = new help_action(*this);

		quit_action *quit = new quit_action(*this);
		m["quit"] = quit;
 		m["exit"] = new alias_action(*this, "quit", quit);

		scan_action *scan = new scan_action(*this);
		m["scan"] = scan;
		m["ls"] = new alias_action(*this, "scan", scan);

		m["talk"] = new talk_action(*this);

		m["take"] = new take_action(*this);

		m["drop"] = new drop_action(*this);

		m["inventory"] = new inventory_action(*this);

		m["inv"] = new alias_action(*this, "inventory", m["inventory"]);

		m["use"] = new use_action(*this);

		m["attack"] = new attack_action(*this);

		m["buy"] = new buy_action(*this);

		m["wait"] = new wait_action(*this);

		m["alias"] = new create_alias_action(*this);

		m["save"] = new save_action(*this);

		m["load"] = new load_action(*this);

		return m;
};

map<string, action*> & game::actions() {
	return m_actions;
};

void game::exit() {
	exit_issued = true;
};

//Igoring rule of 3 because it makes no sense to copy-assign a game instance
game::~game() {
	for (auto ap : m_actions) {
		delete ap.second;
	}

	delete universe;
};

void game::load_savefile(const string filename) {

	using boost::property_tree::ptree;

	ptree pt;
	read_xml(filename, pt);

	universe = game_object::from_ptree(this, pt.get_child
		(typeid(game_object).name()));

	os << "Loaded game " << endl;
};

void game::print_intro() {
	os << universe->desc() << endl;
};

};
