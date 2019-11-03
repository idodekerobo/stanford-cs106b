#include <iostream>
#include "console.h"
#include "stack.h"
#include "simpio.h"
#include <fstream>
using namespace std;

void recursionMysteryComma(int x, int y);
int sumOfSquares(int n);
void zigzag(int n);
void stutterStack(Stack<int> &s);
bool isSubsequence(string big, string small);
void reverseLines(ifstream &in);

int main() {
    /* Problem 1 */
//    recursionMysteryComma(4, 1);
//    recursionMysteryComma(4, 2);
//    recursionMysteryComma(8, 2);
//    recursionMysteryComma(4, 3);
//    recursionMysteryComma(3, 4);

    /* Problem 2 */
//    cout << sumOfSquares(3) << endl;

    /* Problem 3 */
//    zigzag(9);

    /* Problem 4 */
//    Stack<int> s = {1, 2, 3};
//    cout << s << endl;
//    stutterStack(s);
//    cout << s << endl;

    /* Problem 5 */


    /* Problem 6 */
    ifstream in;
    in.open("/Users/idodekerobo/Documents/baby\ mogul/Young\ Zuckerberg/CS106B/Sections/Week3/Section02/res/poem.txt");
    reverseLines(in);


    return 0;
}

void recursionMysteryComma(int x, int y) {
    if (y==1) {
        cout << x;
    } else {
        cout << (x*y) << ", ";
        recursionMysteryComma(x, y-1);
        cout << ", " << (x*y);
    }
}

int sumOfSquares(int n) {
    if (n < 1) {
        return 0;
    } else {
        return n*n + sumOfSquares(n-1);
    }
}

// dry-er version
void zigzag(int n) {
    if (n==2) {
        cout << "**";
    } else if (n==1) {
        cout << "*";
    } else {
        cout <<"<";
        zigzag(n-2);
        cout << ">";
    }
}

// this isn't very dry
//void zigzag(int n) {
//    if (n % 2 == 0) {
//        if (n==2) {
//            cout << "**";
//        } else {
//            cout << "<";
//            zigzag(n-2);
//            cout << ">";
//        }
//    } else {
//        if (n==1) {
//            cout << "*";
//        } else {
//            cout << "<";
//            zigzag(n-2);
//            cout << ">";
//        }
//    }
//}

void stutterStack(Stack<int> &s) {
//    if (s.size() > 0) {
    if (!s.isEmpty()) {
        int tmp = s.pop();
        stutterStack(s);
        for (int i=0; i < 2; i++) {
            s.push(tmp);
        }
    }
}

bool isSubsequence(string big, string small) {
    // base case
    if (small == "") {
        return true; // if small is an empty string before big then it is true
    } else if (big == "") {
        return false; // if big is an empty string before the small then it can't be true cus it ran out of letters in big to check w/ small
    } else {
        // recursive case
        if (big[0] == small[0]) {
            return isSubsequence(big.substr(1), small.substr(1)); // if both first char are equal then go to the next one for both
        } else {
            return isSubsequence(big.substr(1), small); // if both aren't equal then check the next char in big
        }
    }
}

void reverseLines(ifstream &in) {
    string s;
    while (!in.fail()) {
        getline(in, s);
        reverseLines(in);
    }
    cout << s << endl;

    /* also works (answer in solutions): */
/*    if (getline(in, s)) {
        reverseLines(in);
        cout << s << endl;
    } // implicit base case - do nothing

*/
}
