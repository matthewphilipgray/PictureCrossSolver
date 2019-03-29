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


Line::Line(std::vector<unsigned int> settings, std::vector<Cell*> cellSettings):
    m_settings(settings), m_cells(cellSettings)
{
    m_size = m_cells.size();
    N_settings = m_settings.size();
    std::cout<<m_size<<" "<<N_settings<<std::endl;
}

void Line::print(){

    for(int i = 0; i < m_size; i++){

        m_cells[i]->printState();

    }


}

void Line::preSolve(){

    std::vector<unsigned int> indexs;
    std::vector<unsigned int> diffs;

    unsigned int total  = N_settings - 1;

    for(unsigned int setting = 0; setting < N_settings; setting++){
        total += m_settings[setting];

    }
    unsigned int diff = m_size - total;

    for(unsigned int setting = 0; setting < N_settings; setting++){
        if (m_settings[setting] > diff){

            unsigned int base = setting;
            unsigned int top = N_settings - setting - 1;

            for(unsigned int j = 0; j < setting; j++){
                base += m_settings[j];
            }
            for(unsigned int j = setting + 1; j < N_settings; j++){
                top += m_settings[j];
            }
            for(unsigned int cell = m_size - top - m_settings[setting]; cell < base + m_settings[setting]; cell++){

                m_cells[cell]->setState(block);

            }


        }
    }
}

void Line::crossLimits(){


    if(N_settings == 1){
        unsigned int index = 0;
        unsigned int amount = 0;
        bool triggered = false;
        for(unsigned int j = 0; j < m_size; j++){
            if (m_cells[j]->getState() == block){

                if(amount == 0){
                    index = j;
                    amount++;
                    triggered = true;
                }else{
                    amount++;
                }
            }
        }
        unsigned int diff = m_settings[0] - amount;
        if (triggered){
            unsigned int limit =  (index > diff) ? index - diff : 0;
            for(unsigned int j = 0; j < limit; j++){
                m_cells[j]->setState(cross);
            }
            for(unsigned int j = index + amount + diff; j < m_size; j++){
                m_cells[j]->setState(cross);
            }
        }


    }


}

void Line::crossGaps(){

    unsigned int gapSize = 0;
    unsigned int blocks = 0;
    bool inBlock = false;

    for(unsigned int j = 0; j < m_size; j++){

        State cellState = m_cells[j]->getState();

        if(cellState == block){
            inBlock = true;
            gapSize = 0;
        }else if(cellState == empty){
            if (!inBlock){
                gapSize++;
            }
        }else if(cellState == cross){

            if (gapSize > 0){
                unsigned int min = m_settings[blocks];
                for(unsigned int set = blocks + 1; set < m_settings.size(); set++){

                    min = (min < m_settings[set]) ? min : m_settings[set];

                }

                if (min > gapSize){
                    for (unsigned int set = j - gapSize; set < j; set++){
                        m_cells[set]->setState(cross);
                    }
                }

            }
            gapSize = 0;
            inBlock = false;

        }
    }
    if (gapSize > 0){
        unsigned int min = m_settings[blocks];
        for(unsigned int set = blocks + 1; set < m_settings.size(); set++){

            min = (min < m_settings[set]) ? min : m_settings[set];

        }

        if (min > gapSize){
            for (unsigned int set = m_size - gapSize; set < m_size; set++){
                m_cells[set]->setState(cross);
            }
        }

    }

}

void Line::trim(){


    while (m_cells[0]->getState() == cross){
        m_cells.erase(m_cells.begin());
        m_size--;
    }
    while (m_cells[m_size-1]->getState() == cross && m_size > 0){
        m_cells.pop_back();
        m_size--;
    }
    while (m_cells[0]->getState() == block && m_size > 0){
        m_cells.erase(m_cells.begin());
        m_size--;
        if (--m_settings[0] == 0){
            m_settings.erase(m_settings.begin());
            N_settings--;
        }

    }
    while (m_size > 0 && m_cells[m_size - 1]->getState() == block){
        m_cells.erase(m_cells.begin());
        m_size--;
        if (--m_settings[0] == 0){
            m_settings.erase(m_settings.begin());
            N_settings--;
        }

    }

}

void Line::blockEdges(){}

void Line::blockGaps(){

    int N_bigger = 0;
    std::vector<unsigned int> blockSize;
    std::vector<unsigned int> indexs;
    unsigned int blockNumber = 0;
    for(unsigned int i = 0; i < m_size; i++){

        if(m_cells[i]->getState() == block){

            if (blockSize.size() == blockNumber){
                blockSize.push_back(1);
                indexs.push_back(i);
            }else{
                blockSize[blockNumber-1]++;
            }

        }else if(blockSize.size() != blockNumber){
            blockNumber++;
        }
    }


    for(unsigned int i = 0; blockSize.size()-1; i++){

        unsigned int min = blockSize[i] < blockSize[i+1] ? blockSize[i] : blockSize[i+1];
        N_bigger = 0;
        for(unsigned int setting = 0; setting < m_settings.size(); setting++){
            if (m_settings[setting] > min){
                N_bigger++;
            }

        }
        if(N_bigger == 1){
            for(unsigned int j = indexs[i] + blockSize[i] - 1; j < indexs[i+1]; j++){
                std::cout<<j<<" "<<indexs[i]<<" "<<indexs[i+1]<<std::endl;
                m_cells[j]->setState(block);

            }
        }


    }







}





