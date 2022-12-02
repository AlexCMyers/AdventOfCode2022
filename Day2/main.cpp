#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>



int main(int argc, char** argv){
    std::ifstream inputFile;
    inputFile.open("input.txt");
    
    std::vector<int> elves;

    int pointTotal = 0;
    int points = 0;

    std::string currLine = "";
    while(std::getline(inputFile, currLine)){
        std::stringstream temp(currLine);

        char theirMove;
        char result;

        temp >> theirMove;
        temp >> result;

        if(result == 'X'){
            points = 0;
            if(theirMove == 'A'){
                points += 3;
            }else if(theirMove == 'B'){
                points += 1;
            }else{
                points += 2;
            }
        } else if (result == 'Y'){
            points = 3;
            if(theirMove == 'A'){
                points += 1;
            }else if(theirMove == 'B'){
                points += 2;
            }else{
                points += 3;
            }
        } else if (result == 'Z'){
            points = 6;
            if(theirMove == 'A'){
                points += 2;
            }else if(theirMove == 'B'){
                points += 3;
            }else{
                points += 1;
            }
        }
        pointTotal += points;

        

        
    }

    std::cout << pointTotal << std::endl;
    return 0;

}