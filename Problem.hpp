#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include <iostream>
#include <vector>
#include <queue>

#include "Node.hpp"

using namespace std;

class Problem {
    private:
        Node* initialState;
        Node* goalState;
        int maxQueueSize = 0;
        int nodesExpanded = 0;
        int depth = 0;

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
  

 
 
        
};

#endif