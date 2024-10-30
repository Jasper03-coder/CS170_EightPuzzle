#include <iostream>
#include <vector>
#include "Node.hpp"

using namespace std;

int main() {

    vector< vector<int> > puzzle1 = {{1,2,3},{4,5,6},{7,0,8}};
    Node* currState = new Node(puzzle1, nullptr, 0);

    cout << "Testing printNode() function" << endl;
    currState->printNode();
    cout << endl;

    cout << "Testing swapTiles() function" << endl;

    currState->swapTiles(2,1,2,2); // move blank right
    currState->printNode();
    cout << endl;

    cout << "Testing get functions" << endl;

    vector< vector<int> > puzzle2 = {{1,2,3},{4,5,6},{0,7,8}};
    Node* newState = new Node(puzzle2, nullptr, 0);
    cout << "The blank is in Row " << newState->getRow() << " Column " << newState->getCol() << endl << endl;

    


    return 0;
}