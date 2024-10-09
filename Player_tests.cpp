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

TEST(test_player_factory) {
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

TEST(Simple_lead_card_play_card){
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, DIAMONDS));
  bob->add_card(Card(JACK, CLUBS));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(ACE, SPADES));
  Card l = bob->lead_card(SPADES);
  Card c(KING, HEARTS);
  ASSERT_EQUAL(c, l);
  Card e(NINE, DIAMONDS);
  Card p = bob->play_card(l, SPADES);
  ASSERT_EQUAL(p, e);

  Player * bob2 = Player_factory("Bob", "Simple");
  bob2->add_card(Card(NINE, DIAMONDS));
  bob2->add_card(Card(ACE, CLUBS));
  bob2->add_card(Card(JACK, CLUBS));
  bob2->add_card(Card(KING, CLUBS));
  bob2->add_card(Card(ACE, SPADES));
  Card f = bob2->lead_card(SPADES);
  Card g(ACE, CLUBS);
  ASSERT_EQUAL(g, f);
  Card k(KING, CLUBS);
  Card h = bob2->play_card(f, SPADES);
  ASSERT_EQUAL(h, k);

  Player * bob3 = Player_factory("Bob", "Simple");
  bob3->add_card(Card(NINE, CLUBS));
  bob3->add_card(Card(ACE, CLUBS));
  bob3->add_card(Card(JACK, CLUBS));
  bob3->add_card(Card(KING, CLUBS));
  bob3->add_card(Card(TEN, CLUBS));
  Card w = bob3->lead_card(CLUBS);
  Card x(JACK, CLUBS);
  ASSERT_EQUAL(w, x);
  Card y(ACE, CLUBS);
  Card z = bob3->play_card(w, CLUBS);
  ASSERT_EQUAL(y, z);

  delete bob;
  delete bob2;
  delete bob3;
}
// Add more tests here
TEST(test_Simple_make_trump_round_1) {
    // Arrange
    Player* alice = Player_factory("Alice", "Simple");
    Suit order_up_suit;
    Card upcard = Card(JACK, HEARTS);
    bool is_dealer = false;
    int round = 1;

    // Add cards to Alice's hand (simulate having cards)
    alice->add_card(Card(JACK, HEARTS));
    alice->add_card(Card(JACK, HEARTS));
    
    // Act
    bool result = alice->make_trump(upcard, is_dealer, round, order_up_suit);

    // Assert
    ASSERT_TRUE(result);  // Alice should order up
    ASSERT_EQUAL(order_up_suit, upcard.get_suit());  // Alice orders the suit of the upcard
    delete alice;
}

TEST(round_2_trump_make){
  Player* alice = Player_factory("Alice", "Simple");
  Suit order_up_suit = SPADES;
  Card upcard = Card(JACK, HEARTS);
    bool is_dealer = false;
    int round = 2;
    alice->add_card(Card(JACK, DIAMONDS));
    alice->add_card(Card(TEN, DIAMONDS));
    alice->add_card(Card(KING, HEARTS));
    bool result = alice->make_trump(upcard, is_dealer, round, order_up_suit);
    ASSERT_TRUE(result);
    ASSERT_EQUAL(order_up_suit, Suit_next(upcard.get_suit()));
    delete alice;
}

TEST(round_2_trump_make_2){
  Player* alice = Player_factory("Alice", "Simple");
  Suit order_up_suit = SPADES;
  Card upcard = Card(JACK, HEARTS);
    bool is_dealer = false;
    int round = 2;
    alice->add_card(Card(JACK, SPADES));
    alice->add_card(Card(TEN, SPADES));
    alice->add_card(Card(KING, CLUBS));
    bool result = alice->make_trump(upcard, is_dealer, round, order_up_suit);
    ASSERT_FALSE(result);
    delete alice;
}

TEST(round_2_trump_make_dealer){
  Player* alice = Player_factory("Alice", "Simple");
  Suit order_up_suit = SPADES;
  Card upcard = Card(JACK, HEARTS);
    bool is_dealer = true;
    int round = 2;
    alice->add_card(Card(JACK, SPADES));
    alice->add_card(Card(TEN, SPADES));
    alice->add_card(Card(KING, CLUBS));
    bool result = alice->make_trump(upcard, is_dealer, round, order_up_suit);
    ASSERT_TRUE(result);
    ASSERT_EQUAL(order_up_suit, Suit_next(upcard.get_suit()));
    delete alice;
}

TEST(round_1_trump_make_dealer){
  Player* alice = Player_factory("Alice", "Simple");
  Suit order_up_suit = SPADES;
  Card upcard = Card(JACK, HEARTS);
    bool is_dealer = true;
    int round = 1;
    alice->add_card(Card(JACK, SPADES));
    alice->add_card(Card(TEN, SPADES));
    alice->add_card(Card(KING, CLUBS));
    bool result = alice->make_trump(upcard, is_dealer, round, order_up_suit);
    ASSERT_FALSE(result);
    delete alice;
}


TEST(test_Simple_make_trump_round_1_dealer) {
    // Arrange
    Player* alice = Player_factory("Alice", "Simple");
    Suit order_up_suit;
    Card upcard = Card(JACK, HEARTS);
    bool is_dealer = true;
    int round = 1;

    // Add cards to Alice's hand (simulate having cards)
    alice->add_card(Card(JACK, HEARTS));
    alice->add_card(Card(JACK, HEARTS));
    
    // Act
    bool result = alice->make_trump(upcard, is_dealer, round, order_up_suit);

    // Assert
    ASSERT_TRUE(result);  // Alice should order up
    ASSERT_EQUAL(order_up_suit, upcard.get_suit());  // Alice orders the suit of the upcard
    delete alice;
}

TEST(test_Simple_make_trump_round_1_dealer_left_bower) {
    // Arrange
    Player* alice = Player_factory("Alice", "Simple");
    Suit order_up_suit;
    Card upcard = Card(JACK, HEARTS);
    bool is_dealer = true;
    int round = 1;

    // Add cards to Alice's hand (simulate having cards)
    alice->add_card(Card(JACK, DIAMONDS));
    alice->add_card(Card(JACK, SPADES));
    alice->add_card(Card(ACE, HEARTS));
    
    // Act
    bool result = alice->make_trump(upcard, is_dealer, round, order_up_suit);

    // Assert
    ASSERT_TRUE(result);  // Alice should order up
    ASSERT_EQUAL(order_up_suit, upcard.get_suit());  // Alice orders the suit of the upcard
    delete alice;
}
TEST(test_Simple_make_trump_round_1_left_bower) {
    // Arrange
    Player* alice = Player_factory("Alice", "Simple");
    Suit order_up_suit;
    Card upcard = Card(JACK, HEARTS);
    bool is_dealer = false;
    int round = 1;

    // Add cards to Alice's hand (simulate having cards)
    alice->add_card(Card(JACK, DIAMONDS));
    alice->add_card(Card(JACK, SPADES));
    alice->add_card(Card(ACE, HEARTS));
    
    // Act
    bool result = alice->make_trump(upcard, is_dealer, round, order_up_suit);

    // Assert
    ASSERT_TRUE(result);  // Alice should order up
    ASSERT_EQUAL(order_up_suit, upcard.get_suit());  // Alice orders the suit of the upcard
    delete alice;
}

TEST(test_Simple_make_trump_round_2_left_bower) {
    // Arrange
    Player* alice = Player_factory("Alice", "Simple");
    Suit order_up_suit;
    Card upcard = Card(JACK, HEARTS);
    bool is_dealer = false;
    int round = 2;

    // Add cards to Alice's hand (simulate having cards)
    alice->add_card(Card(JACK, DIAMONDS));
    alice->add_card(Card(JACK, SPADES));
    
    // Act
    bool result = alice->make_trump(upcard, is_dealer, round, order_up_suit);

    // Assert
    ASSERT_TRUE(result);  // Alice should order up
    ASSERT_EQUAL(order_up_suit, Suit_next(upcard.get_suit()));  // Alice orders the suit of the upcard
    delete alice;
}
TEST(test_Simple_make_trump_round_2_dealer_left_bower) {
    // Arrange
    Player* alice = Player_factory("Alice", "Simple");
    Suit order_up_suit;
    Card upcard = Card(JACK, HEARTS);
    bool is_dealer = true;
    int round = 2;

    // Add cards to Alice's hand (simulate having cards)
    alice->add_card(Card(JACK, DIAMONDS));
    alice->add_card(Card(JACK, SPADES));
    
    // Act
    bool result = alice->make_trump(upcard, is_dealer, round, order_up_suit);

    // Assert
    ASSERT_TRUE(result);  // Alice should order up
    ASSERT_EQUAL(order_up_suit, Suit_next(upcard.get_suit()));  // Alice orders the suit of the upcard
    delete alice;
}

TEST(test_Simple_make_trump_round_1_2) {
    // Arrange
    Player* alice = Player_factory("Alice", "Simple");
    Suit order_up_suit;
    Card upcard = Card(JACK, HEARTS);
    bool is_dealer = false;
    int round = 1;
    // Add cards to Alice's hand (simulate having cards)
    alice->add_card(Card(QUEEN, HEARTS));
    alice->add_card(Card(JACK, HEARTS));
    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(KING, SPADES));
    alice->add_card(Card(NINE, CLUBS));
    
    // Act
    bool result = alice->make_trump(upcard, is_dealer, round, order_up_suit);
    // Assert
    ASSERT_TRUE(result);  // Alice should order up
    ASSERT_EQUAL(order_up_suit, upcard.get_suit());  // Alice orders the suit of the upcard
    delete alice;
}

TEST(test_Simple_make_trump_round_1_case_5) {
    // Arrange
    Player* alice = Player_factory("Alice", "Simple");
    Suit order_up_suit;
    Card upcard = Card(JACK, HEARTS);
    bool is_dealer = false;
    int round = 1;
    // Add cards to Alice's hand (simulate having cards)
    alice->add_card(Card(QUEEN, HEARTS));
    alice->add_card(Card(TEN, DIAMONDS));
    alice->add_card(Card(ACE, CLUBS));
    alice->add_card(Card(KING, SPADES));
    alice->add_card(Card(NINE, CLUBS));
    
    // Act
    bool result = alice->make_trump(upcard, is_dealer, round, order_up_suit);
    // Assert
    ASSERT_FALSE(result);  // Alice should not order up
    delete alice;
}

TEST(make_trump_round_2_4){
  Player* alice = Player_factory("Alice", "Simple");
    Suit order_up_suit;
    Card upcard = Card(JACK, HEARTS);
    bool is_dealer = false;
    int round = 2;
    // Add cards to Alice's hand (simulate having cards)
    alice->add_card(Card(JACK, HEARTS));
    alice->add_card(Card(TEN, SPADES));
    alice->add_card(Card(ACE, HEARTS));
    alice->add_card(Card(KING, SPADES));
    alice->add_card(Card(NINE, CLUBS));

    
    // Act
    bool result = alice->make_trump(upcard, is_dealer, round, order_up_suit);
    // Assert
    ASSERT_FALSE(result);  // Alice should order up
    delete alice;
}

TEST(make_trump_round_2_case_3){
  Player* alice = Player_factory("Alice", "Simple");
    Suit order_up_suit;
    Card upcard = Card(JACK, HEARTS);
    bool is_dealer = false;
    int round = 2;
    // Add cards to Alice's hand (simulate having cards)
    alice->add_card(Card(JACK, HEARTS));
    alice->add_card(Card(JACK, DIAMONDS));
    alice->add_card(Card(ACE, CLUBS));
    alice->add_card(Card(KING, SPADES));
    alice->add_card(Card(NINE, CLUBS));


    
    // Act
    bool result = alice->make_trump(upcard, is_dealer, round, order_up_suit);
    // Assert
    ASSERT_TRUE(result);  // Alice should order up
    delete alice;
}
TEST_MAIN()
