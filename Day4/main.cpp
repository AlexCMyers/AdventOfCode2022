#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>



int main(int argc, char** argv){
    std::ifstream inputFile;
    inputFile.open("input.txt");
    
   // std::vector<int> elves;

    int count = 0;

    std::string currLine = "";
    while(std::getline(inputFile, currLine)){
        std::stringstream tempIn(currLine);

        char temp;
        int min1;
        int min2;
        int max1;
        int max2;

        tempIn >> min1 >> temp >> max1 >> temp >> min2 >> temp >> max2;

        if((min1 <= max2 && max1 >= min2) || (min2 <= max1 && max2 >= min1)){
            count++;
        }

        
    }

    std::cout << count << std::endl;
    return 0;

}