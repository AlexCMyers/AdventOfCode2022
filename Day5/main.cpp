#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>



int main(int argc, char** argv){
    std::ifstream inputFile;
    inputFile.open("input.txt");
    
    std::stack <char> stacks[9];
    std::string init[8];

    for(int i = 0; i < 8; i++){
        std::getline(inputFile, init[i]);
    }

    for(int i = 7; i >= 0; i--){
        for(int j = 0; j < 9; j++){
            char c = init[i].at(4*j + 1);
            if(c != ' '){
                stacks[j].push(c);
            }
        }
    }

    std::vector<char> boxes;

    int pointTotal = 0;
    int points = 0;

    std::string currLine = "";
    std::getline(inputFile, currLine);
    std::getline(inputFile, currLine);
    while(std::getline(inputFile, currLine)){
        std::stringstream temp(currLine);
        std::string trash;
        int numBoxes;
        int src;
        int dest;

        temp >> trash >> numBoxes >> trash >> src >> trash >> dest;
        boxes.clear();
        for(int i = 0; i < numBoxes; i++){
            boxes.push_back(stacks[src - 1].top());
            
            stacks[src - 1].pop();
        }
        for(int i = boxes.size() - 1; i >= 0; i--){
            stacks[dest - 1].push(boxes.at(i));
        }
        
    }
    for(int i = 0; i < 9; i++){
        std::cout << stacks[i].top() << std::endl;
    }
    
    return 0;

}