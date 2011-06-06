#ifndef __HAND_H__
#define __HAND_H__

#include <QDebug>
#include <QList>
#include <QString>
#include <QTextStream>
#include "card.h"

enum HandRank { HIGH_CARD, ONE_PAIR, TWO_PAIR, THREE_OF_A_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH };

QTextStream& operator<<(QTextStream& out, const HandRank& hr);

class Hand : public QList<Card> {
public:
    Hand();
    Hand(const Hand& other);

    QString toString() const;

    HandRank getRank() const;
};

typedef QListIterator<Card> HandIterator;

QDebug& operator<<(QDebug &debug, const Hand& h);
QTextStream& operator<<(QTextStream& out, const Hand& h);

uint qHash(const Hand& key);

#endif
