#ifndef __CARD_H__
#define __CARD_H__

#include <iostream>
#include <string>

enum Rank { RANK_BEGIN, DEUCE = RANK_BEGIN, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, RANK_END };

std::ostream& operator<<(std::ostream& os, const Rank& r);
std::istream& operator>>(std::istream& is, Rank& r);

Rank& operator++(Rank& rank);

enum Suit { SUIT_BEGIN, HEART = SUIT_BEGIN, DIAMOND, CLUB, SPADE, SUIT_END };

Suit& operator++(Suit& suit);

std::ostream& operator<<(std::ostream& os, const Suit& s);
std::istream& operator>>(std::istream& is, Suit& s);

struct Card {
    Card() : rank(RANK_END), suit(SUIT_END) { }
    Card(Rank r, Suit s) : rank(r), suit(s) { }
    Card(const Card& c) : rank(c.rank), suit(c.suit) { }

    Rank rank;
    Suit suit;

    Card& operator=(const Card &rhs);
    std::string toString() const;
    static Card fromString(const std::string& str);
    static std::string pairString(const Card& a, const Card& b);
};

bool operator<(const Card& a, const Card& b);
bool operator<=(const Card& a, const Card& b);
bool operator==(const Card& a, const Card& b);
bool operator!=(const Card& a, const Card& b);
bool operator>=(const Card& a, const Card& b);
bool operator>(const Card& a, const Card& b);

std::ostream& operator<<(std::ostream& os, const Card& c);
std::istream& operator>>(std::istream& is, Card& c);

#endif
