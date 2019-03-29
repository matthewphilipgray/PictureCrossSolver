#include "line.h"
#include <iostream>


unsigned int max(std::vector<unsigned int> vector){
    unsigned int max = vector[0];
    for (unsigned int i = 1; i < vector.size(); i++){

        if(max < vector[i]){
            max = vector[i];
        }

    }
    return max;
}

unsigned int sumVect(std::vector<unsigned int> vector){
    unsigned int sum = vector[0];

    for (unsigned int i = 1; i < vector.size(); i++){
        sum+=vector[i];
    }
    return sum;
}


Line::Line(std::vector<unsigned int> settings, unsigned int size)
{
    m_settings = settings;
    N_settings = m_settings.size();
    //initialises the line as an empty group the size of the board
    Group *emptyGroup = new Group(size, empty);
    m_groups.push_back(emptyGroup);
    N_groups = 1;
    m_start = 0;
    m_end = N_groups;
}


void Line::checkIfSolved(){

    bool solved = true;

    unsigned int i = 0;

    while (solved && i < N_groups){

        if (m_groups[i]->getState() == empty){
            solved = false;
        }
    }
    m_solved = solved;
}

void Line::setBlocks(unsigned int start, unsigned int end){



    unsigned int base = 0;

    for(unsigned int i = 0; i < m_start; i++){
        base += m_groups[i]->getSize();
    }

    //find the groups that contain the new blocks
    unsigned int total = 0;
    int startGroup = 100;
    int endGroup = 100;
    for(unsigned int i = m_start; i < m_end; i++){
        total += m_groups[i]->getSize();
        if(total > start && startGroup == 100){
            startGroup = int(i);
        }
        if(total > end && endGroup == 100){
            endGroup = int(i);
        }
    }

    if(startGroup == 100 || endGroup == 100){
        std::cout<<"ERROR: group not found in setBlocks()"<<std::endl;
    }
    std::cout<<"settings the blocks"<<std::endl;
    bool startIsEmpty = m_groups[startGroup]->getState() == empty;
    bool endIsEmpty = m_groups[endGroup]->getState() == empty;
    unsigned int blockSize = total;

    for(int i = endGroup; i >= startGroup; i--){
        if(m_groups[i]->getState() == cross){
            std::cout<<"ERROR: writing over crosses with blocks"<<std::endl;
        }
        delete m_groups[i];
        m_groups.erase(m_groups.begin() + i);

    }

    if(endIsEmpty){
        Group *endGroup = new Group(total - end, empty);
        blockSize -= (total - end);
        m_groups.insert(m_groups.begin() + startGroup, endGroup);
    }

    Group *group = new Group(blockSize, block);
    m_groups.insert(m_groups.begin() + startGroup, group);

    if(startIsEmpty){
        Group *startG = new Group(start, empty);
        blockSize -= start;
        m_groups.insert(m_groups.begin() + startGroup, startG);
        m_groups[startGroup + 1]->setSize(blockSize);
    }

    N_groups = m_groups.size();
    for(int i = 0; i < N_groups; i++){
        std::cout<<m_groups[i]->getSize()<<std::endl;

    }
}


void Line::edgesBlocks(){

    unsigned int total = sumVect(m_settings);

    if(m_end - m_start == 1){

        if(m_groups[m_start]->getState() == empty){

            unsigned int size = m_groups[m_start]->getSize();
            unsigned int diff = size - total;

            for(unsigned int set = 0; set < N_settings; set++){

                if(m_settings[set] > diff){

                    unsigned int base = set;
                    unsigned int top = N_settings - set - 1;

                    for(unsigned int j = 0; j < set; j++){
                        base += m_settings[j];
                    }
                    for(unsigned int j = set + 1; j < N_settings; j++){
                        top += m_settings[j];
                    }
                    //sets the blocks using the start: size - top - m_settings[set]
                    //and the end (base + m_settings[set])
                    this->setBlocks(size - top - m_settings[set], base + m_settings[set]);

                }

            }


        }else{
            std::cout<<"ERROR: Solved blocked passed into edgesBlocks()"<<std::endl;
        }


    }

}

void Line::draw(QPainter *painter, int x, int y, int size){

    int groupx = x;
    int index = 0;

    for(unsigned int i = 0; i < N_groups; i++){

        m_groups[i]->draw(painter, groupx, y, size);

        groupx += int(m_groups[i]->getSize()) * size;
        std::cout<<index<<std::endl;



    }

}












