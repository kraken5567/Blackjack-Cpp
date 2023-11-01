#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include <vector>

// My Highscore is 3200

using namespace std;

// V globals here V
int points = 100;
int highestPts = points;

class Cards {
public:
    const char card_list[13] = { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A' };
    vector<char> cardHand{ randCard(), randCard() };
    string hand = cardString();
    int value = evaluate();

    // Class Functions

    string cardString() {
        string handString = "";
        for (int i = 0; i <= cardHand.size() - 1; i++) {
            handString += cardHand[i];
        }
        return handString;
    }

    void sort() { //pushes back Aces to evaluated better!
        for (int i = (cardHand.size() - 1); i >= 0; i--) {
            if (cardHand[i] == 'A') {
                cardHand.push_back('A');
                cardHand.erase(cardHand.begin() + i);
            }
        }
    }

    int evaluate() {
        char cardChar; int value = 0;
        for (int i = 0; i <= cardHand.size() - 1; i++) {
            cardChar = cardHand[i];
            //cout << "value: " << value << endl;
            if (cardChar >= '2' && cardChar <= '9') {
                //cout << "1" << endl;
                value += cardChar - '0';
            }
            else if (cardChar == 'T' || cardChar == 'J' || cardChar == 'Q' || cardChar == 'K') {
                //cout << "2" << endl;
                value += 10;
            }
            else if (cardChar == 'A') {
                //cout << "3" << endl;
                if (value >= 11) {
                    value += 1;
                }
                else {
                    value += 11;
                }
            }
            else {
                value += 0;
            }
        }
        return value;
    }

    int cardValue(char card) {
        int valCopy;
        //cout << "value: " << value << endl;
        if (card >= '2' && card <= '9') {
            //cout << "1" << endl;
            valCopy = card - '0';
        }
        else if (card == 'T' || card == 'J' || card == 'Q' || card == 'K') {
            //cout << "2" << endl;
            valCopy = 10;
        }
        else if (card == 'A') {
            //cout << "3" << endl;
            if (value >= 11) {
                valCopy = 1;
            }
            else {
                valCopy = 11;
            }   
        }
        else {
            valCopy = 0;
        }
        return valCopy;
    }

    string hideCardTotal(vector<char> hand) {
        return cardValue(hand[0]) + " + ?";
    }

    char randCard() {
        // length of Cardinfo elements
        int length = 13;
        // 0 to 12
        return card_list[rand() % 13];
    }

    void Hit() {
        cardHand.push_back(randCard());
        sort();
        value = evaluate();
        hand = cardString();
        
    }
};

void Winner(Cards P1, Cards D1, int wager) {
    cout << endl;
    cout << "Dealer Cards:" << D1.hand << "(" << D1.value << ")" << endl;
    cout << "Player Cards:" << P1.hand << "(" << P1.value << ")" << endl;
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
        while (!(wager > 0 && wager <= points)) { 
            cin >> wager;
            cout << endl;
        }
        
    // Everything else
    Cards player, dealer;

    cout << "Dealer:" << endl;
    // Hiding the second dealer card using a dummy evaluation value
    cout << dealer.cardHand[0] << " " << "?" << " : " << (dealer.cardValue(dealer.hand[0]) + "+ ?");
    cout << endl;
    cout << "Player:" << endl;
    cout << player.cardHand[0] << " " << player.cardHand[1] << " : " << player.value;
    cout << endl;

    while (player.value < 21) {
        cout << endl << "Stand(0) or Hit(1): "; bool hit; cin >> hit;
        if (hit != 0) { hit = 1; }
        if (!hit) { break; }
        player.Hit();
        cout << "Player: " << player.hand << " : " << player.value << endl;
    }

    while ( player.value < 21 && dealer.value <= player.value && dealer.value <= 21 ) {
        dealer.Hit();
    }

    Winner(player, dealer, wager);
    }

    cout << "You are out of points!" << endl;
    cout << "Your high score was: " << highestPts << endl;

}