#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


/* Day 8 challenge 
 * Goal: find a good location for a tree house */
/* Given an input of numbers representing tree height in a grid form
    Ex: ######
        ######
        ######
        ######
    Given tree X, if there is a tree the same height or taller than X 
    in any of the four cardinal directions starting from X, then tree X is hidden */

/* step one: determine how many trees are visible from outside the grid */

/* Thoughts */
// Should read into a 2D int array
// Easy way - loop through the entire grid and determine if the tree is visible from any of its sides
// but that would be exponential
// Better way:
//  As reading in, keep track of the largest height in each row and column
//  Count every edge tree as visible (2h + 2w - 4 visible trees along the edge)
//  look inward from each edge tree (disregard the corners, they're unnecessary)
//      and coutn the number of trees visible from each point on the edge
//      until hitting a tree that is the tallest
// Difficult case to remember: when there is one tree that's the max height in a row or column
//  don't count it twice
// worth it to have a 2D array of booleans to know which trees are already counted as visible?
//      yes, because multiple ways to accidentally count the same tree twice

int getVisibleCount(const std::vector<std::string> trees);
int main(int argc, char** argv){
    std::ifstream inputFile;
    inputFile.open("input.txt");
    
    // unknown width and height of the grid
    std::vector<std::string> trees;
    std::string currLine = "";

    while(std::getline(inputFile, currLine))
        trees.push_back(currLine);

    //now have vector of strings representing grid
    std::cout << std::endl << getVisibleCount(trees) << std::endl;
    return 0;
}

int getVisibleCount(const std::vector<std::string> trees) {
    int width = trees.at(0).length();
    int height = trees.size();

    bool visible[height][width];
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            visible[i][j] = false;
        }
    }
    int count = 0;

    char tallestTreesToLeft[height];
    char tallestTreesAbove[width];
    char tallestTreesToRight[height];
    char tallestTreesBelow[width];
    
    // set edge trees to visible
    for(int i = 0; i < width; i++){
        visible[0][i] = true;
        tallestTreesAbove[i] = trees.at(0).at(i);
        //assumption: height > 1
        visible[height - 1][i] = true;
        tallestTreesBelow[i] = trees.at(height - 1).at(i);
        count += 2;
    }
    for(int i = 1; i < height - 1; i++){
        visible[i][0] = true;
        tallestTreesToLeft[i] = trees.at(i).at(0);
        //assumption: width > 1
        visible[i][width - 1] = true;
        tallestTreesToRight[i] = trees.at(i).at(width - 1);
        count += 2;
    }

    
    for(int currCol = 1; currCol < height - 1; currCol++){
        //down each column from the top
        for(int currRow = 1; currRow < width - 1; currRow++){
            
        }
    }
    return count;
}