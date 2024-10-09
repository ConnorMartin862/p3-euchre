#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
    Player * human = Player_factory("MAN", "Human");
    ASSERT_EQUAL("MAN", human->get_name());
    delete human;
}

TEST(test_player_insertion) {
  Player * human = Player_factory("Jack", "Human");
  ostringstream h;
  h << * human;
  ASSERT_EQUAL(h.str(), "Jack");

  Player * may = Player_factory("May", "Simple");
  ostringstream s;
  s << *may;
  ASSERT_EQUAL(s.str(), "May");

  delete human;
  delete may;
}
TEST(add_discard_lead_card){
    Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, DIAMONDS));
  bob->add_card(Card(QUEEN, CLUBS));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(ACE, SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(NINE, CLUBS) // upcard
  );
  Player * bob2 = Player_factory("Bob", "Simple");
  bob2->add_card(Card(NINE, DIAMONDS));
  bob2->add_card(Card(TEN, DIAMONDS));
  bob->add_card(Card(QUEEN, CLUBS));
  bob2->add_card(Card(KING, HEARTS));
  bob2->add_card(Card(ACE, SPADES));
  Card card_led = bob->lead_card(HEARTS);
  Card card_led2 = bob2->lead_card(HEARTS);
  // Verify the card Bob selected to lead
  Card ace_spades(ACE, SPADES);
  Card ace_spades2(ACE, SPADES);
  ASSERT_EQUAL(card_led, ace_spades);
  ASSERT_EQUAL(card_led2, ace_spades2); //check led card
}

// Add more tests here

TEST_MAIN()
