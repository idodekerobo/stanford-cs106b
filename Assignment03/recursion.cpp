/* 
 * TODO: put your own comments here. Also you should leave comments on
 * each of your methods.
 */

#include <math.h>
#include "recursion.h"
#include "map.h"
#include "vector.h"
#include "set.h"
#include "gwindow.h"
#include "gobjects.h"
#include "tokenscanner.h"
using namespace std;

int gcd(int a, int b) {
    if (b == 0) {
        cout << "gcd(" << a << ", " << b << ") = " << b << endl;
        return b;
    } else {
        cout << "gcd(" << a << ", " << b << ") = gcd(" << b << ", " << (a % b) << ")" << endl;
        return gcd(b, (a % b) );
    }
}

void drawTriangle(GWindow &w, double x, double y, int size) {
    w.drawLine(x, y, x+size, y);
    w.drawLine(x+size, y, x + size/2, y + size*sqrt(3)/2);
    w.drawLine(x, y, x+size/2, y + size*sqrt(3)/2);
}

void serpinskii(GWindow &w, int leftX, int leftY, int size, int order) {

    if (leftX < 0 || leftY < 0 || size < 0 || order < 0) {
        throw ("error");
    } else if (order==1) {
        drawTriangle(w, leftX, leftY, size);
        cout << "order: " << order << endl;
    } else {
        serpinskii(w, leftX, leftY, size/2, order-1);
        serpinskii(w, (leftX + size/2), leftY, size/2, order - 1);
        serpinskii(w, (leftX + size/4), (leftY + size/2*sqrt(3)/2), size/2, order-1);
    }
    cout << "[recursion serpinskii called]" << endl;
}

int doFloodFill(GBufferedImage& image, int x, int y, int newColor) {
    int number = 0;
    int originalColor = image.getRGB(x, y);

    // check if pixel has diff color and if image is in bounds
    if (image.inBounds(x, y) && image.getRGB(x, y) == originalColor) {
        number++;
        image.setRGB(x, y, newColor);
        // recur in multiple directions
        doFloodFill(image, x, y+1, newColor);
        doFloodFill(image, x+1, y, newColor);
        doFloodFill(image, x, y-1, newColor);
        doFloodFill(image, x-1, y, newColor);

//        doFloodFill(image, x+1, y-1, newColor);
//        doFloodFill(image, x-1, y-1, newColor);
//        doFloodFill(image, x+1, y+1, newColor);
    }
    return number;
}
int floodFill(GBufferedImage& image, int x, int y, int newColor) {
    // floodFill wrapper function
    int originalColor = image.getRGB(x, y);

    if (originalColor == newColor) return 0;

    doFloodFill(image, x, y, newColor);

    return 0;
}

void printPersonalCurriculum(Map<string, Vector<string>>& prereqMap, string goal, Set<string>& printedGoals) {

    //direct children of goals
    Vector<string> preReqs = prereqMap.get(goal);

    int numOfPreReqsForConcept = preReqs.size();

    if (numOfPreReqsForConcept == 0) {
        if (!printedGoals.contains(goal)) {
            cout << goal << endl; // base case
            printedGoals.add(goal);
        }
    } else {
        string newGoal;
        for (int i=0; i < numOfPreReqsForConcept; i++) {
            string newGoal = preReqs[i];
            if (newGoal == goal) break;
            printPersonalCurriculum(prereqMap, newGoal, printedGoals);
        }
        if (!printedGoals.contains(goal)) {
            cout << goal << endl; // base case
            printedGoals.add(goal);
        }
    }
}

void betterPrintPersonalCurriculum(Map<string, Vector<string>>& prereqMap, string goal, Set<string>& printedGoals) {
    if (prereqMap.containsKey(goal)) { // if it has prereqs
       for (string item: prereqMap[goal]) {
           betterPrintPersonalCurriculum(prereqMap, item, printedGoals); // recur on ea/ prereqs
       }
    }
    if (!printedGoals.contains(goal)) {
        cout << goal << endl; // base case, prints the first class to not have prereqs first
        printedGoals.add(goal);
    }
}
void personalCurriculum(Map<string, Vector<string>> & prereqMap,string goal) {
    Set<string> printedGoals;
    printPersonalCurriculum(prereqMap, goal, printedGoals);
}

// unfinished function
string generate(Map<string, Vector<string> > & grammar, string symbol) {
    cout << "my input" << endl;
    for (string i: grammar[symbol]) {
        cout << i << endl;
    }
    cout << "end my input" << endl;
    return "";
}
