#include <functional>
#include <boost/property_tree/ptree.hpp>

#include "initializers.h"

#include "game_object.h"
#include "item.h"
#include "consumable_item.h"
#include "weapon.h"
#include "shield.h"
#include "galaxy.h"
#include "solar_system.h"
#include "poisoned_system.h"
#include "shield_booster.h"
#include "sanctuary_system.h"
#include "border_system.h"
#include "player.h"
#include "npc.h"
#include "merchant.h"
#include "hunter.h"
#include "police.h"
#include "boss.h"
#include "miner.h"
#include "mayor.h"
#include <stdexcept>
#include <sstream>

namespace rpg {

initializer::initializer() {
	m_initializers[typeid(game_object).name()] = game_object::from_ptree;
	m_initializers[typeid(galaxy).name()] = galaxy::from_ptree;
	m_initializers[typeid(solar_system).name()] = solar_system::from_ptree;
	m_initializers[typeid(border_system).name()] = border_system::from_ptree;
	m_initializers[typeid(poisoned_system).name()] = poisoned_system::from_ptree;
	m_initializers[typeid(sanctuary_system).name()] = sanctuary_system::from_ptree;

	m_initializers[typeid(item).name()] = item::from_ptree;
	m_initializers[typeid(shield_booster).name()] = shield_booster::from_ptree;
	m_initializers[typeid(weapon).name()] = weapon::from_ptree;
	m_initializers[typeid(shield).name()] = shield::from_ptree;

	m_initializers[typeid(merchant).name()] = merchant::from_ptree;
	m_initializers[typeid(player).name()] = player::from_ptree;
	m_initializers[typeid(hunter).name()] = hunter::from_ptree;
	m_initializers[typeid(police).name()] = police::from_ptree;
	m_initializers[typeid(mayor).name()] = mayor::from_ptree;
	m_initializers[typeid(miner).name()] = miner::from_ptree;
	m_initializers[typeid(boss).name()] = boss::from_ptree;
	m_initializers[typeid(npc).name()] = npc::from_ptree;
};

function<game_object*(game*, boost::property_tree::ptree)> initializer::operator[] (const string key) const {
	auto it = m_initializers.find(key);
	if (it == m_initializers.end()) {
		stringstream ss;
		ss << "Unexpected initializer key: " << key;
		throw runtime_error(ss.str());
	}
	return it->second;
};

/* Global initializers variable */
initializer initializers;

}
