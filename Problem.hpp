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


        
 
        
};

#endif
