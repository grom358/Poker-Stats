#include <QStringList>
#include "card.h"

template <class Enum> Enum& enum_increment(Enum& value, Enum begin, Enum end) {
    return value = (value == end) ? begin : Enum(value + 1);
}

Rank& operator++(Rank& rank) {
    return enum_increment(rank, RANK_BEGIN, RANK_END);
}

Suit& operator++(Suit& suit) {
    return enum_increment(suit, SUIT_BEGIN, SUIT_END);
}

static const QList<QChar> rankList = QList<QChar>() << '2' << '3' << '4' << '5' << '6' << '7' << '8' << '9' << 'T' << 'J' << 'Q' << 'K' << 'A' << '?';
static const QList<QChar> suitList = QList<QChar>() << 'h' << 'd' << 'c' << 's' << '?';

QString Card::toString() const {
    QString str;
    str.append(rankList[rank]);
    str.append(suitList[suit]);
    return str;
}

QString Card::pairString(const Card& a, const Card& b)
{
    QString str;
    if (a > b) {
        str.append(rankList[a.rank]);
        str.append(rankList[b.rank]);
    } else {
        str.append(rankList[b.rank]);
        str.append(rankList[a.rank]);
    }
    if (a.suit == b.suit) {
        str.append('s');
    }
    return str;
}

Card Card::fromString(const QString& str) {
    int i = rankList.indexOf(str[0]);
    Rank rank = (i == -1) ? RANK_END : ((Rank) i);
    i = suitList.indexOf(str[1]);
    Suit suit = (i == -1) ? SUIT_END : ((Suit) i);
    return Card(rank, suit);
}

QDebug& operator<<(QDebug &debug, const Card& c) {
    return debug << c.toString();
}

QTextStream& operator<<(QTextStream& out, const Card& c) {
    return out << c.toString();
}

QTextStream& operator>>(QTextStream& in, Card& c) {
    QChar r, s;
    in >> r >> s;
    QString str(r);
    str.append(s);
    c = Card::fromString(str);
    return in;
}

Card& Card::operator=(const Card &rhs) {
    rank = rhs.rank;
    suit = rhs.suit;
    return *this;
}

bool operator<(const Card& a, const Card& b) {
    return a.rank < b.rank;
}

bool operator<=(const Card& a, const Card& b) {
    return a.rank < b.rank || a == b;
}

bool operator==(const Card& a, const Card& b) {
    return a.suit == b.suit && a.rank == b.rank;
}

bool operator!=(const Card& a, const Card& b) {
    return a.suit != b.suit && a.rank != b.rank;
}

bool operator>=(const Card& a, const Card& b) {
    return a.rank > b.rank || a == b;
}

bool operator>(const Card& a, const Card& b) {
    return a.rank > b.rank;
}

uint qHash(const Card& key) {
    return qHash(key.rank * 4 + key.suit);
}
