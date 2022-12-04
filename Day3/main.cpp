#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>



int main(int argc, char** argv){
    std::ifstream inputFile;
    inputFile.open("input.txt");
    std::string dict = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int pointTotal = 0;
    int points = 0;

    std::string first = "";
    while(std::getline(inputFile, first)){
        std::string second;
        std::string third;
        std::getline(inputFile, second);
        std::getline(inputFile, third);


        for(int i = 0; i < dict.length(); i++){
            if(first.find(dict[i]) != std::string::npos && second.find(dict[i]) != std::string::npos 
                && third.find(dict[i]) != std::string::npos){
                pointTotal += (i + 1);
            }
        }
    }

    std::cout << pointTotal << std::endl;
    return 0;

}