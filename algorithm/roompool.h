#ifndef ROOMPOOL_H
#define ROOMPOOL_H

#include <QtCore>
#include "room.h"

class roomPool
{
    QVector<room *> m_pool;

public:
    roomPool(QVector<room *> pool);

    room* getRandomRoom();

    //getters & setters
    int getCount(){
        return m_pool.count();
    }
};

#endif // ROOMPOOL_H
