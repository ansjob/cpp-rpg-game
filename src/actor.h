#ifndef ACTOR_H
#define ACTOR_H

#include <boost/property_tree/ptree.hpp>
#include <string>
#include <sstream>
#include <map>

#include "item.h"
#include "weapon.h"
#include "shield.h"
#include "game_object.h"
#include "item_carrier.h"

using namespace std;

namespace rpg {

class solar_system;

/**
 *	An actor is anything that can move on its own, have weapons and shields
	equipped and items in their 'cargo hull'.
 */
class actor : public game_object, public item_carrier {
protected:
	int m_hp;
	weapon * cur_weapon;
	shield * cur_shield;
	multimap<string, item*> m_items;

public:

	/**
	 *	Constructs a generic actor with some default values for cargo hull size, hit points etc.
	 * The use of this constructor directly is discouraged.
	 * Instantiate from this class and delegate to this constructor.
	 */
	actor(string name, string desc);
	bool selling;
	int credits;

	/**
	 *	Where the actor is currently located.
	 */
	virtual solar_system & location();

	/**
	 *	Moves the actor to the target solar system.
	 */
	virtual void move_to(solar_system &dest);
	virtual void remove();

	/**
	 *	@return What the actor currently has to say...
	 */ 
	virtual string talk();

	virtual int hp() const;
	virtual int max_hp() const;
	virtual int shield_hp() const;
	virtual int max_cargo() const;
	virtual int max_shield() const;
	virtual int avail_cargo() const;

	/**
	 *	Kills the character, drops it's items, and calls delete on the character. 
	 */
	virtual void die(ostream &os);
	virtual void set_weapon(weapon* w);
	virtual void set_shield(shield* w);
	virtual weapon* current_weapon() const;
	virtual shield* current_shield() const;

	/**
	 *	Drops the currently equipped weapon into the current solar system
	 */
	void drop_weapon();
	/**
	 *	Drops the currently shield weapon into the current solar system
	 */
	void drop_shield();

	/**
	 *	Deletes the current weapon completely from the game and calls it's destructor.
	 */
	void delete_weapon();

	/**
	 * Tries to attack if the actor has a weapon,
	 * prints the 'action' information to the ostream.
	 */
	virtual void attack(ostream& os, actor* target);

	/**
	 * Buy an item from this actor.
	 *
	 * @param os Where to print messages about the purchase.
	 * @param buyer The actor to transfer the item to.
	 * @param item_no The index in the items[] field of the item to purchase.
	 */
	virtual int buy(ostream& os, actor* buyer, unsigned int item_no);

	/**
	 *	Take damage (possibly from a specified actor).
	 *
	 *	@param attacker Pointer to damaging actor, can be NULL(!)
	 *	@param damage Amount of damage to take
	 */
	virtual void take_damage(ostream& os, actor* attacker, int damage);

	virtual multimap<string, item*> & items();
	virtual const multimap<string, item*> & items() const;

	virtual boost::property_tree::ptree to_ptree() const; 

	virtual void init(game * g, boost::property_tree::ptree);

	virtual void after_tick(ostream& os);
};
};

#endif
