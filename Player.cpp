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
    
  virtual const std::string & get_name() const{
    return name;
  }
  virtual void add_card(const Card &c){
    assert(hand.size() < MAX_HAND_SIZE);
    hand.push_back(c);
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  virtual bool make_trump(const Card &upcard, bool is_dealer,
    int round, Suit &order_up_suit) const{
    assert(round == 1 || round == 2);
    int count1 = 0;
    int count2 = 0;
    Suit n = Suit_next(upcard.get_suit());
    if (round == 1){
      for (int i = 0; i < hand.size(); i++){
        if ((hand[i].get_suit() == upcard.get_suit() && hand[i].get_rank() >= JACK) || 
        (n == hand[i].get_suit() && hand[i].get_rank() == JACK)){
          count1++;
        }
      }
      if (count1 >= 2){
        order_up_suit = upcard.get_suit();
        return true;
      }
      else {
        return false;
      }
    }
    else{
      for (int j = 0; j < hand.size(); j++){
        if ((hand[j].get_suit() == n && hand[j].get_rank() >= JACK) || 
        (upcard.get_suit() == hand[j].get_suit() && hand[j].get_rank() == JACK)){
          count2++;
        }
      }
      if (count2 >= 1){
        order_up_suit = n;
        return true;
      }
      else if (is_dealer == true){
        order_up_suit = upcard.get_suit();
      }
      else {
        return false;
      }
    }
  }

  virtual void add_and_discard(const Card &upcard){
    assert(hand.size() >= 1);
    add_card(upcard);
    Card remove = hand[0];
    int r = 0;
    for (int i = 1; i < hand.size(); i++){
      if (Card_less(hand[i], remove, upcard.get_suit())){
        remove = hand[i];
        r = i;
      }
    }
    hand.erase(hand.begin() + r);
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  virtual Card lead_card(Suit trump){
    assert(hand.size() >= 1);
    assert(false);
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  virtual Card play_card(const Card &led_card, Suit trump){
    assert(hand.size() >= 1);
    assert(false);
  }

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
    return name;
    assert(false);
  }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
  virtual void add_card(const Card &c){
    assert(hand.size() < MAX_HAND_SIZE);
    hand.push_back(c);
  }

  //REQUIRES round is 1 or 2
  //MODIFIES order_up_suit
  //EFFECTS If Player wishes to order up a trump suit then return true and
  //  change order_up_suit to desired suit.  If Player wishes to pass, then do
  //  not modify order_up_suit and return false.
  virtual bool make_trump(const Card &upcard, bool is_dealer,
  int round, Suit &order_up_suit) const{
    assert(round == 1 || round == 2);
    assert(false);
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  virtual void add_and_discard(const Card &upcard){
    assert(hand.size() >= 1);
    assert(false);
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  virtual Card lead_card(Suit trump){
    assert(hand.size() >= 1);
    assert(false);
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  virtual Card play_card(const Card &led_card, Suit trump){
    assert(hand.size() >= 1);
    assert(false);
  }

  // Maximum number of cards in a player's hand
  static const int MAX_HAND_SIZE = 5;
};