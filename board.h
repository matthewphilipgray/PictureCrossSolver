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

    Board(std::vector<std::vector<unsigned int>>  settings [2]);
    ~Board();

    void iterate();

    void draw(QPainter *painter, int x, int y, int size);


};

#endif // BOARD_H
