#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <string>
#include "card.h"
#include "hand.h"

using namespace std;

struct HandStats {
    HandStats() : count(0) {
        for (int i = 0; i < 8; ++i) {
            outs[i] = 0;
        }
    }

    unsigned long long count;
    unsigned long long outs[8];
};

static unordered_map<string,HandStats> stats;

void board(const string& hole, const set<Card>& deck, const Hand& hand)
{
    HandStats s;
    for (set<Card>::const_iterator i = deck.begin(); i != deck.end(); ++i) {
        set<Card>::const_iterator j = i;
        for (++j; j != deck.end(); ++j) {
            set<Card>::const_iterator k = j;
            for (++k; k != deck.end(); ++k) {
                Hand flop(hand);
                flop.append(*i); flop.append(*j); flop.append(*k);
                /*
                for (set<Card>::const_iterator l = k + 1; l != deck.end(); ++l) {
                    for (set<Card>::const_iterator m = l + 1; m != deck.end(); ++m) {

                    }
                }*/
                s.count++;
                s.outs[ flop.getRank() ]++;
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
        for (int i = 0; i < 8; ++i) {
             cout << ',' << (handStats.outs[i] / count);
        }
        cout << endl;
    }
}

int main(int argc, char *argv[])
{
    // Setup deck of cards
    set<Card> deck;
    for (Rank r = RANK_BEGIN; r != RANK_END; ++r) {
        for (Suit s = SUIT_BEGIN; s != SUIT_END; ++s) {
            Card card(r, s);
            deck.insert(card);
        }
    }

    unsigned long long count = 0;

    // Test each starting hand
    for (set<Card>::iterator i = deck.begin(); i != deck.end(); ++i) {
        set<Card>::iterator j = i;
        for (++j; j != deck.end(); ++j) {
            string hole = Card::pairString(*i, *j);
            set<Card> test(deck);
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
