#ifndef FILELOADER_H
#define FILELOADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

void parseString(std::string line, std::string delim, std::vector <std::string> *outVector){


    size_t pos = 0;
    std::string token;

    while ((pos = line.find(delim)) != std::string::npos) {
        token = line.substr(0, pos);
        outVector->push_back(token);
        line.erase(0, pos + delim.length());
    }
    outVector->push_back(line);


}

void unpackSettings(std::string filename, std::vector<std::vector<unsigned int>> outVector [2])
{
    std::ifstream file;
    file.open(filename);
    std::string line;

    int index = 0;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            std::vector<std::string> stringList;
            std::cout<<"line: "<<index<<std::endl;
            parseString(line, ",", &stringList);
            size_t listSize = stringList.size();
            for (size_t i = 0; i < listSize; i++){
                std::vector<std::string> settingsString;
                std::vector<unsigned int> settings;
                parseString(stringList[i], "+", &settingsString);
                for (size_t j = 0; j < settingsString.size(); j++){
                    unsigned int setting = 0;
                    std::stringstream dummy(settingsString[j]);
                    dummy >> setting;
                    settings.push_back(setting);
                }
                outVector[index].push_back(settings);
            }

            index++;
        }
    }else
    {
        std::cout<<"File doesn't exist"<<std::endl;
    }

    file.close();

}














#endif // FILELOADER_H
