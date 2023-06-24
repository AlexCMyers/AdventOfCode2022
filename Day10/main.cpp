#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

/* Day 10: Cathode Ray Tube
Input: a series of commands that can be of two types
    - "noop": takes 1 cycle, changes nothing
    - "addx V": takes 3 cycles to add V to X
register X starts with a value of 1

Problem 1: Figure out the value of X at every 20th cycle - the "signal strength"
Return the sum of all calculated signal strengths
*/

void printChar(int x, int cycle);
int main(int argc, char** argv){
    std::ifstream inputFile;
    inputFile.open("input.txt");

    std::string currentDirection = "?";
    int x = 1;
    int deltaX = 0;
    int cycleCount = 0;

    int sigStrength = 0;

    while(inputFile >> currentDirection){
        if(currentDirection != "noop"){
            inputFile >> deltaX;
            cycleCount++;
            if(cycleCount % 40 == 20)
                sigStrength += (cycleCount * x);
            cycleCount++;
            if(cycleCount % 40 == 20)
                sigStrength += (cycleCount * x);
            x += deltaX;
        } else {
            cycleCount++;
            if(cycleCount % 40 == 20)
                sigStrength += (cycleCount * x);
        }
    }
    std::cout << sigStrength << std::endl;


    /* Part 2 */
    /* It's revealed that X represents the horizontal, position of the center pixel of a 3-pixel-wide sprite
     * the CRT is 40 pixels wide, and 6 tall
     * Only horizontal position is considered here, if 40 < X < 80, it just means the sprite is on the second line
     * The CRT draws a single pixel during each cycle 
     * Output the drawing using '.' if the sprite is not present at the pixel currently being drawn and 
     * using '#' if the sprite is at that pixel */
    inputFile.clear();
    inputFile.seekg(std::ios::beg);
    x = 1;
    deltaX = 0;
    cycleCount = 0;

    while(inputFile >> currentDirection){
        if(currentDirection != "noop"){
            inputFile >> deltaX;
            printChar(x, cycleCount++);
            printChar(x, cycleCount++);
            x += deltaX;
        } else
            printChar(x, cycleCount++);
    }
}
void printChar(int x, int cycle) {
    if(abs((cycle%40) - x) < 2)
        std::cout << '#';
    else 
        std::cout << '.';
    if((cycle+1) % 40 == 0)
        std::cout << std::endl;
}
