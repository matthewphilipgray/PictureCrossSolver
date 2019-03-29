enum State {empty, block, cross};
#include <QPainter>
#ifndef CELL_H
#define CELL_H


class Cell
{

public:

    unsigned int m_row;
    unsigned int m_col;
    State m_cellState = empty;


    Cell(unsigned int row=0, unsigned int col=0, State state=empty);
    ~Cell();

    void changePlace(unsigned int row, unsigned int col){
        m_row = row; m_col = col;
    }
    void printState();
    State getState(){
        return m_cellState;
    }

    void draw(QPainter *painter,int x, int y, int size);

    void setState(State changeState){
        m_cellState = changeState;
    }
};



#endif // CELL_H
