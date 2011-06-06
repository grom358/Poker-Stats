#include <QtCore>
#include <algorithm>
#include "card.h"
#include "hand.h"

struct HandStats {
    HandStats() : count(0) {
        for (int i = 0; i < 8; ++i) {
            outs[i] = 0;
        }
    }

    qulonglong count;
    qulonglong outs[8];
};

static QHash<QString,HandStats> stats;

void board(const QString& hole, const QSet<Card>& deck, const Hand& hand)
{
    for (QSet<Card>::const_iterator i = deck.begin(); i != deck.end(); ++i) {
        for (QSet<Card>::const_iterator j = i + 1; j != deck.end(); ++j) {
            for (QSet<Card>::const_iterator k = j + 1; k != deck.end(); ++k) {
                Hand flop(hand);
                flop.append(*i); flop.append(*j); flop.append(*k);
                /*
                for (QSet<Card>::const_iterator l = k + 1; l != deck.end(); ++l) {
                    for (QSet<Card>::const_iterator m = l + 1; m != deck.end(); ++m) {

                    }
                }*/
                stats[hole].count++;
                stats[hole].outs[ flop.getRank() ]++;
            }
        }
    }
}

void printStats()
{
    QTextStream out(stdout);
    QHashIterator<QString,HandStats> it(stats);
    while (it.hasNext()) {
        it.next();
        QString hole = it.key();
        out << hole << ',' << it.value().count;

        HandStats handStats = it.value();
        double count = handStats.count;
        for (int i = 0; i < 8; ++i) {
             out << ',' << (handStats.outs[i] / count);
        }
        out << endl;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream qout(stdout);

    // Setup deck of cards
    QSet<Card> deck;
    for (Rank r = RANK_BEGIN; r != RANK_END; ++r) {
        for (Suit s = SUIT_BEGIN; s != SUIT_END; ++s) {
            Card card(r, s);
            deck.insert(card);
        }
    }

    qulonglong count = 0;

    // Test each starting hand
    for (QSet<Card>::iterator i = deck.begin(); i != deck.end(); ++i) {
        for (QSet<Card>::iterator j = i + 1; j != deck.end(); ++j) {
            QString hole = Card::pairString(*i, *j);
            QSet<Card> test(deck);
            Hand hand;
            test.remove(*i); hand.append(*i);
            test.remove(*j); hand.append(*j);
            count++;
            board(hole, test, hand);
        }
    }

    qout << "TOTAL: " << count << endl;
    printStats();

    QTimer::singleShot(0, &a, SLOT(quit()));
    return a.exec();
}
