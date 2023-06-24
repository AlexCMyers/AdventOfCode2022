#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <stack>
#include <queue>
#include <set>
#include <map>

/* Day 9: Rope Bridge
The Head and Tail of the rope must always be adjacent (ortho or diag)
They start in the same spot
When the Head moves, the Tail will follow to keep adjacency
When they are in the same row or column, the Tail moves ortho to keep up
When they are not in the same row or colum, the Tail moves Diag to keep up
Assume begin with H at same position as T
First step - output number of unique locations the tail visits
*/

bool isAdjacent(int hx, int hy, int tx, int ty);
std::pair<int, int> updatedTail(int hx, int hy, int tx, int ty);
int main(int argc, char** argv){
    std::ifstream inputFile;
    inputFile.open("input.txt");

    std::set<std::pair<int, int>> visited;
    char currentDirection = '?';
    int numSteps = 0;

    //starting head and tail at same location
    int headX = 0;
    int headY = 0;
    int tailX = 0;
    int tailY = 0;

    visited.insert(std::make_pair(tailX, tailY));

    while(inputFile >> currentDirection){
        inputFile >> numSteps;
        for(int i = 0; i < numSteps; i++){
            //update the head
            if(currentDirection == 'R')
                headX++;
            if(currentDirection == 'L')
                headX--;
            if(currentDirection == 'U')
                headY++;
            if(currentDirection == 'D')
                headY--;
            //if the head has moved out of reach, we need to update the tail
            if(!isAdjacent(headX, headY, tailX, tailY)){
                std::pair<int, int> newTailPos = updatedTail(headX, headY, tailX, tailY);
                visited.insert(newTailPos);
                tailX = newTailPos.first;
                tailY = newTailPos.second;
            }
        }
    }

    std::cout << visited.size() << std::endl;

    /* Part 2 */
    /* Extend the math to work with a rope with 10 knots, where each one behaves as the head to the knot
        After it, and as the tail to the knot before it
    The inputs describe the motion of the first knot, and we want to keep track of
    the number of visited spots of the final knot */
    std::ifstream inputFile2;
    inputFile2.open("input2.txt");

    std::set<std::pair<int, int>> visited2;
    currentDirection = '?';
    numSteps = 0;

    //starting all knots at same location
    std::pair<int, int> knots[10];
    for(int i = 0; i < 10; i++){
        knots[i].first = 0;
        knots[i].second = 0;
    }

    visited2.insert(knots[9]);
    while(inputFile2 >> currentDirection){
        inputFile2 >> numSteps;
        for(int i = 0; i < numSteps; i++){
            //update the head
            if(currentDirection == 'R')
                knots[0].first++;
            if(currentDirection == 'L')
                knots[0].first--;
            if(currentDirection == 'U')
                knots[0].second++;
            if(currentDirection == 'D')
                knots[0].second--;
            //for each knot, see if the knot prior to it has now moved out of reach
            // if so, update it
            for(int i = 0; i < 9; i++){
                if(!isAdjacent(knots[i].first, knots[i].second, knots[i+1].first, knots[i+1].second))
                    knots[i + 1] = updatedTail(knots[i].first, knots[i].second, knots[i+1].first, knots[i+1].second);
            }
            visited2.insert(knots[9]);
        }
    }

    std::cout << visited2.size() << std::endl;
    return 0;   
}

bool isAdjacent(int hx, int hy, int tx, int ty) {
    // in same row and adjacent columns or in same column and adjacent rows
    // also accounts for overlapping positions, which can be considered adjacent for this puzzle
    bool ortho = (hx == tx && abs(hy-ty) < 2) || (hy == ty && abs(hx-tx) < 2);
    //both row and column indexes are 1 apart
    bool diag = abs(hy - ty) == 1 && abs(hx - tx) == 1;
    return ortho || diag;
}

std::pair<int, int> updatedTail(int hx, int hy, int tx, int ty) {
    //if the head is orthogonal to the tail in any direction, move in that direction
    if(hx == tx) {
        if(hy > ty)
            return std::make_pair(tx, ty + 1);
        else
            return std::make_pair(tx, ty - 1);
    }
    if(hy == ty) {
        if(hx > tx)
            return std::make_pair(tx + 1, ty);
        else
            return std::make_pair(tx - 1, ty);
    }

    // If this point is reached, then the head and tail are not on the same row or colum
    // move diagonally toward the head
    int newX = (hx > tx) ? tx + 1 : tx - 1;
    int newY = (hy > ty) ? ty + 1 : ty - 1;
    return std::make_pair(newX, newY);
}