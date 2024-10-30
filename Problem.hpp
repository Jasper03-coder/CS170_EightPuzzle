#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include <iostream>
#include <vector>

#include "Node.hpp"

using namespace std;

class Problem {
    private:
        Node* initialState;
        Node* goalState;

    public:

        Problem(Node* initialState, Node* goalState) {
            this->initialState = initialState;
            this->goalState = goalState;
        }
        
       // Operators:

        Node* Up(Node* currNode) {
            if (currNode->getRow() > 0) { // Check that moving up is within bounds
                Node* newNode = new Node(currNode->getPuzzle(), currNode, currNode->getCost() + 1);
                newNode->swapTiles(currNode->getRow(), currNode->getCol(), currNode->getRow() - 1, currNode->getCol());
                newNode->decrementRow(); // Adjust as per swap direction
                return newNode;
            }
            return nullptr;
        }

        Node* Down(Node* currNode) {
            if (currNode->getRow() < 2) { // Check that moving down is within bounds
                Node* newNode = new Node(currNode->getPuzzle(), currNode, currNode->getCost() + 1);
                newNode->swapTiles(currNode->getRow(), currNode->getCol(), currNode->getRow() + 1, currNode->getCol());
                newNode->incrementRow(); // Adjust as per swap direction
                return newNode;
            }
            return nullptr;

        }

        Node* moveLeft(Node* currNode) {
            if (currNode->getCol() > 0) { // Check that moving left is within bounds
                Node* newNode = new Node(currNode->getPuzzle(), currNode, currNode->getCost() + 1);
                newNode->swapTiles(currNode->getRow(), currNode->getCol(), currNode->getRow(), currNode->getCol() - 1);
                newNode->decrementCol();
                return newNode;
            }
            return nullptr;

        }

        Node* moveRight(Node* currNode) {
            if (currNode->getCol() < 2) { // Check that moving right is within bounds
                Node* newNode = new Node(currNode->getPuzzle(), currNode, currNode->getCost() + 1);
                newNode->swapTiles(currNode->getRow(), currNode->getCol(), currNode->getRow(), currNode->getCol() + 1);
                newNode->incrementCol();
                return newNode;
            }
            return nullptr;

        }

        bool isGoalState(Node* current) { // Check if the current State is the goalState
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (current->getPuzzle().at(i).at(j) != goalState->getPuzzle().at(i).at(j)) { // if at least one tile is not in the right place, then it is not the goal state
                        return false;
                    }
                }
            }
            return true;
        }

        bool isExplored(Node* current, vector<Node*> explored) { // Check if the current state has already been explored
            if (explored.size() == 0) {
                return false;
            }
            for (int i = 0; i < explored.size(); i++) {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        if (current->getPuzzle().at(j).at(k) != explored.at(i)->getPuzzle().at(j).at(k)) { // If they aren't the same puzzle, then it has not been explored
                           return false;
                        }
                    }
                }
            }
            return true;
        }

        void printSolution(Node* current) { // Recursively print the solution path

            if (current->getParent() == nullptr) {
                cout << "Solution Path: " << endl << endl;
            }
            else {
                printSolution(current->getParent());
            }

            current->printNode();
            cout << endl << endl;
            
        }

        vector<Node*> expand(Node* currNode) {
            vector<Node*> children;

            if (Node* up = Up(currNode)) children.push_back(up);
            if (Node* down = Down(currNode)) children.push_back(down);
            if (Node* left = moveLeft(currNode)) children.push_back(left);
            if (Node* right = moveRight(currNode)) children.push_back(right);

            return children; // Return all possible moves
        }

        Node* getInitialState() {
            return this->initialState;
        }

        Node* getGoalState() {
            return this->goalState;
        }
  
        /* put into another file for
        
        
struct MTCompareCosts {
    bool operator() (Node* node1, Node* node2) {
        
        vector< vector<int> > goal = {{1,2,3}, {4,5,6}, {7,8,0}};
        Node* goalState = new Node(goal, nullptr, 0);

        return (node1->getCost() + node1->countMisplacedTiles(goalState)) > (node2->getCost() + node2->countMisplacedTiles(goalState));
    }
    
};

// Search algorithm to solve the 8 puzzle by A* Misplaced Tiles Search

void misplacedTilesSearch(Problem* problem) {
    priority_queue<Node*, vector<Node*>, MTCompareCosts > frontier; // priority queue to select the node with the lowest cost
    vector<Node*> explored;     // keep track of nodes we already explored
    frontier.push(problem->getInitialState());        // initialize the frontier using the initialState

    // Create and initialize variables since we removed it from the problems private variables
    int nodesExpanded = 0;
    int maxQueueSize = 0;

    while (!frontier.empty()) { // Check if the frontier is not empty
        
        if (frontier.size() > maxQueueSize) { // check if the size of the frontier is bigger than the maxQueue size
            maxQueueSize = frontier.size(); // Update if it is
        }

        Node* current = frontier.top(); // Get a leaf node from the frontier
        frontier.pop(); // Remove the leaf node from the frontier

        if (current == problem->getInitialState()) {
            // cout << "Expanding state" << endl;
            // current->printNode();
            nodesExpanded++;
            // cout << endl << endl;
        }
        else {
            // cout << endl;
            // current->printNode();
            // cout << "   Expanding this node..." << endl;
            // cout << endl;
            nodesExpanded++;
        }

        // Check if the current state is the goal state
        
        if (problem->isGoalState(current)) { // if it is the goal state, return the corresponding solution
            problem->printSolution(current); 
            cout << "Nodes expanded: " << nodesExpanded << endl;
            cout << "Maximum queue size: " << maxQueueSize << endl;
            cout << "Depth of goal node: " << current->getCost() << endl;
            return;
        }

        if (!problem->isExplored(current, explored)) { // check if the current state has been explored
            explored.push_back(current); // add it to the explored set

            // Use the operators to expand the current state

            Node* newState = problem->Up(current); 
            if (newState != nullptr) { // if Up is a valid move

                if (!problem->isExplored(newState, explored) ) { // if the state has not been explored
                    frontier.push(newState); // add it to the frontier
                }
                
    
            }

            newState = problem->Down(current);
            if (newState != nullptr) { // if down is a valid move

                if (!problem->isExplored(newState, explored)) { // check if the state has not been explored
                    frontier.push(newState); // add it to the frontier
                }
                
            }

            newState = problem->moveLeft(current);
            if (newState != nullptr) { // if Left is a valid move

                if (!problem->isExplored(newState, explored)) { // check if the state has not been explored
                    frontier.push(newState); // add it to the frontier
                }
    
            }

            newState = problem->moveRight(current); 
            if (newState != nullptr) { // if right is a valid move

                if (!problem->isExplored(newState, explored)) { // check if the state has not been explored
                    frontier.push(newState); // add it to the frontier
                }
    
            }

            
        }

    }
    
}

        
        */

 
 
        
};

#endif
