#include <iostream>
#include <vector>

#include "Problem.hpp"
#include "Node.hpp"
#include "MisplacedTilesSearch.hpp"
        
        
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

        
    