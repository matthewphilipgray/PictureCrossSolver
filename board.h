#ifndef BOARD_H
#define BOARD_H
#include<vector>
#include<QPainter>
#include"line.h"

class Board
{
public:

    std::vector<std::vector<unsigned int>> *m_settings;
    unsigned int m_size;
    std::vector<std::vector<Line*>> m_lines;
    std::vector<std::vector<Cell*>> m_cells;


    Board(std::vector<std::vector<unsigned int>>  settings [2]);
    ~Board();


    void printSettings();

    void printPuzzle(int axis = 0);

    void draw(QPainter *painter, int x1, int y1, int x2, int y2);

    void preSolve();

    void addBlocks();
    void blockEdges();

    void addCrosses();

    void crossLimits();

    void crossGaps();

    void iterate();

    void trimLines();

};

#endif // BOARD_H
