#include "UniformCostSearch.hpp"
#include "Problem.hpp"
#include "Node.hpp"
#include <queue>
#include <set>
#include <vector>
#include <iostream>

// Structure for the priority queue to handle Nodes by cumulative cost
struct CompareCost {
    bool operator()(Node* const& n1, Node* const& n2) {
        return n1->getCost() > n2->getCost();
    }
};

void uniformCostSearch(const Problem& problem) {
    // Priority queue to select the node with the lowest cumulative cost
    std::priority_queue<Node*, std::vector<Node*>, CompareCost> pq;
    std::set<std::vector<std::vector<int>>> visited;

    // Start with the initial state of the problem
    Node* startNode = problem.getInitialState();
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
        if (problem.isGoalState(current)) {
            std::cout << "Goal reached with path cost: " << current->getCost() << std::endl;
            problem.printSolution(current);
            std::cout << "Nodes expanded: " << nodesExpanded << std::endl;
            std::cout << "Maximum queue size: " << maxQueueSize << std::endl;
            std::cout << "Depth of goal node: " << current->getCost() << std::endl;
            return;
        }

        // If state has already been visited, skip further expansion
        if (visited.find(current->getPuzzle()) != visited.end()) {
            continue;
        }

        // Mark the current state as visited
        visited.insert(current->getPuzzle());
        nodesExpanded++;

        // Expand the current node and add all valid children to the priority queue
        std::vector<Node*> children = problem.expand(current);
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
