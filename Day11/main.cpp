#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>

/* Day 10: Monkey in the middle */
struct Monkey {
    std::queue<int> items;
    std::function<int(int)> operation;
    int test;
    int trueMonkeyId;
    int falseMonkeyId;
    int itemsInspected;
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
            monkeys.at(ind)->items.push(item);
            inputFile >> com;
        }
        monkeys.at(ind)->itemsInspected = 0;
        inputFile.clear();
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

    /* Part 2 challenge */
    // Must find a new way to keep worry levels "manageable" (not too large to overflow)
    // While still being sure to pass to the appropriate monkey for the sake of knowing how much
    // "monkey business" there is
    // Essentially, must maintain the worry level's divisibility by all the monkeys' tests
    
    // if num % x == y, then (num + nx) % x == y
    // could multiple all the test nums together and if the worry level exceeds that product,
    // subtract it
    // And subtracting a number over an over until your number is too small to subtract from is the
    // same as doing modulo

    int testProduct = 1;
    for(auto m: monkeys)
        testProduct = testProduct * m->test;
    int currItem;
    // Instructions for part 1 say to test for 20 rounds
    // Part 2 has 10000 rounds
    // Monkeys go in order, and test each item they have
    for(int i = 0; i < 10000; i++){
        for(auto m: monkeys) {
            while(!m->items.empty()){
                currItem = m->items.front();
                // When a monkey inspects an item, the operation is performed
                currItem = m->operation(currItem);
                m->itemsInspected++;
                // In part 1, When a monkey finishes inspecting an item, worry level is divided by 3
                // In part 2, that stops happening
                // currItem = currItem / 3;

                currItem = currItem % testProduct;

                // test the item and toss it to the corresponding monkey
                if(currItem % m->test == 0)
                    monkeys.at(m->trueMonkeyId)->items.push(currItem);
                else
                    monkeys.at(m->falseMonkeyId)->items.push(currItem);
                m->items.pop();
            }
        }
    }
    // calculating level of monkey business -> find 2 monkeys who inspected the most items
    // and multiply their inspectedItems counts together
    std::sort(monkeys.begin(), monkeys.end(), [] (Monkey* rhs, Monkey* lhs) {
        return rhs->itemsInspected > lhs->itemsInspected;});
    
    int monkeyBusiness = monkeys.at(0)->itemsInspected * monkeys.at(1)->itemsInspected;
    std::cout << monkeyBusiness << std::endl;
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