#include <sstream>
#include <string>

#include "utils.h"
#include "shield.h"
#include "adverb.h"
#include "player.h"
#include "initializers.h"
#include "solar_system.h"

using namespace std;
namespace rpg {

extern initializer initializers;

void shield::use(ostream& os, actor* a) {
	shield * cur_equipped = a->current_shield();
	if (cur_equipped != NULL) {
		int e_v = cur_equipped->volume();
		if (e_v > a->avail_cargo() + this->volume()) {
			os << "There is not enough room in your cargo to make the shield swap." << endl;
			return;
		}
		else {
			a->items().insert(make_pair(utils::tolower(cur_equipped->name()),cur_equipped));
			a->set_shield(NULL);
		}
	}

	equipped = true;
	a->set_shield(this);
	for (auto it = a->items().begin(); it != a->items().end(); ++it) {
		if (it->second == this) {
			a->items().erase(it);
			break;
		}
	}
	os << "Equipped " << name() << " " << random_adverb() << endl; 
}; 

int shield::hp() const {
	return m_cur;
}

int shield::recharge_rate() const {
	return m_recharge_rate;
}

int shield::recharge_amount() const {
	return m_recharge_amount;
}

void shield::tick(ostream &os) {
	/* Don't recharge when not equipped, or if fully charged */
	if (!equipped || m_cur == m_max)
		return;

	/* If recharge time has passed */
	if (until_recharge == 0) {
		m_cur = min(m_max, m_cur + m_recharge_amount);
		until_recharge = m_recharge_rate;
	}
	until_recharge -= 1;
}

void shield::recharge(ostream &os, int amount) {
	amount = min(m_max, amount);
	os << "Shield " << random_adverb() << " recharged " << amount
		<< "!\n";
	m_cur = min(m_cur + amount, m_max);
}

void shield::take_damage(ostream &os, int damage) {
	int shield_damage = min(damage, m_cur);
	/* Take damage */
	m_cur -= shield_damage;

	/* Print messages */
	os << "Shield " << random_adverb() << " absorbed " << shield_damage << " damage." << endl;
	if (m_cur == 0) {
		os << "Shields are down!" << endl;
	}

	/* Reset recharge "timer" */
	until_recharge = m_recharge_rate;
}

int shield::max() const {
	return m_max;
}

string shield::desc() const {
	stringstream ss;

	ss << m_desc << "\n";
	ss << "Properties:\n";
	ss << "\tCharge: " << hp() << "/" << max() << "\n";
	ss << "\tRecharge rate: " << recharge_amount() << " every " << recharge_rate() << " turn(s)\n";

	if (hp() != max()) {
		ss << "Turns until next recharge: " << (until_recharge + 1) << "\n";
	}

	return ss.str();
}

void shield::unequip() {
	equipped = false;
};

item * shield::copy() const {
	item *p = new shield(*this);
	return p;
};

using boost::property_tree::ptree;

ptree shield::to_ptree() const {
	using boost::property_tree::ptree;
	ptree pt = item::to_ptree();

	pt.put("equipped", equipped);
	pt.put("m_recharge_rate", m_recharge_rate);
	pt.put("m_recharge_amount", m_recharge_amount);
	pt.put("m_max", m_max);
	pt.put("m_cur", m_cur);
	pt.put("m_until_recharge", until_recharge);

	return pt;
};

shield * shield::from_ptree(game * g, ptree tree) {
	shield * s = new shield;
	s->init(g, tree);
	return s;
};

void shield::init(game * g, ptree tree) {
	item::init(g, tree);

	equipped = 			tree.get<bool>("equipped");
	m_recharge_rate = 	tree.get<int>("m_recharge_rate");
	m_recharge_amount = tree.get<int>("m_recharge_amount");
	m_max =				tree.get<int>("m_max");
	m_cur =				tree.get<int>("m_cur");
	until_recharge =	tree.get<int>("m_until_recharge");
};

};
