#ifndef WEAPON_H
#define WEAPON_H

#include <string>

#include "item.h"

using namespace std;

namespace rpg {

class solar_system;
class actor;

class weapon : public item {

protected:
	double m_accuracy;
	int m_min_damage, m_max_damage;

public:
	weapon(
		string n = "Dummy weapon",
		string desc = "Dummy weapon description",
		int vol = 0,
		int val = 0,
		int min_damage = 0,
		int max_damage = 0,
		double accuracy = 0.0) 
		:
		item(n, desc, vol, val),
		m_accuracy(accuracy),
		m_min_damage(min_damage),
		m_max_damage(max_damage) 
		{}

	virtual string desc() const;

	virtual void use(ostream& os, actor*);

	virtual void attack(ostream& os, actor * target);

	virtual double accuracy() const;
	virtual int min_damage() const;
	virtual int max_damage() const;
	virtual item * copy() const;

	virtual boost::property_tree::ptree to_ptree() const;
	static weapon * from_ptree(game * g, boost::property_tree::ptree);
	virtual void init(game * g, boost::property_tree::ptree);
};

};

#endif
