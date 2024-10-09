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
    Card d(ACE, DIAMONDS);
    ASSERT_EQUAL(DIAMONDS, d.get_suit(DIAMONDS));
    ASSERT_EQUAL(CLUBS, c.get_suit(CLUBS));
}

TEST(test_is_face_or_ace) {
    Card a(ACE, DIAMONDS);
    Card b(JACK, SPADES);
    Card c(KING, SPADES);
    Card d(QUEEN, CLUBS);
    Card e(NINE, HEARTS);
    Card f(TEN, DIAMONDS);
    ASSERT_EQUAL(true, a.is_face_or_ace());
    ASSERT_EQUAL(true, b.is_face_or_ace());
    ASSERT_EQUAL(true, c.is_face_or_ace());
    ASSERT_EQUAL(true, d.is_face_or_ace());
    ASSERT_EQUAL(false, e.is_face_or_ace());
    ASSERT_EQUAL(false, f.is_face_or_ace());
}

TEST(test_is_right_bower) {
    Card c(JACK, CLUBS);
    Card d(JACK, SPADES);
    Card e(KING, DIAMONDS);
    ASSERT_EQUAL(true, c.is_right_bower(CLUBS));
    ASSERT_EQUAL(false, d.is_right_bower(CLUBS));
    ASSERT_EQUAL(false, e.is_right_bower(DIAMONDS));
}

TEST(test_is_left_bower) {
    Card c(JACK, CLUBS);
    Card d(JACK, SPADES);
    Card e(KING, DIAMONDS);
    ASSERT_EQUAL(true, c.is_left_bower(SPADES));
    ASSERT_EQUAL(false, d.is_left_bower(SPADES));
    ASSERT_EQUAL(false, e.is_left_bower(HEARTS));
    ASSERT_EQUAL(false, e.is_left_bower(DIAMONDS));
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
    Card f(TEN, CLUBS);
    Card led(KING, SPADES);
    Card led2(NINE, HEARTS);

    ASSERT_EQUAL(false, Card_less(c, d, led, CLUBS));
    ASSERT_EQUAL(false, Card_less(c, d, led, SPADES));
    ASSERT_EQUAL(true, Card_less(c, d, led, DIAMONDS));
    ASSERT_EQUAL(false, Card_less(c, d, led, HEARTS));
    ASSERT_EQUAL(true, Card_less(e, d, led, CLUBS));
    ASSERT_EQUAL(true, Card_less(e, d, led, SPADES));
    ASSERT_EQUAL(false, Card_less(e, d, led, DIAMONDS));
    ASSERT_EQUAL(false, Card_less(e, d, led, HEARTS));
    ASSERT_EQUAL(true, Card_less(c, f, led2, CLUBS));
    ASSERT_EQUAL(false, Card_less(d, f, led2, HEARTS));
    ASSERT_EQUAL(false, Card_less(e, f, led2, DIAMONDS));
    ASSERT_EQUAL(false, Card_less(d, f, led2, SPADES));
}
// Add more test cases here

TEST_MAIN()
