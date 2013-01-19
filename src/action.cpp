#include <sstream>

#include "action.h"

using namespace std;
namespace rpg {

	action::action(game& ref) : g(ref) {};
	action::~action() {};

	string action::item_regexp(string optional_prefix) {
		if (optional_prefix == "") {
			return "[\\s]*((?:(?:[\\w|'] [\\w|'])|[\\w|']| \\(|\\))+)(?:\\s)*";
		}
		stringstream ss;
		ss << "[\\s]*(" << optional_prefix << ")?((?:(?:[\\w|'] [\\w|'])|[\\w|']| \\(|\\))+)(?:\\s)*";
		return ss.str();
	};

};
