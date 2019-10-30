#include <iostream>
#include "console.h"
#include "vector.h"
#include "queue.h"
#include "stack.h"
#include "tokenscanner.h"
#include "map.h"
#include <fstream>
#include "grid.h"
//#include <iterator>
using namespace std;

/* Problem 1 */
struct emailMsg {
    Vector<string> to;
    string from;
    string message;
    string subject;
    int date;
    int time;
};

Vector<emailMsg> inbox;

void RemoveSpam(Vector<emailMsg> &inbox) {
    for (int i=0; i < inbox.size(); i++) {
        string subject = inbox[i].subject;
        if (subject.find("SPAM", 0) != string::npos) {
            inbox.remove(i);
            // have to decrement i, because you'll skip an element due to removing
            // the current one and having every other element shift left
            i--;
        }
    }
}

string GetLastToAddress(emailMsg email) {
    int lastIndex = email.to.size() - 1;
    string address = email.to[lastIndex];
    return address;
}

/*Problem 2*/
void ReverseQueue(Queue<int> &q) {
    Stack<int> flipped;

    // uses a stack to add the first queue element to stack which will make it last to come off
    while (!q.isEmpty()) {
        int i = q.dequeue();
        flipped.push(i);
    }

    // pops ea/ element off the stack back onto the queue which flips it
    while (!flipped.isEmpty()) {
        int i = flipped.pop();
        q.enqueue(i);
    }
}

/* Problem 3 */
void ScannerCheck(string htmlStr) {
    TokenScanner scan;
    scan.ignoreWhitespace();
    scan.setInput(htmlStr);

    while (scan.hasMoreTokens()) {
        cout << scan.nextToken() << endl;
    }
}
bool ProcessOpenTag(TokenScanner& scan, Stack<string> tagStack) {
    string tag = scan.nextToken();
    tagStack.push(tag); // pushes the actual element tag (no < or > or /) onto the stack
    return true;
}
bool ProcessCloseTag(TokenScanner& scan, Stack<string> tagStack) {
    string tag = scan.nextToken();
    if ((!tagStack.isEmpty()) && tag == tagStack.pop()) { // if tagStack isn't empty and the token we grabbed equals the most recent tag on Stack
        return true;
    } else {
        return false;
    }
}
bool ProcessTag(TokenScanner& scan, Stack<string>& tagStack) {
    // read next token to see if we found an open or a close tag
    string token = scan.nextToken();
    if (token == "/") {
        // if true that means it's a close tag
        return ProcessCloseTag(scan, tagStack);
    } else {
        // if false that means it's an open tag
        scan.saveToken(token); // pushes that token back into scan input so we can use it in next method
        return ProcessOpenTag(scan, tagStack);
    }
}
// buggy - gotta figure out how to fix
bool IsCorrectlyNested(string htmlStr) {
    Stack<string> tagStack;
    bool isCorrect = true;
    TokenScanner scan;
    scan.ignoreWhitespace();
    scan.setInput(htmlStr);

    while (scan.hasMoreTokens()) {
        string token = scan.nextToken();
        if (token == "<") {
            // do stuff - process
            if (!ProcessTag(scan, tagStack)) { // if ProcessTag is false
                isCorrect = false; // then the htmlStr is NOT correct, should be false
                break;
            }
            // get rid of ">" part of tag
            scan.nextToken();
        }
    }

    if (!tagStack.isEmpty()) isCorrect = false;

    return isCorrect;
}

/* Problem 4 */
char MostFrequentCharacter(ifstream &in, int &numOccurences) {

    Map<char, int> charMap;

//    while (true) {
//        if (in.fail()) break;

//        for (int i=0; i < line.length(); i++) {
//            char key = line[i];
//            if (charMap.containsKey(key)) {
//                charMap[key]++;
//            } else {
//                charMap.put(key, 1);
//            }
//        }
//    }
    int nextChar;
    // while there's a nextchar in the input file until end-of-file
    while ((nextChar = in.get()) != EOF) {

        // convert to string for lookup in the map
        char foundChar;
        foundChar += char(nextChar);

        // if we find it, increment the stored value, otherwise enter a new one
        int frequency = 1;
        if (charMap.containsKey(foundChar)) {
            frequency = charMap[foundChar] + 1;
        }
        charMap[foundChar] = frequency;
    }

    // use an iterator to go through the entire map
    Map<char, int>::iterator it = charMap.Map::const_iterator();

    numOccurences = 0;



};

/* Problem 5 */
void MarkBomb(int row, int col, Grid<int>& bombCounts, Grid<bool>& bombLocations) {
    for (int i= -1; i <= 1; i++) {
        for (int j=-1; j <= 1; j++) {
            if (bombLocations[row + i][col + j]) {
                bombCounts[row][col]++;
            }
        }
    }
}
Grid<int> MakeGridOfCounts(Grid<bool> &bombLocations) {
    Grid<int> bombCounts(bombLocations.numRows(), bombLocations.numCols());

    for (int row=0; row < bombLocations.numRows(); row++) {
        for (int col=0; col < bombLocations.numCols(); col++) {
            bombCounts[row][col] = 0;
        }
    }

    for (int row=0; row < bombLocations.numRows(); row++) {
        for (int col=0; col < bombLocations.numCols(); col++) {
            MarkBomb(row, col, bombCounts, bombLocations);
        }
    }
}

int main() {
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(8);
    q.enqueue(7);
    ReverseQueue(q);

    cout << endl;
    string htmlStr = "<html><b><i>CS106 rules!</i></b></html>";
    string htmlStr2 = "<html>test case</html>";
    IsCorrectlyNested(htmlStr2);

    //MakeGridOfCounts();
    return 0;
}
