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

// Thoughts: could consider this a graph with nodes and directional edges, use a modified Dijkstras?
struct node {
    int x;
    int y;
    char height;
    int distanceFromStart;
    bool visited;
};
int main(int argc, char** argv){
    std::ifstream inputFile;
    inputFile.open("input.txt");

    std::string input = "";
    std::vector<std::string> map;
    std::queue<node> unvisited;
    while(inputFile >> input) {
        map.push_back(input);
    }
    int height = map.size();
    int width = map.at(0).length();

    int startX, startY, endX, endY;
    // all data read in, now build node array
    node graph[height][width];
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            graph[i][j].height = map.at(i)[j];
            graph[i][j].distanceFromStart = 2000000;
            graph[i][j].visited = false;
            graph[i][j].x = j;
            graph[i][j].y = i;
            if(graph[i][j].height == 'S'){
                startX = j;
                startY = i;
                graph[i][j].height = 'a';
            }
            if(graph[i][j].height == 'E'){
                endX = j;
                endY = i;
                graph[i][j].height = 'z';
            }
        }
    }
    graph[startY][startX].visited = true;
    graph[startY][startX].distanceFromStart = 0;
    int y = startY;
    int x = startX;
    while(!(y == endY && x == endX)){
        //consider the note above the current node
        // if we can move to that node, and it would be the shortest path to that node,
        // update it.
        if(y > 0 && graph[y - 1][x].height - 1 <= graph[y][x].height 
                    && graph[y - 1][x].distanceFromStart > graph[y][x].distanceFromStart + 1){
            graph[y - 1][x].distanceFromStart = graph[y][x].distanceFromStart + 1;
            // if the node has already been visited, it stands to reason that its shortest path to
            // start has already been found since all edge lengths are 1
            // So if we reach this point, the node has not been properly visited.
            // In this way, we can skip the aspect of Dijkstra's that depends on visiting unvisited nodes in order
            // of current shortest path from the start node.
            unvisited.push(graph[y - 1][x]);
        }
        //repeat for the other 3 directions.
        // looking below
        if(y < height - 1 && graph[y + 1][x].height - 1 <= graph[y][x].height 
                    && graph[y + 1][x].distanceFromStart > graph[y][x].distanceFromStart + 1){
            graph[y + 1][x].distanceFromStart = graph[y][x].distanceFromStart + 1;
            unvisited.push(graph[y + 1][x]);
        }
        // looking left
        if(x > 0 && graph[y][x - 1].height - 1 <= graph[y][x].height 
                    && graph[y][x - 1].distanceFromStart > graph[y][x].distanceFromStart + 1){
            graph[y][x - 1].distanceFromStart = graph[y][x].distanceFromStart + 1;
            unvisited.push(graph[y][x - 1]);
        }
        //looking right
        if(x < width - 1 && graph[y][x + 1].height - 1 <= graph[y][x].height 
                    && graph[y][x + 1].distanceFromStart > graph[y][x].distanceFromStart + 1){
            graph[y][x + 1].distanceFromStart = graph[y][x].distanceFromStart + 1;
            unvisited.push(graph[y][x + 1]);
        }
        node next = unvisited.front();
        x = next.x;
        y = next.y;
        unvisited.pop();
    }
    std::cout << graph[endY][endX].distanceFromStart << std::endl;
}
