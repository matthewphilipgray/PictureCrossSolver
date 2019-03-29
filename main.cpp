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
#include "group.h"


int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

}



