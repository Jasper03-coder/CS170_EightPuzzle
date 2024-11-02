#include <iostream>
#include <vector>
#include <queue>
#include <set>

#include "Problem.hpp"
#include "Node.hpp"
#include "EuclideanDistanceSearch.hpp"
        
struct EDCompareCosts {
    bool operator() (Node* node1, Node* node2) {
        
        vector< vector<int> > goal = {{1,2,3}, {4,5,6}, {7,8,0}};
        Node* goalState = new Node(goal, nullptr, 0);
        return node1->getCost() + node1->findEuclideanDistance(goalState) > node2->getCost() + node2->findEuclideanDistance(goalState);
    }
    
};

void euclideanDistanceSearch(Problem* problem) {
    // Priority queue to select the node with the lowest cumulative cost
    std::priority_queue<Node*, std::vector<Node*>, EDCompareCosts> pq;
    std::set<std::vector<std::vector<int>>> visited;

    // Start with the initial state of the problem
    Node* startNode = problem->getInitialState();
    pq.push(new Node(startNode->getPuzzle(), nullptr, 0)); // Initialize with cost 0

    int nodesExpanded = 0;
    int maxQueueSize = 0;

    while (!pq.empty()) {
        // Update maximum queue size for statistics
        if (pq.size() > maxQueueSize) maxQueueSize = pq.size();

        // Pop the node with the lowest cost
        Node* current = pq.top();
        pq.pop();


        // Goal check
        if (problem->isGoalState(current)) {
            std::cout << "Goal reached with path cost: " << current->getCost() << std::endl;
            problem->printSolution(current);
            std::cout << "Nodes expanded: " << nodesExpanded << std::endl;
            std::cout << "Maximum queue size: " << maxQueueSize << std::endl;
            std::cout << "Depth of goal node: " << current->getCost() << std::endl;
            return;
        }

        if (pq.size() == 0) {
            cout << "Expanding state" << endl;
            current->printNode();
            nodesExpanded++;
            cout << endl << endl;
        }
        else {
            cout << endl;
            cout << "The best state to expand with g(n) = " << current->getCost() << " and h(n) = " << current->getH() << endl;
            current->printNode();
            cout << "   Expanding this node..." << endl;
            cout << endl;
            nodesExpanded++;
        }

        // If state has already been visited, skip further expansion
        if (visited.find(current->getPuzzle()) != visited.end()) {
            continue;
        }

        // Mark the current state as visited
        visited.insert(current->getPuzzle());

        // Expand the current node and add all valid children to the priority queue
        std::vector<Node*> children = problem->expand(current);
        for (Node* child : children) {
            if (visited.find(child->getPuzzle()) == visited.end()) {
                pq.push(new Node(child->getPuzzle(), current, current->getCost() + 1));
            }
        }
    }

    // If we exit the loop, the goal was not reachable
    std::cout << "Goal not reachable" << std::endl;
    std::cout << "Nodes expanded: " << nodesExpanded << std::endl;
    std::cout << "Maximum queue size: " << maxQueueSize << std::endl;
}
