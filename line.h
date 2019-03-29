#ifndef LINE_H
#define LINE_H
#include "group.h"
#include <vector>

#include<QPainter>

class Line
{
public:

    std::vector<unsigned int> m_settings;    
    unsigned int N_settings;
    std::vector<Group*> m_groups;
    unsigned int N_groups;
    //m_start and m_end are used to define where the logic is used as
    //do not need to iterate over blocks or crosses at the start or end
    unsigned int m_start;
    unsigned int m_end;
    bool m_solved = false;

    Line(std::vector<unsigned int> settings, unsigned int size);

    void checkIfSolved();

    void setBlocks(unsigned int start, unsigned int end);

    void edgesBlocks();

    void draw(QPainter *painter, int x, int y, int size);

};

#endif // LINE_H
