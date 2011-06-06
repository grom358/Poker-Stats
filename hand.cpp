#include <algorithm>
#include <QDebug>
#include <QHash>
#include <QStringList>
#include "hand.h"

using namespace std;

static const QStringList strHandRanks = QStringList() << "High Card" << "Pair" << "Two Pair" << "Three of a Kind" << "Straight" << "Flush" << "Full House" << "Four of a Kind" << "Straight Flush";

QTextStream& operator<<(QTextStream& out, const HandRank& hr) {
    return out << strHandRanks[hr];
}

Hand::Hand() : QList<Card>()
{
}

Hand::Hand(const Hand& other) : QList<Card>(other)
{
}

static bool highRankCompare(const Card& a, const Card& b) {
    return a > b;
}

static void findSets(const QList<Card>& cards, int& maxSize, int& pairCount)
{
    maxSize = 0;
    pairCount = 0;

    QList<Card> cardsByRank(cards);
    sort(cardsByRank.begin(), cardsByRank.end(), highRankCompare);
    int size = 0;
    Rank r = RANK_END;
    HandIterator it(cardsByRank);
    while (it.hasNext()) {
        Card card = it.next();
        if (card.rank != r) {
            if (size > 1) {
                maxSize = (size > maxSize) ? size : maxSize;
                pairCount++;
            }
            size = 0;
        }
        r = card.rank;
        size++;
    }
    if (size > 1) {
        maxSize = (size > maxSize) ? size : maxSize;
        pairCount++;
    }
}

static bool isStraight(QList<Card>::const_iterator first, QList<Card>::const_iterator last)
{
    int count = 1;

    QList<Card>::const_iterator it = first;
    QList<Card>::const_iterator prev = it;
    for (++it; it != last; ++it) {
        if (prev->rank == it->rank) {
            continue;
        }

        if (prev->rank != it->rank + 1) {
            count = 0;
        }
        count++;
        if (count == 5) {
            return true;
        }
        prev = it;
    }
    return false;
}

static bool suitRankCompare(const Card& a, const Card& b) {
    if (a.suit == b.suit) {
        return a > b;
    }
    return a.suit < b.suit;
}

static bool isStraightFlush(const QList<Card>& cards) {
    QList<Card> cardsBySuit(cards);
    // By sorting into suits any straight we find is a straight flush
    sort(cardsBySuit.begin(), cardsBySuit.end(), suitRankCompare);
    return isStraight(cardsBySuit.begin(), cardsBySuit.end());
}

static bool isFlush(const QList<Card>& cards) {
    int suits[4] = { 0, 0, 0, 0 };
    for (QList<Card>::const_iterator it = cards.begin(); it != cards.end(); ++it) {
        int cardSuit = (int) it->suit;
        suits[cardSuit]++;
        if (suits[cardSuit] == 5) {
            return true;
        }
    }
    return false;
}

static bool isStraight(const QList<Card>& cards) {
    QList<Card> cardsByRank(cards);
    sort(cardsByRank.begin(), cardsByRank.end(), highRankCompare);
    return isStraight(cards.begin(), cards.end());
}

HandRank Hand::getRank() const
{
    int kindCount = 0;
    int pairCount = 0;
    findSets(*this, kindCount, pairCount);

    if (isStraightFlush(*this)) {
        return STRAIGHT_FLUSH;
    } else if (kindCount == 4) {
        return FOUR_OF_A_KIND;
    } else if (kindCount >= 3 && pairCount >= 2) {
        return FULL_HOUSE;
    } else if (isFlush(*this)) {
        return FLUSH;
    } else if (isStraight(*this)) {
        return STRAIGHT;
    } else if (kindCount >= 3) {
        return THREE_OF_A_KIND;
    } else if (kindCount >= 2 && pairCount >= 2) {
        return TWO_PAIR;
    } else if (kindCount == 2) {
        return ONE_PAIR;
    } else {
        return HIGH_CARD;
    }
}

QString Hand::toString() const
{
    QStringList strList;
    HandIterator it(*this);
    while (it.hasNext()) {
        strList.append(it.next().toString());
    }
    return strList.join(" ");
}

QDebug& operator<<(QDebug &debug, const Hand& h)
{
    return debug << h.toString();
}

QTextStream& operator<<(QTextStream& out, const Hand& h)
{
    return out << h.toString();
}

uint qHash(const Hand& key)
{
    uint hash = 17;
    HandIterator it(key);
    while (it.hasNext()) {
        hash = hash * 37 + qHash(it.next());
    }
    return hash;
}
