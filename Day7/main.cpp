#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <stack>
#include <queue>
#include <set>
#include <map>

const int DISK_SPACE = 70000000;
const int SPACE_NEEDED = 30000000;

std::string getPathFromVec(std::vector<std::string> pathVec, std::string file){
    std::string path = "";
    for(std::string s: pathVec){
        path += s;
        path += " ";
    }
    path += file;
    return path;
}

int main(int argc, char** argv){
    std::ifstream inputFile;
    inputFile.open("input.txt");
    
    std::vector<std::string> currentPath;
    std::map<std::string, int> fileSizes;
    std::map<std::string, int> dirSizes;

    std::string cmd;
    std::string dir;
    std::string size;
    std::string currLine = "";

    bool prevLs = false;
    while(std::getline(inputFile, currLine)){
        std::stringstream currStream(currLine);
        // if it's a command
        if(currLine[0] == '$'){
            char temp;
            currStream >> temp;
            currStream >> cmd;
            if(cmd == "cd"){
                currStream >> dir;
                if(dir == ".."){
                    currentPath.pop_back();
                } else {
                    currentPath.push_back(dir);
                }
            }
        } else {
            currStream >> size;
            if(size != "dir"){
                int currSize = stoi(size);
                std::string fileName;
                currStream >> fileName;
                fileSizes[getPathFromVec(currentPath, fileName)] = currSize;
            }
        }
    }
    std::map<std::string, int>::iterator it;
    long totalFileSize = 0;
    for(it = fileSizes.begin(); it != fileSizes.end(); it++){
        totalFileSize += it->second;

        std::string filePath = it->first;
        std::istringstream fileISS(filePath);
        std::vector<std::string> directories(std::istream_iterator<std::string>{fileISS},
                                 std::istream_iterator<std::string>());
        // remove file name
        directories.pop_back();

        // complex due to concern of directories having the same name
        while(directories.size() > 0){
            std::string dirName = "";
            for(std::string s: directories){
                dirName += s + " ";
            }
            if(dirSizes.count(dirName) == 0){
                dirSizes[dirName] = 0;
            }
            dirSizes[dirName] = dirSizes[dirName] + it->second;
            directories.pop_back();
        }
    }

    int spaceAvailable = DISK_SPACE - totalFileSize;
    int amountNeededToDelete = SPACE_NEEDED - spaceAvailable;
    int currChosenSize = DISK_SPACE;
    //Need to find the smallest directory that's at least as big as the amountNeededToDelete
    for(it = dirSizes.begin(); it != dirSizes.end(); it++){
        if(it->second >= amountNeededToDelete && it->second <=currChosenSize){
            currChosenSize = it->second;
        }
    }

    std::cout << currChosenSize <<std::endl;

    return 0;

}