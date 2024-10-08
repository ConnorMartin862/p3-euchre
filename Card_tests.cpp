#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_default_ctor) {
    Card c;
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
}

TEST(test_get_suit_two) {
    Card c(JACK, SPADES);
    ASSERT_EQUAL(CLUBS, c.get_suit(CLUBS));
}

TEST(test_is_face_or_ace) {
    Card c(ACE, DIAMONDS);
    ASSERT_EQUAL(true, c.is_face_or_ace());
}

TEST(test_is_right_bower) {
    Card c(JACK, CLUBS);
    ASSERT_EQUAL(true, c.is_right_bower(CLUBS));
}

TEST(test_is_left_bower) {
    Card c(JACK, CLUBS);
    ASSERT_EQUAL(true, c.is_left_bower(SPADES));
}

TEST(test_is_trump) {
    Card c(KING, CLUBS);
    ASSERT_EQUAL(true, c.is_trump(CLUBS));
    Card d(KING, SPADES);
    ASSERT_EQUAL(false, d.is_trump(CLUBS));
}

TEST(test_suit_next) {
    ASSERT_EQUAL(DIAMONDS, Suit_next(HEARTS));
    ASSERT_EQUAL(HEARTS, Suit_next(DIAMONDS));
    ASSERT_EQUAL(SPADES, Suit_next(CLUBS));
    ASSERT_EQUAL(CLUBS, Suit_next(SPADES));
}

TEST(test_card_less) {
    Card c(QUEEN, CLUBS);
    Card d(ACE, DIAMONDS);
    Card e(JACK, HEARTS);

    ASSERT_EQUAL(false, Card_less(c, d, CLUBS));
    ASSERT_EQUAL(true, Card_less(c, d, SPADES));
    ASSERT_EQUAL(true, Card_less(c, d, DIAMONDS));
    ASSERT_EQUAL(true, Card_less(c, d, HEARTS));
    ASSERT_EQUAL(true, Card_less(e, d, CLUBS));
    ASSERT_EQUAL(true, Card_less(e, d, SPADES));
    ASSERT_EQUAL(false, Card_less(e, d, DIAMONDS));
    ASSERT_EQUAL(false, Card_less(e, d, HEARTS));
}

TEST(test_led_card_less) {
    Card c(QUEEN, SPADES);
    Card d(ACE, DIAMONDS);
    Card e(JACK, HEARTS);
    Card led(KING, SPADES);

    ASSERT_EQUAL(false, Card_less(c, d, led, CLUBS));
    ASSERT_EQUAL(false, Card_less(c, d, led, SPADES));
    ASSERT_EQUAL(true, Card_less(c, d, led, DIAMONDS));
    ASSERT_EQUAL(false, Card_less(c, d, led, HEARTS));
    ASSERT_EQUAL(true, Card_less(e, d, led, CLUBS));
    ASSERT_EQUAL(true, Card_less(e, d, led, SPADES));
    ASSERT_EQUAL(false, Card_less(e, d, led, DIAMONDS));
    ASSERT_EQUAL(false, Card_less(e, d, led, HEARTS));
}
// Add more test cases here

TEST_MAIN()
