cpp-rpg-game
============

A fairly big lab we (ansjob@kth.se and marcular@kth.se) made for the course cprog12 to create a C++ 
role playing game using classic text-commands. 
The engine is there and very extensible.

Some key features are:

* Fully customizable map (read from the file univ.xml)
* Fight system with accuracy and ranges for each weapon (making fights interesting)
* Possibility to alias commands
* Consumable items like shield boosters

Setting
=======

The setting of the game is space. You have a small space ship and travel between solar systems in the galaxy.
When you encounter other characters you can talk to them, fight them, and engage in trade with some.
The main plot is that you should try to find and kill the evil boss; "Charlie Mancrunch" because
he has kidnapped the mayor of your home town.


Compiling
=========

This was developed on Ubuntu Linux, but most resonably patched unix-like systems should run it just fine.
We use lots of C++11 features, so an up-to-date compiler is a must.

Third party libraries
=====================

We make use of boost's property tree and regular expressions, so a recent version of boost is also necessary.

When these requirements are met, compiling is simply done by using cmake:

cmake .

make 

./game


