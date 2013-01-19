#include <iostream>

#include "game.h"
#include "player.h"


using namespace std;
using namespace rpg;


int main(int argc, char *argv[]) {

	//To make the game funner!
//	srandom(time(NULL));

	game g(cin, cout);

	if (argc == 2)
		g.load_universe(argv[1]);
	else {
		g.load_universe();
		g.print_intro();
	}

	return g.run();
}
