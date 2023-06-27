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

std::function<int(int)> parseOperation(char op, std::string operand);

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
    int item = 0;
    int ind = 0;
    int tempNum = 0;
    char col, com;
    char op;
    std::string operand;
    /* Monkey */
    while(inputFile >> input) {
        monkeys.push_back(new Monkey);
        /* 0: */
        inputFile >> ind >> col;
        /* Starting items: */
        inputFile >> input >> input;
        while(inputFile >> item){
            monkeys.at(ind)->items.push_back(item);
            inputFile >> com;
        }
        /* Operation: new = old */
        inputFile >> input >> input >> input >> input;
        // the equations are always `old _ ()` where _ is either * or + and
        // () is either 'old' or a number
        /* * 19 */
        inputFile >> op >> operand;
        monkeys.at(ind)->operation = parseOperation(op, operand);
        /* Test: divisible by 23 */
        inputFile >> input >> input >> input >> tempNum;
        monkeys.at(ind)->test = tempNum;
        /* If true: throw to monkey 2 */
        inputFile >> input >> input >> input >> input >> input >> tempNum;
        monkeys.at(ind)->trueMonkeyId = tempNum;
        /* If false: throw to monkey 3 */
        inputFile >> input >> input >> input >> input >> input >> tempNum;
        monkeys.at(ind)->falseMonkeyId = tempNum;
    }

    // Monkeys go in order, and test each item they have
    for(auto m: monkeys) {
        for(auto item: m->items){
            // When a monkey inspects an item, the operation is performed
            item = m->operation(item);
            // When a monkey finishes inspecting an item, worry level is divided by 3
            item = item / 3;
            // TODO: Consider using a queue for the items 
            // since each monkey will always throw all of its items going in FCFS order 

        }
    }
   
    return 0;
}

std::function<int(int)> parseOperation(char op, std::string operand){
    if(operand == "old"){
        switch(op){
            case '*':
                return [](int x) { return x * x; };
                break;
            case '+':
                return [](int x) { return x + x; };
                break;
            default:
                std::cout << "error" << std::endl;
        }
    } else {
        int num = stoi(operand);
        switch(op){
            case '*':
                return [num](int x) { return x * num; };
                break;
            case '+':
                return [num](int x) { return x + num; };
                break;
            default:
                std::cout << "error" << std::endl;
        }
    }
}