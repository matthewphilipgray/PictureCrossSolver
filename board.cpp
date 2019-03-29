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

        std::vector<Line*> cells;
        std::vector<Line*> cells_T;

        for (unsigned int i = 0; i < m_size; i++){
            std::vector<Cell*> row;
            for (unsigned int j = 0; j < m_size; j++){
                Cell *cell = new Cell(i, j);
                row.push_back(cell);
            }
            m_cells.push_back(row);
            Line *line = new Line(m_settings[0][i], row);
            cells.push_back(line);
        }
        m_lines.push_back(cells);

        for (unsigned int i = 0; i < m_size; i++){
            std::vector<Cell*> col;
            for (unsigned int j = 0; j < m_size; j++){
                Cell *cell = m_lines[0][j]->getCell(i);
                col.push_back(cell);
            }
            Line *line = new Line(m_settings[1][i], col);
            cells_T.push_back(line);
        }
        m_lines.push_back(cells_T);

        bool created = true;

    }else{
        printf("Number of rows and columns must match: ");
        std::cout<<settings[0].size() << ", " << settings[1].size() << std::endl;
    }


}

Board::~Board(){

        std::cout<<"deleting the board"<<std::endl;
        delete m_settings;
        for (int i = m_size - 1; i >= 0; i--){
            for (int j = m_size - 1; j >= 0; j--){

                delete m_cells[i][j];
            }

        }




}


void Board::printSettings()
{
    std::string names [] = {"Row", "Col"};

    for (int i = 0; i < 2; i++)
    {
        printf("%s settings: ", names[i].c_str());
        for (int j = 0; j < m_size; j++)
        {
            std::cout<<"(";

            for (size_t setting = 0; setting < m_settings[i][j].size(); setting++){
                std::cout<<m_settings[i][j][setting]<<", ";
            }

            std::cout<<")";

        }
        std::cout<<std::endl;

    }
}

void Board::printPuzzle(int axis){

    for (unsigned int i = 0; i < m_size; i++){
        for (unsigned int j = 0; j < m_size; j++){

            m_cells[i][j]->printState();
            if(j != m_size - 1) std::cout<<" ";
            else std::cout<<std::endl;

        }
    }
}

void Board::draw(QPainter *painter, int x1, int y1, int x2, int y2){

    int size = (x2 - x1);
    size /= m_size;
    painter->fillRect(QRect(x1, y1, m_size*size, m_size*size),QColor(255,255,255));


    for (unsigned int i = 0; i < m_size; i++){
        for (unsigned int j = 0; j < m_size; j++){

            m_cells[i][j]->draw(painter, x1 + j * size, y1 + i * size, size);
        }
    }
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
        auto colRect = QRect(x1 + i * size, y1 - heightFactor, size, heightFactor);
        painter->drawRect(colRect);
        auto rowRect = QRect(x1 - heightFactor, y1 + i * size, heightFactor, size);
        painter->drawRect(rowRect);
        painter->setFont(QFont("times", size/ 2));
        painter->drawText(rowRect, Qt::AlignCenter,QString::fromStdString(rowString));
        painter->drawText(colRect, Qt::AlignCenter,QString::fromStdString(colString));


    }
}

void Board::iterate(){

    this->preSolve();
    this->addCrosses();
    this->trimLines();




}


void Board::preSolve(){

    for(unsigned int axis = 0; axis < 2; axis++){
        for(unsigned int i = 0; i < m_size; i++){
            m_lines[axis][i]->preSolve();
        }
    }
}


void Board::addCrosses(){

    this->crossLimits();
    this->crossGaps();

}

void Board::addBlocks(){

}

void Board::blockEdges(){

    for(unsigned int axis = 0; axis < 2; axis++){
        for(unsigned int i = 0; i < m_size; i++){

            //m_lines[axis][i]->blockEdges();
            //m_lines[axis][i]->blockGaps();


        }

    }


}



void Board::crossLimits(){

    for(unsigned int axis = 0; axis < 2; axis++){
        for(unsigned int i = 0; i < m_size; i++){

            m_lines[axis][i]->crossLimits();
        }
    }

}




void Board::crossGaps(){

    for(unsigned int axis = 0; axis < 2; axis++){
        for(unsigned int i = 0; i < m_size; i++){
             m_lines[axis][i]->crossGaps();

        }
    }
}



void Board::trimLines(){

    for(unsigned int axis = 0; axis < 2; axis++){
        for(unsigned int i = 0; i < m_size; i++){
             m_lines[axis][i]->trim();

        }
    }
}









