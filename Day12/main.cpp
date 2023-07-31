#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>

/* Day 12: Hill climbing algorithm */
/* Input */
// A rows of letters representing relative elevation (a as lowest, z as highest)
// starting point is marked by S and has elevation of a
// ending point is marked by E and has elevation of z
// I can only move orthogonally, to a spot at most 1 letter higher than my current spot
// Goal: how many steps will it take to go from S to E in as few moves as possible

// Thoughts: could consider this a graph with nodes and directional edges
// iteratively is possible, but costly, especially with the size of the input.

int main(int argc, char** argv){
    std::ifstream inputFile;
    inputFile.open("input.txt");

    std::string input = "";
    std::vector<std::string> map;

    while(inputFile >> input) {
    }
}
