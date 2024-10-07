#include <cassert>
#include <iostream>
#include <array>
#include <string>
#include <array>
#include "Pack.hpp"

// EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on. 
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  // NOTE: The pack is initially full, with no cards dealt.
  Pack::Pack(){
    next = 0;
    int order = 0;
    for (int i = SPADES; i <= DIAMONDS; i++){
      for (int j = NINE; j <= ACE; j++){
        cards[order] = Card(static_cast<Rank>(j), static_cast<Suit>(i));
        order++;
      }
    }
  }

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  // NOTE: The pack is initially full, with no cards dealt.
  Pack::Pack(std::istream& pack_input){
    next = 0;
    for (int i = 0; i < PACK_SIZE; i++){
      pack_input >> cards[i];
    }
  }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one(){
    assert(!empty());
    return cards[next++];
  }

  // EFFECTS: Resets next index to first card in the Pack
  void Pack::reset(){
    next = 0;
  }

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
  void Pack::shuffle(){
    for (int i = 0; i < 7; i++){
      std::array<Card, 12> top;
      std::array<Card, 12> bottom;
      for (int j = 0; j < 12; j++){
        top[j] = cards[j];
        bottom[j] = cards[j+12];
      }
      for (int k = 0; k < 12; k++){
        cards[2*k] = bottom[k];
        cards[2*k+1] = top[k];
      }
    }
    reset();
  }

  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const{
    if (next >= PACK_SIZE){
      return true;
    }
    else{
      return false;
    }
  }