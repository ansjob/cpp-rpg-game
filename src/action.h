#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <iostream>

using namespace std;

namespace rpg {

class game;

/**
 *	An action represents a command that can be issued by the user from the CLI.
 */
class action {
private:

protected:
	game &g;

public:

	/**
	 *	Construct the functor to be used for this command.
	 *	@param ref The game instance to run the command on.
	 */
	action(game &ref);
	virtual ~action();

	/**
	 * Runs the command on the game with which this command was instantiated.
	 * The command should print a newline to the ostream when it is finished,
	 * so the prompt ends up on a new line.
	 */
	virtual int operator()(ostream &os, string args = "") = 0;

	/**
	 * Prints a short help message. No endline included.
	 */
	virtual ostream& print_short_help(ostream& os) = 0;
	/**
	 * Prints a longer help message. No endline included.
	 */
	virtual ostream& print_long_help(ostream& os) = 0;

	/**
	 *		Utility function for actions to create regular expression patterns.
	 *		Called with the optional prefix set to "from" will create a pattern
	 *		that matches strings like "from olle", "olle", or "from olle the rebel (hostile)".
	 *
	 *		@param optional_prefix The optional prefix. "from" in the example above.
	*/
	static string item_regexp(string optional_prefix = "");
};

};
#endif
