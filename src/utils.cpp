#include <locale>
#include <string>

#include "utils.h"

using namespace std;

namespace rpg {

namespace utils {

string tolower(const string& str) {
	string final = str;
	for (char &c : final) {
		c = std::tolower(c);
	};
	return final;
};
};

};
