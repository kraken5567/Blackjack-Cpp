#include <iostream>
#include <string>
#include <random>
#include <time.h>


// A, any, any: Ace does not re-evaluate 


using namespace std;

// V globals here V
int points = 100;
int highestPts = points;

class Cards {
public:
    const char card_list[13] = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };
    char cards[21] = { randCard(), randCard(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int value = evaluate(cards[0], evaluate(cards[1], value = 0) );

    // Class Functions

    int evaluate(char cardChar, int value) {
        //cout << "value: " << value << endl;
        if (cardChar >= '2' && cardChar <= '9') {
            //cout << "1" << endl;
            return cardChar-'0' + value;
        }
        else if (cardChar == 'T' || cardChar == 'J' || cardChar == 'Q' || cardChar == 'K') {
            //cout << "2" << endl;
            return 10 + value;
        }
        else if (cardChar == 'A') {
            //cout << "3" << endl;
            if (value >= 11) {
                return 1 + value;
            }
            else {
                return 11 + value;
            }
        }
        else {
            return 0 + value;
        }
    }
    char randCard() {
        // length of Cardinfo elements
        int length = 13;

        // 0 to 12
        return card_list[rand() % 13];
    }
    void Hit(int i) {
        cards[2 + i] = randCard();
        value = evaluate(cards[2 + i], value);
        cout << cards << ": " << value << endl;
    }
};

void Winner(Cards P1, Cards D1, int wager) {
    cout << endl;
    cout << "Dealer Cards:" << D1.cards << "(" << D1.value << ")" << endl;
    cout << "Player Cards:" << P1.cards << "(" << P1.value << ")" << endl;
    cout << endl;

    if (P1.value <= 21 && (P1.value > D1.value || D1.value > 21)) {
        cout << "PLAYER WINS!"; 
        points += wager;
    }
    else if (D1.value <= 21 && (D1.value > P1.value || P1.value > 21)) {
        cout << "DEALER WINS!"; 
        points -= wager;
    }
    else {
        cout << "DEALER WINS!"; 
        points -= wager;
    }

    if (points > highestPts) { highestPts = points; }

    for (int i = 0; i < 4; i++) { cout << endl; }
}

int main()
{
    // DO FIRST!
    srand(time(0));
    while (points > 0) {
        int wager = 0;
        cout << endl << "Current points: " << points << endl << "Points to wager: ";
        while (!(wager > 0 && wager <= points)) { cin >> wager; }
        
    // Everything else
    Cards player, dealer, dummy;

    cout << "Dealer:" << endl;
    // Hiding the second dealer card using a dummy evaluation value
    cout << dealer.cards[0] << " " << "?" << " : " << dealer.value-dummy.evaluate(dealer.cards[1],0) << " + ?";
    cout << endl;
    cout << "Player:" << endl;
    cout << player.cards[0] << " " << player.cards[1] << " : " << player.value;

    int i = 0;
    while (player.value < 21) {
        cout << endl << "Stand(0) or Hit(1): "; bool hit; cin >> hit;
        if (hit != 0) { hit = 1; }
        if (!hit) { break; }
        cout << "Player: ";
        player.Hit(i);

        i++;
    }

    i = 0;
    while ( player.value < 21 && dealer.value <= player.value && dealer.value <= 21 ) {
        cout << "Dealer: ";
        dealer.Hit(i);

        i++;
    }

    Winner(player, dealer, wager);
    }

    cout << "You are out of points!" << endl;
    cout << "Your high score was: " << highestPts << endl;

}