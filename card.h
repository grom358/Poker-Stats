#ifndef __CARD_H__
#define __CARD_H__

#include <QString>
#include <QDebug>
#include <QTextStream>

enum Rank { RANK_BEGIN, DEUCE = RANK_BEGIN, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, RANK_END };

Rank& operator++(Rank& rank);

enum Suit { SUIT_BEGIN, HEART = SUIT_BEGIN, DIAMOND, CLUB, SPADE, SUIT_END };

Suit& operator++(Suit& suit);

struct Card {
    Card() : rank(RANK_END), suit(SUIT_END) { }
    Card(Rank r, Suit s) : rank(r), suit(s) { }
    Card(const Card& c) : rank(c.rank), suit(c.suit) { }

    Rank rank;
    Suit suit;

    Card& operator=(const Card& rhs);
    QString toString() const;
    static Card fromString(const QString& str);
    static QString pairString(const Card& a, const Card& b);
};

bool operator<(const Card& a, const Card& b);
bool operator<=(const Card& a, const Card& b);
bool operator==(const Card& a, const Card& b);
bool operator!=(const Card& a, const Card& b);
bool operator>=(const Card& a, const Card& b);
bool operator>(const Card& a, const Card& b);

uint qHash(const Card& key);

QDebug& operator<<(QDebug &debug, const Card& c);
QTextStream& operator<<(QTextStream& out, const Card& c);
QTextStream& operator>>(QTextStream& in, Card& c);

#endif
