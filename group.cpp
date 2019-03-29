#include "group.h"

Group::Group(unsigned int size, State state)
{
    m_size = size;
    m_state = state;
}
Group::~Group(){

}

void Group::draw(QPainter *painter, int x, int y, int size){



    auto rect = QRect{x, y, size, size};
    switch(m_state){
        case empty:
            for(unsigned int i = 0; i < m_size; i++){
                auto rect = QRect{x + int(i) * size, y, size, size};
                painter->setPen(QPen{Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin});
                painter->drawRect(rect);
            }
        break;
        case block:
            for(unsigned int i = 0; i < m_size; i++){
                auto rect = QRect{x + int(i) * size, y, size, size};
                painter->fillRect(rect, QColor(0,0,0));
            }
        break;

        case cross:

            for(unsigned int i = 0; i < m_size; i++){
                auto rect = QRect{x + int(i) * size, y, size, size};
                painter->fillRect(rect, QColor(0,0,0));
                painter->setPen(QPen{Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin});
                painter->drawRect(rect);
                painter->setPen(QPen{Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin});
                int X = x + int(i) * size;
                painter->drawLine(X, y, X + size, y + size);
                painter->drawLine(X,y + size, X + size, y);
            }

        break;
    }


}
