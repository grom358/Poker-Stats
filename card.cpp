#include "card.h"

template <class Enum> Enum& enum_increment(Enum& value, Enum begin, Enum end) {
    return value = (value == end) ? begin : Enum(value + 1);
}

Rank& operator++(Rank& rank) {
    return enum_increment(rank, RANK_BEGIN, RANK_END);
}

static char Ranks[] = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };

std::ostream& operator<<(std::ostream& os, const Rank& r) {
    return os << Ranks[r];
}

std::istream& operator>>(std::istream& is, Rank& r) {
    char c;
    is >> c;
    for (int i = 0; i < 13; ++i) {
        if (Ranks[i] == c) {
            r = (Rank) i;
            return is;
        }
    }
    return is;
}

Suit& operator++(Suit& suit) {
    return enum_increment(suit, SUIT_BEGIN, SUIT_END);
}

static char Suits[] = { 'h', 'd', 'c', 's' };

std::ostream& operator<<(std::ostream& os, const Suit& s) {
    return os << Suits[s];
}

std::istream& operator>>(std::istream& is, Suit& s) {
    char c;
    is >> c;
    for (int i = 0; i < 4; ++i) {
        if (Suits[i] == c) {
            s = (Suit) i;
            return is;
        }
    }
    return is;
}

std::string Card::toString() const {
    std::string str;
    str.append(1, Ranks[rank]);
    str.append(1, Suits[suit]);
    return str;
}

std::string Card::pairString(const Card& a, const Card& b)
{
    std::string str;
    if (a > b) {
        str.append(1, Ranks[a.rank]);
        str.append(1, Ranks[b.rank]);
    } else {
        str.append(1, Ranks[b.rank]);
        str.append(1, Ranks[a.rank]);
    }
    if (a.suit == b.suit) {
        str.append(1, 's');
    }
    return str;
}

int indexOf(const char& letter, const char* list, int n) {
    for (int i = 0; i < n; ++i) {
        if (list[i] == letter) {
            return i;
        }
    }
    return -1;
}

Card Card::fromString(const std::string& str) {
    int i = indexOf(str[0], Ranks, RANK_END);
    Rank rank = (i == -1) ? RANK_END : ((Rank) i);
    i = indexOf(str[1], Suits, SUIT_END);
    Suit suit = (i == -1) ? SUIT_END : ((Suit) i);
    return Card(rank, suit);
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

size_t card_hash(const Card& key) {
    return key.rank * 4 + key.suit;
}

std::ostream& operator<<(std::ostream& os, const Card& c) {
    return os << c.rank << c.suit;
}

std::istream& operator>>(std::istream& is, Card& c) {
    return is >> c.rank >> c.suit;
}
