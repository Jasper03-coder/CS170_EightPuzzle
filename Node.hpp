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
 /*
        Node(vector<vector<int>> puzzle, Node* parent, int cost);
        void printNode();
        void swapTiles(int curr_row, int curr_col, int new_row, int new_col);
*/
        Node(vector<vector<int> > puzzle, Node* parent, int cost) {
            this->puzzle = puzzle;
            this->parent = parent;
            this->g = cost;
            
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

// It should be checking if (column != puzzle.size() - 1) to prevent printing a space after the last element in the row.
        void printNode() {
            for(int row = 0; row < puzzle.size(); row++){ 
                for(int column = 0; column < puzzle.size(); column++){
                    cout << puzzle.at(row).at(column);
// column != puzzle.at(row).at(puzzle.size()
                    if (column != puzzle.size() - 1) { 
                    cout << " ";
                    }
                }
                cout << "\n";
            }
        } 

        void swapTiles(int curr_row, int curr_col, int new_row, int new_col) {
    // Check if both current and new positions are within the 3x3 grid bounds
    if (curr_row >= 0 && curr_row < 3 && curr_col >= 0 && curr_col < 3 &&
        new_row >= 0 && new_row < 3 && new_col >= 0 && new_col < 3) {
        
        // Perform the swap
        int temp = this->puzzle.at(new_row).at(new_col); // Save the value in the new position
        this->puzzle.at(new_row).at(new_col) = this->puzzle.at(curr_row).at(curr_col); // Move the blank tile
        this->puzzle.at(curr_row).at(curr_col) = temp; // Place the temp value in the current position
    } else {
        // If out of bounds, print an error message for debugging
        std::cout << "swapTiles attempted out-of-bounds access: (" 
                  << curr_row << ", " << curr_col << ") <-> ("
                  << new_row << ", " << new_col << ")\n";
    }
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
        
    };


// {1 2 3}
// {4 5 6}
// {7 8 0}

    

// {1 2 3}      {1 2 3}
// {4 5 6}  ->  {4 5 6}
// {7 0 8}      {7 8 0}

    

#endif
