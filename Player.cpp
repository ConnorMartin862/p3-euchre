#include "Player.hpp"
#include <cassert>
#include <array>
#include <string>
#include <iostream>

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy){
    assert(false);
}

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p){
    assert(false);
}