#include <algorithm>
#include "hand.h"

using namespace std;

static const char* strHandRanks[] = { "High Card", "Pair", "Two Pair",
    "Three of a Kind", "Straight", "Flush", "Full House", "Four of a Kind",
    "Straight Flush" };

ostream& operator<<(ostream& out, const HandRank& hr) {
    return out << strHandRanks[hr];
}

Hand::Hand() : cards()
{
}

Hand::Hand(const Hand& other) : cards(other.cards)
{
}

void Hand::append(const Card& card)
{
    this->cards.push_back(card);
}

static bool highRankCompare(const Card& a, const Card& b) {
    return a > b;
}

static void findSets(const vector<Card>& cards, int& maxSize, int& pairCount)
{
    maxSize = 0;
    pairCount = 0;

    vector<Card> cardsByRank(cards);
    sort(cardsByRank.begin(), cardsByRank.end(), highRankCompare);
    int size = 0;
    Rank r = RANK_END;
    for (vector<Card>::const_iterator it = cardsByRank.begin(); it != cardsByRank.end(); ++it) {
        Card card = (*it);
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

static bool isStraight(vector<Card>::const_iterator first, vector<Card>::const_iterator last)
{
    int count = 1;

    vector<Card>::const_iterator it = first;
    vector<Card>::const_iterator prev = it;
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

static bool isStraightFlush(const vector<Card>& cards) {
    vector<Card> cardsBySuit(cards);
    // By sorting into suits any straight we find is a straight flush
    sort(cardsBySuit.begin(), cardsBySuit.end(), suitRankCompare);
    return isStraight(cardsBySuit.begin(), cardsBySuit.end());
}

static bool isFlush(const vector<Card>& cards) {
    int suits[4] = { 0, 0, 0, 0 };
    for (vector<Card>::const_iterator it = cards.begin(); it != cards.end(); ++it) {
        int cardSuit = (int) it->suit;
        suits[cardSuit]++;
        if (suits[cardSuit] == 5) {
            return true;
        }
    }
    return false;
}

static bool isStraight(const vector<Card>& cards) {
    vector<Card> cardsByRank(cards);
    sort(cardsByRank.begin(), cardsByRank.end(), highRankCompare);
    return isStraight(cardsByRank.begin(), cardsByRank.end());
}

HandRank Hand::getRank() const
{
    int kindCount = 0;
    int pairCount = 0;
    findSets(this->cards, kindCount, pairCount);

    if (isStraightFlush(this->cards)) {
        return STRAIGHT_FLUSH;
    } else if (kindCount == 4) {
        return FOUR_OF_A_KIND;
    } else if (kindCount >= 3 && pairCount >= 2) {
        return FULL_HOUSE;
    } else if (isFlush(this->cards)) {
        return FLUSH;
    } else if (isStraight(this->cards)) {
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

template <typename Iter>
Iter next(Iter iter)
{
    return ++iter;
}

string Hand::toString() const
{
    string str;
    for (vector<Card>::const_iterator it = this->cards.begin(); it != this->cards.end();) {
        str.append(it->toString());
        ++it;
        if (it != this->cards.end()) {
            str.append(" ");
        }
    }
    return str;
}

ostream& operator<<(ostream& out, const Hand& h)
{
    return out << h.toString();
}
