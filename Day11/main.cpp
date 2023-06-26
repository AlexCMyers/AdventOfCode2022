#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

/* Day 10: Monkey in the middle */
struct Monkey {
    std::vector<int> items;
    std::function<int(int)> operation;
    int test;
    int trueMonkeyId;
    int falseMonkeyId;
};

std::function<int(int)> parseOperation(std::string op);

int main(int argc, char** argv){
    std::ifstream inputFile;
    inputFile.open("input.txt");

    std::vector<Monkey*> monkeys;

    /* Input example */
    /* Monkey 0:
     * Starting items: 79, 98
     * Operation: new = old * 19
     * Test: divisible by 23
     * If true: throw to monkey 2
     * If false: throw to monkey 3 */

    std::string input = "";
    std::string equation = "";
    int item = 0;
    int ind = 0;
    char col, com;
  
    while(inputFile >> input) {
        monkeys.push_back(new Monkey);
        inputFile >> ind >> col;
        inputFile >> input >> input;
        while(inputFile >> item){
            monkeys.at(ind)->items.push_back(item);
            inputFile >> com;
        }
        inputFile >> input >> input >> input >> input;
        std::getline(inputFile, equation);


    }
   
    return 0;
}

std::function<int(int)> parseOperation(std::string op){
    
}