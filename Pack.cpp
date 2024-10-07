#include <cassert>
#include <iostream>
#include <string>
#include <array>
#include "Pack.hpp"


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

  Pack::Pack(std::istream& pack_input){
    next = 0;
    for (int i = 0; i < PACK_SIZE; i++){
      pack_input >> cards[i];
    }
  }

  Card Pack::deal_one(){
    assert(!empty());
    return cards[next++];
  }

  void Pack::reset(){
    next = 0;
  }

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

  bool Pack::empty() const{
    if (next >= PACK_SIZE){
      return true;
    }
    else{
      return false;
    }
  }