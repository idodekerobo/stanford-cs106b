#include <iostream>
#include "console.h"
#include <fstream>
#include "vector.h"
#include "stringutils.h"
using namespace std;

/* Problem #1 */
void CensorString(string &myString, string remove) {
    string copy = "";
    bool match = false;
    for (int i=0; i < myString.length(); i++) {
        for (int j=0; j < remove.length(); j++) {

            if (remove[j] == myString[i]) {
                match = true;
            }

        }
        if (!match) {
            copy += myString[i];
        }
        match = false;
    }

    myString = copy;
}


/* Problem #2 */
struct examStats {
    double min;
    double max;
    double avg;
};

void analyzeExam(string filename, examStats exam) {
    ifstream in;
    ofstream out;

    in.open(filename);

    if (in.fail()) {
        cout << "File could not be opened" << endl;
    } else {
        double score;
        double totalScore = 0;
        double count = 0;

        /* hard code an impossible score so minimum automatically gets changed and works */
        double min = 101;
        double max = -1;

        while (true) {
            in >> score;
            if (in.fail()) {
                break; // no more lines
            }
            totalScore += score;
            count++;

            if (score > max) {
                max = score;
            }
            if (score < min) {
                min = score;
            }
        }

        exam.avg = totalScore / count;
        exam.max = max;
        exam.min = min;

        cout << "Midterm average: ";
        cout << exam.avg << endl;

        cout << "Lowest score: ";
        cout << exam.min << endl;

        cout << "Highest Score: ";
        cout << exam.max << endl;

    }
    in.close();
}

/* Problem #3 */
void CountLetters(string filename) {
    ifstream in;
    in.open(filename);

    string line;
    Vector<int> charVec;

    // initialize ea/ letter index at 0 to start
    for (int i=0; i < 26; i++) {
        //charVec[i] = 0;
        charVec.add(0);
    }

    if (in.fail()) {
        cout << "File couldn't be opened" << endl;
    } else {
        while (true) {
            if (in.fail()) break; //no more files to read

            getline(in, line);
            // make string of line lowercase
            for (int i=0; i < line.length(); i++) {
                // have to overwrite the string by assigning to line at that index
                line[i] = tolower(line[i]);
            }


            for (int i=0; i < line.length(); i++) {
                char ch = line[i];

                int index = int(ch) - 97; // convert char to ascii value and start at index 0 to 25

                // make sure that index doesn't grab characters outside the vector range - will kill the program
                if (index >= 0 && index < 26) {
                    charVec[index]++; //increment index by 1
                }
            }
        }
    }

    in.close();
    // print vector
    for (int i=0; i < 26; i++) {
        char currentLetter = 'a' + i;
        // cout << char(97) + ": " + integerToString(charVec[i]) << endl;
        cout << currentLetter<< ": " << charVec[i] << endl;
    }
}

int main() {

    /* Problem 1 */
    cout << "Problem #1" << endl;
    string someString = "Llamas like to laugh";
    CensorString(someString, "la");
    cout << someString << endl;
    cout << "===============================================" << endl;

    /* Problem 1 */
    cout << "Problem #2" << endl;
    examStats midtermStats;
    /* in C++ you need to copy the full file path for the file to work */
    analyzeExam("/Users/idodekerobo/Documents/baby\ mogul/Young\ Zuckerberg/CS106B/Lecture\ 3/SectionHandout01/src/midtermScores.txt", midtermStats);
    // cout << "Midterm Avergae: ";
    // cout << midtermStats.avg << endl;
    cout << "===============================================" << endl;

    /* Problem #3 */
    CountLetters("/Users/idodekerobo/Documents/baby\ mogul/Young\ Zuckerberg/CS106B/Lecture\ 3/SectionHandout01/src/vectors.txt");
    return 0;
}
