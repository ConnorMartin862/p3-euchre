#include "Player.hpp"
#include <cassert>
#include <array>
#include <string>
#include <iostream>
#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <sstream>
using namespace std;

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy){
    if (strategy == "Simple") {
        return new Simple(name);
    } else if(strategy == "Human"){
        return new Human(name);
    }
    else{
        assert(false); 
        return nullptr;
    }
 }

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p){
    os << p.get_name();
    return os;
}

class Simple : public Player{
    private:
    string name;
    vector<Card> hand;

    public:
    Simple(const string& n) : name(n) {}
    
    //EFFECTS returns player's name
  virtual const std::string & get_name() const{
    assert(false);
  }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  virtual void add_card(const Card &c){
    assert(false);
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  virtual bool make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) const{
    assert(false);
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  virtual void add_and_discard(const Card &upcard){
    assert(false);
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  virtual Card lead_card(Suit trump){
    assert(false);
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  virtual Card play_card(const Card &led_card, Suit trump){
    assert(false);
  }

  // Maximum number of cards in a player's hand
  static const int MAX_HAND_SIZE = 5;
};

class Human : public Player{
    private:
    string name;
    vector<Card> hand;

    public:
    Human(const string& n) : name(n) {}
    //EFFECTS returns player's name
  virtual const std::string & get_name() const{
    assert(false);
  }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  virtual void add_card(const Card &c){
    assert(false);
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  virtual bool make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) const{
    assert(false);
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  virtual void add_and_discard(const Card &upcard){
    assert(false);
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  virtual Card lead_card(Suit trump){
    assert(false);
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  virtual Card play_card(const Card &led_card, Suit trump){
    assert(false);
  }

  // Maximum number of cards in a player's hand
  static const int MAX_HAND_SIZE = 5;
};