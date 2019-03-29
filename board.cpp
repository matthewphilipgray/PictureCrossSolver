#include "board.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>




Board::Board(std::vector<std::vector<unsigned int>> settings [2])
{
    if (settings[0].size() == settings[1].size()){
        m_settings = settings;
        m_size = m_settings[0].size();

        for(unsigned int axis = 0; axis < 2; axis++){

            std::vector<Line*> lines;

            for(unsigned int i = 0; i < m_size; i++){

                Line *line = new Line(m_settings[axis][i], m_size);
                lines.push_back(line);
            }
            m_lines.push_back(lines);

        }




    }else{
        printf("Number of rows and columns must match: ");
        std::cout<<settings[0].size() << ", " << settings[1].size() << std::endl;
    }


}

void Board::iterate(){

    for(unsigned int axis = 0; axis < 1; axis++){
        for(unsigned int line = 0; line < m_size; line++){
            m_lines[axis][line]->edgesBlocks();
        }
    }
}

void Board::draw(QPainter *painter, int x, int y, int size){


    size /= int(m_size);
    int puzzleSize = int(m_size)*size;
    painter->fillRect(QRect(x, y, puzzleSize, puzzleSize), QColor(255,255,255));

    for(unsigned int line = 0; line < m_size; line++){
        int liney = y + int(line) * size;
        m_lines[0][line]->draw(painter, x, liney, size);
    }
    //draw the settings
    painter->setPen(QPen{Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin});
    int heightFactor = 3 * size;
    for(unsigned int i = 0; i < m_size; i++){


        std::string rowString = "";
        std::string colString = "";
        for (unsigned int j = 0; j < m_settings[0][i].size(); j++){
            rowString += std::to_string(m_settings[0][i][j]);
            if(j != m_size - 1) rowString += " ";
        }
        for (unsigned int j = 0; j < m_settings[1][i].size(); j++){
            colString += std::to_string(m_settings[1][i][j]);
            if(j != m_size - 1) colString += "\n";
        }
        auto colRect = QRect(x + int(i) * size, y - heightFactor, size, heightFactor);
        painter->drawRect(colRect);
        auto rowRect = QRect(x - heightFactor, y + int(i) * size, heightFactor, size);
        painter->drawRect(rowRect);
        painter->setFont(QFont("times", size/ 2));
        painter->drawText(rowRect, Qt::AlignCenter,QString::fromStdString(rowString));
        painter->drawText(colRect, Qt::AlignCenter,QString::fromStdString(colString));


    }
}








