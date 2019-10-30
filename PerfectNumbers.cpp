/*
 * Program: Perfect Numbers.cpp
 * =============================
 * Program is used to test whether or not a number is
 * a 'perfect' number. Perfect numbers are numbers that
 * are equal to the sum of their proper divisors.
 * For example: 6 is a perfect number because it is the sum of
 * 3, 2, and 1.
 */

#include <iostream>
#include "console.h"
#include <fstream>
#include "vector.h"
#include "random.h"
#include "strlib.h"

#include "simpio.h"
#include "gwindow.h"
#include "gevents.h"
#include "gtypes.h"
using namespace std;

/* Problem 1 */
bool IsPerfect(int n) {
    bool isPerfect = false;

    // find divisors of n
    Vector<int> divisors;

    // if number is a divisor of n it'll add to the vector
    for (int i = n - 1; i > 0; i--) {
        if ((n % i) == 0) {
            divisors.add(i);
        }
    }

    //add divisors of n
    int sumOfDivisors = 0;

    for (int i = 0; i < divisors.size(); i++) {
        sumOfDivisors += divisors[i];
    }

    // check if n is perfect
    if (sumOfDivisors == n) {
        isPerfect = true;
    }

    return isPerfect;
}
/* Problem 2 */
int TrialRun(int intendedVotes, double error) {
    bool correctVote = true;
    int actualVotes = 0;
    double chance = 0;
    for (int i=0; i < intendedVotes; i++) {
        chance = 1-error;
        correctVote = randomChance( chance );
        if (correctVote) {
            actualVotes++;
        }
    }
    return actualVotes;
}
void VoterSimulation() {
    int voters;
    cout << "Enter number of voters: ";
    cin >> voters;

    double spread;
    cout << "Enter the percentage spread between candidates: ";
    while (true) {
        cin >> spread;
        if (spread > 0 && spread < 1) break;
        cout << " Please enter a valid percentage spread (in decimal format): ";
    }

    double error;
    cout << "Enter the voting error percentage: ";
    while (true) {
        cin >> error;
        if (error > 0 && error < 1) break;
        cout << " Please enter a valid error percentage (in decimal format): ";
    }

    double numTrials;
    cout << "Enter total number of trials to simulate: ";
    cin >> numTrials;

    int intendedVotesForWinner = voters * (1 + spread) * .50;
    //int intendedVotesForLoser = voters - intendedVotesForWinner;

    double invalidTrials = 0;

    for (int i=0; i < numTrials; i++) {
        int actualVotesForWinner = TrialRun(intendedVotesForWinner, error);
        // int actualVotesForLoser = TrialRun(intendedVotesForLoser, error); // don't run a separate trial for loser, she/he just gets remainder
        int actualVotesForLoser = voters - actualVotesForWinner;
        if (actualVotesForWinner <= actualVotesForLoser) {
            invalidTrials++;
        }
    }

    double chanceOfInvalidElection = (invalidTrials/numTrials); // * 100;

    cout << "This election has a " << chanceOfInvalidElection << " chance of having the wrong outcome" << endl;
}


/*Problem 4*/
string Capitalize(string word) {
    word[0] = toupper(word[0]);

    for (int i=1; i < word.length(); i++) {
        word[i] = tolower(word[i]);
    }
    return word;
}
string letterDigits[7] = { "aeiouhwy", "bfpv", "cgjkqsxz", "dt", "mn", "l", "r" };
string ConvertOtherLettersToDigits(string name, string arr[]) {

    for (int i = 1; i < name.length(); i++) {
        for (int j=0; j < 7; j++) { // arr.size() not working so used j < 7;

             string placeholder;
             placeholder = arr[j];
            for (int w = 0; w < placeholder.length(); w++) {
                if (char(placeholder[w]) == char(name[i])    ) {
                    name[i] = integerToChar(j);
                }
            }
        }
    }
    return name;
}
string RemoveDuplicates(string name) {
    int j = 0;
    for (int i=1; i < name.length(); i++) {
        if (name[j] != name[i]) {
            j++;
            name[j] = name[i];
        }
    }
        j++;
        name.erase(j, (name.length()-j) );
        // '\0' is the null string that terminates the rest of the string
        // name[j] = '\0';

    //cout << name << endl;
    return name;
}
string RemoveZeroes(string name) {
    for (int i=0; i < name.length(); i++) {
        if (name[i] == integerToChar(0)) {
            name.erase(i, 1);
        }
    }
    return name;
}
string MakeFourLetters(string name) {
    int index = 4;
    if (name.length() > 4) {
        name.erase(index);
    } else if (name.length() < 4) {
        int numZeroes = 4 - name.length();
        for (int i = 0; i < numZeroes; i++) {
            name += integerToChar(0);
        }
    }
    return name;
}
string Soundex() {
    string name;
    cout << "Enter surname to put into Soundex algorithm (RETURN to quit)" << endl;
    cin >> name;

    if (!name.empty()) {
        name = Capitalize(name);
        name = ConvertOtherLettersToDigits(name, letterDigits);
        name = RemoveDuplicates(name); // not done
        name = RemoveZeroes(name);
        name = MakeFourLetters(name);

        cout << name << endl;

    }

   return name;
}
/* Problem 5 */
void PrintScores(vector<int> &vec) {

    Vector<int> hist;

    for (int i=0; i < 10; i++) {
        hist.add(0);
    }

    for (int i=0; i < vec.size(); i++) {
        int tally = vec[i] / 10;
        hist[tally]++;
    }

    for (int i=0; i < hist.size(); i++) {
        cout << integerToString(i*10) + "-" + integerToString((i*10)+9) + ": ";
        for (int j=0; j < hist[i]; j++) {
            cout << "X";
        }
        cout << endl;
    }
}
void ReadScores() {
    string filename;
    // cout << "What's the filename? (include .extension)" << endl;
    // cin >> filename;
    filename = "/Users/idodekerobo/Documents/baby\ mogul/Young\ Zuckerberg/CS106B/Lecture\ 3/Assign1SimpleC/src/scores.txt";
    Vector<int> scores;
    int currentScore;
    ifstream in;
    ofstream out;

    /*try {
        in.open(filename);
        while (true) {
            in >> currentScore;
            if (in.fail()) break; // no more lines
            scores.add(currentScore);
        }
    } catch (const ifstream::failure& e) {
        cout << "cannot open file" << endl;
    }
    in.close();
    */

    in.open(filename);
    string line;
    if (in.fail()) {
        cout << "couldn't open file" << endl;
    } else {
        while (getline(in, line)) {
            int num = stringToInteger(line);
            scores.add(num);
        }
    }
    in.close();

    // PrintScores(&scores);
    // function call won't work for some reason
    Vector<int> hist;

    for (int i=0; i < 10; i++) {
        hist.add(0);
    }

    for (int i=0; i < scores.size(); i++) {
        int tally = scores[i] / 10;
        hist[tally]++;
    }

    for (int i=0; i < hist.size(); i++) {
        cout << integerToString(i*10) + "-" + integerToString((i*10)+9) + ": ";
        for (int j=0; j < hist[i]; j++) {
            cout << "X";
        }
        cout << endl;
    }
}

int main() {
    /* if (IsPerfect(6)) {
        cout << "6 is perfect" << endl;
    } else {
        cout << "Nobody's perfect" << endl;
    } */

    /* Problem 1 */
   /* cout << "Problem #1" << endl;
    for (int i=1; i <= 10000; i++) {
        if (IsPerfect(i)) {
            cout << i << endl;
        }
    }
    cout << "=============================" << endl; */

    /* Problem 2 */
    //VoterSimulation();

    /* Problem 4 */
    Soundex();

    /* Problem 5 */
    //cout << "Problem #5" << endl;
    //ReadScores();
    //cout << "=============================" << endl;


    return 0;
}
