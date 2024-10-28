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
            if (currNode->getRow() == 0) {
                return nullptr;
            }

            Node* newNode = new Node(currNode->getPuzzle(), currNode, currNode->getCost() + 1); //  Create a new node with a copy of the current nodes puzzle

            // moving up means blank_row increments by 1 and blank_col remains the same
            newNode->swapTiles(currNode->getRow(), currNode->getCol(), currNode->getRow() + 1, currNode->getCol());
            newNode->incrementRow();

            return newNode;
        }

        Node* Down(Node* currNode) {
            if (currNode->getRow() == 2) {
                return nullptr;
            }

            Node* newNode = new Node(currNode->getPuzzle(), currNode, currNode->getCost() + 1); //  Create a new node with a copy of the current nodes puzzle

            // moving down means blank_row decrements by 1 and blank_col remains the same
            newNode->swapTiles(currNode->getRow(), currNode->getCol(), currNode->getRow() - 1, currNode->getCol());
            newNode->decrementRow();

            return newNode;

        }

        Node* left(Node* currNode) {
            if (currNode->getCol() == 0) {
                return nullptr;
            }

            Node* newNode = new Node(currNode->getPuzzle(), currNode, currNode->getCost() + 1); //  Create a new node with a copy of the current nodes puzzle

            // moving left means blank_row remains and blank_col decrements by 1
            newNode->swapTiles(currNode->getRow(), currNode->getCol(), currNode->getRow(), currNode->getCol() - 1);
            newNode->decrementCol();

            return newNode;

        }

        Node* right(Node* currNode) {
            if (currNode->getCol() == 2) {
                return nullptr;
            }

            Node* newNode = new Node(currNode->getPuzzle(), currNode, currNode->getCost() + 1); //  Create a new node with a copy of the current nodes puzzle

            // moving left means blank_row remains and blank_col increments by 1
            newNode->swapTiles(currNode->getRow(), currNode->getCol(), currNode->getRow(), currNode->getCol() + 1);
            newNode->incrementCol();

            return newNode;

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
                cout << "Solution Path: " << endl;
            }
            else {
                printSolution(current->getParent());
            }

            current->printNode();
        }


        
 
        
};

#endif
