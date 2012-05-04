#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "card.h"
#include "hand.h"

using namespace std;

class CardHash {
public:
    size_t operator()(const Card& key) const {
        return key.rank * 4 + key.suit;
    }
};

typedef unordered_set<Card,CardHash> CardSet;

struct HandStats {
    HandStats() : count(0) {
        for (int i = 0; i < HAND_RANK_END; ++i) {
            outs[i] = 0;
        }
    }

    unsigned long long count;
    unsigned long long outs[HAND_RANK_END];
};

static unordered_map<string,HandStats> stats;

size_t board_rank(Hand hand, Card flop1, Card flop2, Card flop3) {
    hand.append(flop1);
    hand.append(flop2);
    hand.append(flop3);
    return hand.getRank();
}

void board(const string& hole, const CardSet& deck, const Hand& hand)
{
    HandStats s = stats[hole];
    for (CardSet::const_iterator i = deck.begin(); i != deck.end(); ++i) {
        CardSet::const_iterator j = i;
        for (++j; j != deck.end(); ++j) {
            CardSet::const_iterator k = j;
            for (++k; k != deck.end(); ++k) {                
                s.count++;
                s.outs[ board_rank(hand, *i, *j, *k) ]++;
            }
        }
    }
    stats[hole] = s;
}

void printStats()
{
    for (unordered_map<string,HandStats>::iterator it = stats.begin(); it != stats.end(); it++) {
        string hole = it->first;
        HandStats handStats = it->second;
        double count = handStats.count;

        cout << hole << ',' << count;
        for (int i = 0; i < HAND_RANK_END; ++i) {
             cout << ',' << (handStats.outs[i] / count);
        }
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    // Setup deck of cards
    CardSet deck;
    for (Rank r = RANK_BEGIN; r != RANK_END; ++r) {
        for (Suit s = SUIT_BEGIN; s != SUIT_END; ++s) {
            Card card(r, s);
            deck.insert(card);
        }
    }

    unsigned long long count = 0;

    // Test each starting hand
    for (CardSet::const_iterator i = deck.begin(); i != deck.end(); ++i) {
        CardSet::const_iterator j = i;
        for (++j; j != deck.end(); ++j) {
            string hole = Card::pairString(*i, *j);
            CardSet test(deck);
            Hand hand;
            test.erase(*i); hand.append(*i);
            test.erase(*j); hand.append(*j);
            count++;
            board(hole, test, hand);
        }
    }

    cout << "TOTAL: " << count << endl;
    printStats();

    return 0;
}
