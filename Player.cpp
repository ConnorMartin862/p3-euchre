#include "Player.hpp"
#include <cassert>
#include <array>
#include <string>
#include <iostream>
#include "Card.hpp"
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over


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
    assert(hand.size() <= MAX_HAND_SIZE);
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

    // Round 1 logic
    if (round == 1) {
        for (int i = 0; i < hand.size(); i++) {
            if ((hand[i].get_suit() == upcard.get_suit() && hand[i].get_rank() >= JACK) || 
                (n == hand[i].get_suit() && hand[i].get_rank() == JACK)) {
                count1++;
            }
        }
        if (count1 >= 2) {
            order_up_suit = upcard.get_suit();
            return true;
        }
        return false;
    }

    // Round 2 logic
    if (round == 2) {
        for (int j = 0; j < hand.size(); j++) {
            if ((hand[j].get_suit() == n && hand[j].get_rank() >= JACK) || 
                (upcard.get_suit() == hand[j].get_suit() && hand[j].get_rank() == JACK)) {
                count2++;
            }
        }
        if (count2 >= 1) {
            order_up_suit = n;
            return true;
        }
    }

    // If player is dealer
    if (is_dealer) {
        order_up_suit = upcard.get_suit();
        return true;
    }

    return false;
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
    int index = -1;
    Card lead;
    for (int i = 0; i < hand.size(); i++){
      if ((hand[i].is_trump(trump) == false) && (hand[i].is_left_bower(trump) == false)){
        if (index == -1 || Card_less(hand[index] ,hand[i] ,trump)){
          index = i;
        }
      }
    }
    if (index == -1){
      index = 0;
      for (int j = 0; j < hand.size(); j++){
        if (Card_less(hand[index], hand[j], trump)){
          index = j;
        }
      }
      lead = hand[index];
      hand.erase(hand.begin() + index);
      return lead;
    }
    else {
      lead = hand[index];
      hand.erase(hand.begin() + index);
      return lead;
    }
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  virtual Card play_card(const Card &led_card, Suit trump){
    assert(hand.size() >= 1);
    int index = -1;
    Card play;
    for (int i = 0; i < hand.size(); i++){
      if (hand[i].get_suit() == led_card.get_suit()){
        if (index == -1 || Card_less(hand[index] ,hand[i] , led_card, trump)){
          index = i;
        }
      }
    }
    if (index == -1){
      index = 0;
      for (int j = 0; j < hand.size(); j++){
        if (Card_less(hand[j], hand[index], led_card, trump)){
          index = j;
        }
      }
      play = hand[index];
      hand.erase(hand.begin() + index);
      return play;
   }
   else {
    play = hand[index];
      hand.erase(hand.begin() + index);
      return play;
   }
  }
  static const int MAX_HAND_SIZE = 5;
};

class Human : public Player{
    private:
    string name;
    vector<Card> hand;
    void print_hand() const {
  for (size_t i=0; i < hand.size(); ++i)
    cout << "Human player " << name << "'s hand: "
         << "[" << i << "] " << hand[i] << "\n";
}

    public:
    Human(const string& n) : name(n) {}
    //EFFECTS returns player's name
  virtual const std::string & get_name() const{
    return name;
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
    print_hand();
    cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
    string s;
    cin >> s;
    if (s != "pass") {
      order_up_suit = string_to_suit(s);
      return true;
    }
    else{
      return false;
    }
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Player adds one card to hand and removes one card from hand.
  virtual void add_and_discard(const Card &upcard){
    assert(hand.size() >= 1);
    hand.push_back(upcard);
    sort(hand.begin(), hand.end());
    print_hand();
    cout << "Discard upcard: [-1]\n";
    cout << "Human player " << name << ", please select a card to discard:\n";
    int remove;
    cin >> remove;
    if (remove == -1){
      for (int i = 0; i < hand.size(); i++){
        if(operator==(hand[i], upcard)){
          hand.erase(hand.begin() + i);
        }
      }
    }
    else {
      hand.erase(hand.begin() + remove);
    }
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Leads one Card from Player's hand according to their strategy
  //  "Lead" means to play the first Card in a trick.  The card
  //  is removed the player's hand.
  virtual Card lead_card(Suit trump){
    assert(hand.size() >= 1);
    sort(hand.begin(), hand.end());
    print_hand();
    cout << "Human player " << name << ", please select a card:\n";
    int lead;
    cin >> lead;
    Card l = hand[lead];
    hand.erase(hand.begin() + lead);
    return l;
  }

  //REQUIRES Player has at least one card
  //EFFECTS  Plays one Card from Player's hand according to their strategy.
  //  The card is removed from the player's hand.
  virtual Card play_card(const Card &led_card, Suit trump){
    assert(hand.size() >= 1);
    sort(hand.begin(), hand.end());
    print_hand();
    cout << "Human player " << name << ", please select a card:\n";
    int play;
    cin >> play;
    Card p = hand[play];
    hand.erase(hand.begin() + play);
    return p;
  }

  // Maximum number of cards in a player's hand
  static const int MAX_HAND_SIZE = 5;
};

Player * Player_factory(const std::string &name, 
                        const std::string &strategy) {
  if (strategy == "Simple") {
    return new Simple(name);
  }
  else if (strategy == "Human") {
    return new Human(name);
  }
  else { 
    assert(false);
    return nullptr;
  }
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
    os << p.get_name();
    return os;
}