#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>
using namespace std;

class Node{
    private: 
        vector<vector<int> > puzzle;
        Node* parent;
        int g;
        int h;
        int blank_row;
        int blank_col;

    public: 
        Node(vector<vector<int> > puzzle, Node* parent, int cost) {
            this->puzzle = puzzle;
            this->parent = parent;
            this->g = cost;
            this->h = 0;
            
            // find the row and column of where the blank tile is at
            for (int i = 0; i < puzzle.size(); i++) {
                for (int j = 0; j < puzzle.at(i).size(); j++) {
                    if (puzzle.at(i).at(j) == 0) {
                        blank_row = i;
                        blank_col = j;
                    }
                }
            }
        }

        void printNode() {
            for(int row = 0; row < puzzle.size(); row++){ 
                for(int column = 0; column < puzzle.size(); column++){
                    cout << puzzle.at(row).at(column);

                    if (column != puzzle.size() - 1) { 
                    cout << " ";
                    }
                }
                if (row != 2) {
                    cout << "\n";
                }
                
            }
        } 

        void swapTiles(int curr_row, int curr_col, int new_row, int new_col) {
            int temp = this->puzzle.at(new_row).at(new_col); // save the value stored in the new position
            this->puzzle.at(new_row).at(new_col) = 0; // store the blank in the new position
            this->puzzle.at(curr_row).at(curr_col) = temp; // store the temp value in the curr position
            
        }

        vector< vector<int> > getPuzzle() {
            return puzzle;
        }
        
        Node* getParent() {
            return parent;
        }

        int getRow() {
            return blank_row;
        }
        
        int getCol() {
            return blank_col;
        }

        void incrementRow() { 
            blank_row += 1;
        }

        void decrementRow() { 
            blank_row -= 1;
        }

        void incrementCol() {
            blank_col += 1;
        }

        void decrementCol() {
            blank_col -= 1;
        }

        int getCost() {
            return g;
        }

        int getH() {
            return this->h;
        }

        int findEuclideanDistance(Node* goalState) {
            int distance = 0;
            int size = puzzle.size();

            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (puzzle.at(i).at(j) != 0) { // Do not include blank tile
                        int goalX;
                        int goalY;
                        for (int k = 0; k < size; k++) {
                            for (int l = 0; l < size; l++) {
                                if (puzzle.at(i).at(j) == goalState->getPuzzle().at(k).at(l)) {
                                    goalX = k;
                                    goalY = l;
                                    break;
                                }
                            }
                        }
                        distance += sqrt(pow(i- goalX, 2) + pow(j - goalY, 2));
                    }
                }
            }
            return distance;
        }
        

        int countMisplacedTiles(Node* goalState) {
            int count = 0;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) { 
                    if (puzzle.at(i).at(j) != goalState->getPuzzle().at(i).at(j)) {
                        count++; 
                    }
                }
            }

            this->h = count;
            return count;
        }  

    };


// {1 2 3}
// {4 5 6}
// {7 8 0}

    

// {1 2 3}      {1 2 3}
// {4 5 6}  ->  {4 5 6}
// {7 0 8}      {7 8 0}

    

#endif
