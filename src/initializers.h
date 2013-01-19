#ifndef INIT_H
#define INIT_H

#include <map>
#include <string>
#include <functional>

using namespace std;

namespace rpg {

	class game_object;
	class game;

	struct initializer {
		map<
			string, 
			function<game_object*(game*, boost::property_tree::ptree)>
		> m_initializers;

		initializer();

		function<game_object*(game*, boost::property_tree::ptree)> operator[] (const string) const;

	};

};
#endif
