
#ifndef GROUP_H
#define GROUP_H
enum State {empty, block, cross};

#include<QPainter>

class Group
{
public:

    State m_state;
    unsigned int m_size;

    Group(unsigned int size, State state);

    ~Group();

    unsigned int getSize(){
        return m_size;
    }
    void setSize(unsigned int size){
        m_size = size;
    }

    State getState(){
        return m_state;
    }
    void setState(State state){
        m_state = state;
    }

    void draw(QPainter *painter, int x, int y, int size);

};

#endif // GROUP_H
