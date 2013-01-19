#include <vector>

#include "adverb.h" 

namespace rpg {
	vector<string> adverbs = {
		"boldly",
		"swiftly",
		"eagerly",
		"happily",
		"utterly",
		"hazardly",
		"strongly",
		"timidly",
		"cowardly",
		"angrily",
		"mildly",
		"pleasantly",
		"elegantly",
		"lazily",
		"jealously",
		"carefully",
		"correctly",
		"loudly",
		"quickly",
		"stealthily",
		"intentionally",
		"finally",
		"boastfully",
		"adventurously",
		"smoothly",
		"quizzically",
		"mockingly",
		"swiftly",
		"obnoxiously",
		"furiously",
		"wholeheartedly",
		"simply",
		"gradually",
		"rambunctiously",
		"sneakliy"
	
	};

	string random_adverb() {
		return adverbs[random()%adverbs.size()];
	};
};
