#ifndef ROOMPOOL_H
#define ROOMPOOL_H

#include <QtCore>
#include "room.h"

class roomPool
{
    QVector<room *> m_pool;

public:
    roomPool(QVector<room *> pool);

    ~roomPool(){
        qDeleteAll(m_pool);
    }

    room* getRandomRoom();

    //getters & setters
    int getCount(){
        return m_pool.count();
    }

    room* getRoomAtIndex(int index){
        return m_pool.at(index);
    }
};

#endif // ROOMPOOL_H
