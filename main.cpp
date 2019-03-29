#include "mainwindow.h"
#include <QApplication>
#include "board.h"

#include<vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>
#include "line.h"

void unpackSettings(std::string filename, std::vector<std::vector<unsigned int>> outvector [2]);
void parseString(std::string line, std::string delim, std::vector <std::string> *outVector);



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

}



