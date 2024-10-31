#include <iostream>
#include <vector>

#include "Problem.hpp"
#include "Node.hpp"

using namespace std;

int main() {

    vector< vector<int> > goal = {{1, 2, 3}, {4, 5, 6}, {7,8,9}};
    vector< vector<int> > initial = {{1, 2, 3}, {4, 8, 5}, {7,0,6}};

    Node* goalState = new Node(goal, nullptr, 0);
    Node* initialState = new Node(initial, nullptr, 0);

    Problem* puzzle = new Problem(initialState, goalState);

    cout << "Testing isGoal(Node* current) " << endl;

    bool check = puzzle->isGoalState(initialState);

    if (!check) {
        cout << endl;
        cout << "Checking if the following puzzle is a goal state" << endl;
        cout << "{1, 2, 3}" << endl;
        cout << "{4, 8, 5}" << endl;
        cout << "{7, 0, 6}" << endl;
        
        cout << "It is not the goal state" << endl;
    }
    check = puzzle->isGoalState(goalState);

    if (check) {
        cout << endl;
        cout << "Checking if the following puzzle is a goal state" << endl;
        cout << "{1, 2, 3}" << endl;
        cout << "{4, 5, 6}" << endl;
        cout << "{7, 8, 0}" << endl;
        cout << "It is a goal state" << endl;
    }

    cout << endl;
    cout << "Testing isExplored(Node* current, vector<Node*> explored)" << endl << endl;

    vector<Node*> explored;

    explored.push_back(initialState);

    vector< vector<int> > vect = {{1, 2, 3}, {4, 5, 0}, {7,8,6}};
    Node* current = new Node(vect, nullptr, 0);

    

    check = puzzle->isExplored(initialState, explored);
    if (check) {
        cout << "Checking if the following state has already been explored" << endl;
        cout << "{1, 2, 3}" << endl;
        cout << "{4, 8, 5}" << endl;
        cout << "{7, 0, 6}" << endl;
        cout << "It has been explored!" << endl << endl;
    }
    check = puzzle->isExplored(current, explored);

    if (!check) {
        cout << "Checking if the following state has already been explored" << endl;
        cout << "{1, 2, 3}" << endl;
        cout << "{4, 5, 0}" << endl;
        cout << "{7, 8, 6}" << endl;
        cout << "It has not been explored!" << endl << endl;
    }

    
    return 0;
}