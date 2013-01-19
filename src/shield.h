#ifndef SHIELD_H
#define SHIELD_H

#include <string>
#include "item.h"

using namespace std;

namespace rpg {

class solar_system;
class actor;

class shield : public item {

protected:
	bool equipped;
	int m_recharge_rate;
	int m_recharge_amount;
	int m_max;
	int m_cur;
	int until_recharge;

public:
	shield(
		string n = "Dummy shield",
		string desc = "Dummy shield description",
		int vol = 0,
		int val = 0,
		int recharge_rate = 0,
		int recharge_amount = 0,
		int max = 0)
		:
		item(n, desc, vol, val),
		equipped(false),
		m_recharge_rate(recharge_rate),
		m_recharge_amount(recharge_amount),
		m_max(max),
		m_cur(max),
		until_recharge(0)
		{}

	/**
	 * Equips the shield (on actor a)
	 * @param a The actor using the item.
	 */
	virtual void use(ostream& os, actor*);
	virtual void take_damage(ostream &os, int damage);
	virtual void recharge(ostream &os, int amount);
	virtual void tick(ostream &os);
	virtual string desc() const;
	virtual void unequip();
	
	int hp() const;
	int max() const;
	int recharge_rate() const;
	int recharge_amount() const;
	virtual item *copy() const;

	virtual boost::property_tree::ptree to_ptree() const;

	static shield * from_ptree(game *, boost::property_tree::ptree);
	virtual void init(game *, boost::property_tree::ptree);

};
};

#endif
