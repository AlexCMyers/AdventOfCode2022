#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <queue>
#include <set>

int findStartInd(std::string s){
    std::stringstream temp(s);
    char circBuff[4];
    int currInd = 0;
    int result = 0;
    temp >> circBuff[0] >> circBuff[1] >> circBuff[2] >> circBuff[3];
    result = 4;

    while(!(circBuff[0] != circBuff[1] && circBuff[0] != circBuff[2] &&
            circBuff[0] != circBuff[3] && circBuff[1] != circBuff[2] &&
            circBuff[1] != circBuff[3] && circBuff[2] != circBuff[3])){
                temp >> circBuff[currInd];
                currInd = currInd == 3 ? 0 : currInd + 1;
                result++;
            }
    return result;
}

int findStartMessage(std::string s){
    std::stringstream temp(s);
    
    char circBuff[14];
    int currInd = 0;
    int result = 0;

    for(int i = 0; i < 14; i++){
        temp >> circBuff[i];
    }
    result = 14;

    bool unique = true;

    for(int i = 0; i < 14; i++){
        for(int j = 0; j < 14; j++){
            if((i != j) && (circBuff[i] == circBuff[j])){
                unique = false;
            }
        }
    }
    while(!unique){
        result++;
        temp >> circBuff[currInd];
        currInd = currInd == 13 ? 0 : currInd + 1;

        std::string myString(circBuff);
        std::set<char> charSet(myString.begin(), myString.end());

        //if all elements in current string are unique
        unique = charSet.size() == myString.size();

    }
    return result;
}

int main(int argc, char** argv){
    std::ifstream inputFile;
    inputFile.open("input.txt");
    
    
    
    int pointTotal = 0;
    int points = 0;

    std::string currLine = "";
    while(std::getline(inputFile, currLine)){
        std::cout << findStartMessage(currLine);
    }

    return 0;

}