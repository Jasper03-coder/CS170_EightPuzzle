#include <iostream>
#include<sstream>
#include <vector>

#include "Node.hpp"
#include "Problem.hpp"

using namespace std;

int main() {

    cout << "Welcome to 862288730, 862277791, and XXX 8 puzzle solver." << endl;

    cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
    int puzzleType;
    cin >> puzzleType;

    while (puzzleType != 1 && puzzleType != 2) {
        cout << "\nPlease type a valid digit" << endl;
        cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
        cin >> puzzleType;
    }

    vector< vector<int> > goal = {{1,2,3},{4,5,6},{7,8,0}};
    Node* goalState = new Node(goal, nullptr, 0);
    vector< vector<int> > default_initial; 
    vector< vector<int> > custom_initial;

    bool defaultPuzzle = true;

    if (puzzleType == 1) { // Default puzzle ---------------
        
        default_initial = {{1,2,3}, {4,8,0}, {7,6,5}};

    }
    else if (puzzleType == 2) { // Custom puzzle ----------------

        cout << "Enter your puzzle, use a zero to represent the blank" << endl;
        cout << "Enter the first row, use space or tabs between numbers" << endl;
        
        string row;
        stringstream ss;
        int value;

        cin.ignore();
        getline(cin, row);
        ss << row;

        
        vector<int> row1;
        for (int i = 0; i < 3; i++) {
            ss >> value;
            row1.push_back(value);
        }
        custom_initial.push_back(row1);

        cout << "Enter the second row, use space or tabs between numbers" << endl;

        ss.clear();
        getline(cin, row);
        ss << row;
        vector<int> row2;
        for (int i = 0; i < 3; i++) {
            ss >> value;
            row2.push_back(value);
        }
        custom_initial.push_back(row2);

        cout << "Enter the third row, use space or tabs between numbers" << endl;

        ss.clear();
        getline(cin, row);
        ss << row;
        
        vector<int> row3;
        for (int i = 0; i < 3; i++) {
            ss >> value;
            row3.push_back(value);
        }
        custom_initial.push_back(row3);

        defaultPuzzle = false;
    }

    Node* initialState = nullptr;
    if (defaultPuzzle) {
        initialState = new Node(default_initial, nullptr, 0);
    }
    else {
        initialState = new Node(custom_initial, nullptr, 0);
    }


    cout << "\nEnter your choice of algorithm" << endl;
    cout << "1 for Uniform Cost Search" << endl;
    cout << "2 for A* with the Misplaced Tile Heuristic" << endl;
    cout << "3 for A* with the Euclidean distance Heuristic" << endl;

    int algorithm;
    cin >> algorithm;

    while (algorithm != 1 && algorithm != 2 && algorithm != 3) {
        cout << "\nPlease enter a valid digit" << endl;
        cout << "\nEnter your choice of algorithm" << endl;
        cout << "1 for Uniform Cost Search" << endl;
        cout << "2 for A* with the Misplaced Tile Heuristic" << endl;
        cout << "3 for A* with the Euclidean distance Heuristic" << endl;

        cin >> algorithm;
    }

    /*
    
        Add code if necessary
    
    */

    Problem* puzzle = new Problem(initialState, goalState);

    // run the algorithms here
    
    if (algorithm == 1) { // Uniform Cost Search

    }
    else if (algorithm == 2) { // Misplaced Tile 

        puzzle->MisplacedTilesSearch();

    }
    else if (algorithm == 3) { // Euclidean Distance
         
    }

    
     cout << "To solve this problem the search algorithm expanded a total of " << puzzle->getNodesExpanded() << " nodes." << endl;
     cout << "The maximum number of nodes in the queue at any one time: " << puzzle->getMaxQueue() << endl;
     cout << "The depth of the goal was " << puzzle->getDepth() << endl;
   

    return 0;
}