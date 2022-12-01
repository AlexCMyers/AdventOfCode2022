#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>



int main(int argc, char** argv){
    std::ifstream inputFile;
    inputFile.open("input.txt");
    
    std::vector<int> elves;

    int currCalorieTotal = 0;
    int currCal = 0;

    std::string currLine = "";
    while(std::getline(inputFile, currLine)){
        //we've hit an empty line, add current running total to elves
        if(currLine.length() == 0){
            elves.push_back(currCalorieTotal);
            currCalorieTotal = 0;
        } else {
            std::stringstream temp(currLine);
            temp >> currCal;
            currCalorieTotal += currCal;
        }
    }

    int top1 = *std::max_element(elves.begin(), elves.end());
    elves.erase(std::max_element(elves.begin(), elves.end()));
    int top2 = *std::max_element(elves.begin(), elves.end());
    elves.erase(std::max_element(elves.begin(), elves.end()));
    int top3 = *std::max_element(elves.begin(), elves.end());
    elves.erase(std::max_element(elves.begin(), elves.end()));

    std::cout << top1 + top2 + top3 << std::endl;
    return 0;

}