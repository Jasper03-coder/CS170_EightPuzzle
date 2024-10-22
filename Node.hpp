#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <vector>
using namespace std;

class Node{
    private: 
        vector<vector<int> > puzzle;
        Node* parent;
        int cost;
        int blank_row;
        int blank_col;

    public: 
        Node(vector<vector<int> > puzzle, Node* parent, int cost) {
            this->puzzle = puzzle;
            this->parent = parent;
            this->cost = cost;
            
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
                for(int column = 0; column < puzzle.at(row).size(); column++){
                    cout << puzzle.at(row).at(column);

                    if (column != puzzle.at(row).size() - 1) {
                    cout << " ";
                    }
                }
                cout << "\n";
            }
        } 

        void swapTiles(int curr_row, int curr_col, int new_row, int new_col) {
            int temp = this->puzzle.at(new_row).at(new_col); // save the value stored in the new position
            this->puzzle.at(new_row).at(new_col) = 0; // store the blank in the new position
            this->puzzle.at(curr_row).at(curr_col) = temp; // store the temp value in the curr position
        }
        
        int getRow() {
            return blank_row;
        }

        int getCol() {
            return blank_col;
        }
    };


// {1 2 3}
// {4 5 6}
// {7 8 0}

    

// {1 2 3}      {1 2 3}
// {4 5 6}  ->  {4 5 6}
// {7 0 8}      {7 8 0}

    

#endif
