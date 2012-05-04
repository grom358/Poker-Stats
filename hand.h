#ifndef __HAND_H__
#define __HAND_H__

#include <iostream>
#include <vector>
#include "card.h"

enum HandRank { HIGH_CARD, ONE_PAIR, TWO_PAIR, THREE_OF_A_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_A_KIND, STRAIGHT_FLUSH, HAND_RANK_END };

std::ostream& operator<<(std::ostream& out, const HandRank& hr);

class Hand {
public:
    Hand();    
    Hand(const Hand& other);
    
    void append(const Card& card);

    std::string toString() const;

    HandRank getRank() const;
private:
    std::vector<Card> cards;
};

std::ostream& operator<<(std::ostream& os, const Hand& h);

#endif
