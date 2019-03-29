#ifndef LINE_H
#define LINE_H
#include "cell.h"
#include <vector>
class Line
{
public:

    std::vector<unsigned int> m_settings;
    std::vector<Cell*> m_cells;
    unsigned int m_size;
    unsigned int N_settings;

    Line(std::vector<unsigned int> settings, std::vector<Cell*> cellSettings);

    Cell *getCell(unsigned int index){
        return m_cells[index];
    }

    void print();
    void preSolve();

    void addBlocks();

    void blockEdges();
    void blockGaps();

    void addCrosses();

    void crossLimits();

    void crossGaps();

    void trim();

};

#endif // LINE_H
