cpp-rpg-game
============

A small lab we made for the course cprog12 to create a C++ role playing game using classic text-commands. The engine is there and very extensible.

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


