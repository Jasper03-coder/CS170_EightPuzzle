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
            if (currNode->getRow() == 0) {
                return nullptr;
            }

            Node* newNode = new Node(currNode->getPuzzle(), currNode, currNode->getCost() + 1); //  Create a new node with a copy of the current nodes puzzle

            // moving up means blank_row increments by 1 and blank_col remains the same
            newNode->swapTiles(currNode->getRow(), currNode->getCol(), currNode->getRow() - 1, currNode->getCol());
            newNode->decrementRow();

            return newNode;
        }

        Node* Down(Node* currNode) {
            if (currNode->getRow() == 2) {
                return nullptr;
            }

            Node* newNode = new Node(currNode->getPuzzle(), currNode, currNode->getCost() + 1); //  Create a new node with a copy of the current nodes puzzle

            // moving down means blank_row decrements by 1 and blank_col remains the same
            newNode->swapTiles(currNode->getRow(), currNode->getCol(), currNode->getRow() + 1, currNode->getCol());
            newNode->incrementRow();

            return newNode;

        }

        Node* Left(Node* currNode) {
            if (currNode->getCol() == 0) {
                return nullptr;
            }

            Node* newNode = new Node(currNode->getPuzzle(), currNode, currNode->getCost() + 1); //  Create a new node with a copy of the current nodes puzzle

            // moving left means blank_row remains and blank_col decrements by 1
            newNode->swapTiles(currNode->getRow(), currNode->getCol(), currNode->getRow(), currNode->getCol() - 1);
            newNode->decrementCol();

            return newNode;

        }

        Node* Right(Node* currNode) {
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

        int getMaxQueue() {
            return this->maxQueueSize;
        }

        int getNodesExpanded() {
            return this->nodesExpanded;
        }

        int getDepth() {
            return this->depth;
        }

 

        struct EDCompareCosts {
            bool operator() (Node* node1, Node* node2) {
                
                // for A* search return node1->f > node2->f where f = g + h
                vector< vector<int> > goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
                Node* goalState = new Node(goal, nullptr, 0);
                return node1->getCost() + node1->findEuclideanDistance(goalState) > node2->getCost() + node2->findEuclideanDistance(goalState);
            }
        };
        
        int EuclideanDistanceSearch() {
            priority_queue<Node*, vector<Node*>, EDCompareCosts> frontier;
            vector<Node*> explored;
            frontier.push(initialState);

            while(!frontier.empty()) {

                // check if the current size of the frontier is bigger than the maxQueueSize 

                Node* current = frontier.top();
                frontier.pop();

                // print the node

                if (isGoalState(current)) {
                    printSolution(current);
                    return 0;
                }

                if (!isExplored(current, explored)) {
                    explored.push_back(current);

                    // use the operators to expand the nodes and if the new node is not explored, then add it to the frontier


                    Node* newState = Up(current); 
                    if (newState != nullptr) { // if Up is a valid move

                        if (!(isExplored(newState, explored)) ) { // if the state has not been explored
                            frontier.push(newState); // add it to the frontier
                        }
                        
            
                    }

                    newState = Down(current);
                    if (newState != nullptr) { // if down is a valid move

                        if (!isExplored(newState, explored)) { // check if the state has not been explored
                            frontier.push(newState); // add it to the frontier
                        }
                        
                    }

                    newState = Left(current);
                    if (newState != nullptr) { // if Left is a valid move

                        if (!isExplored(newState, explored)) { // check if the state has not been explored
                            frontier.push(newState); // add it to the frontier
                        }
            
                    }

                    newState = Right(current); 
                    if (newState != nullptr) { // if right is a valid move

                        if (!isExplored(newState, explored)) { // check if the state has not been explored
                            frontier.push(newState); // add it to the frontier
                        }
            
                    }


                }


            
            
            }
            return -1;
        }



        
 
        
};

#endif