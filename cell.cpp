#include "cell.h"
#include <iostream>


Cell::Cell(unsigned int row, unsigned int col, State state):
    m_row(row), m_col(col), m_cellState(state)
{
}

Cell::~Cell(){
    std::cout<<"delting cell"<<std::endl;
}

void Cell::printState(){

    switch(m_cellState){
        case empty: std::cout<<" "; break;
        case block: std::cout<<"*"; break;
        case cross: std::cout<<"X"; break;
    }
}



void Cell::draw(QPainter *painter,int x, int y, int size){
    auto rect = QRect{x, y, size, size};
    switch(m_cellState){
        case empty:
            painter->setPen(QPen{Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin});
            painter->drawRect(rect);
        break;

        case block:
            painter->fillRect(rect, QColor(0,0,0));
        break;

        case cross:
            painter->setPen(QPen{Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin});
            painter->drawRect(rect);
            painter->setPen(QPen{Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin});
            painter->drawLine(x, y, x + size, y + size);
            painter->drawLine(x,y + size, x + size, y);
        break;
    }

}
