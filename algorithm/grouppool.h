#ifndef GROUPPOOL_H
#define GROUPPOOL_H

#include "group.h"
#include <QtCore>

class groupPool
{
    QVector<group *> m_pool;
    bool init(QVector<group *> pool);

public:

    explicit groupPool();

    static groupPool* createWithVector(QVector<group *> pool);

    QVector<group *> getGroupPool();

    int getCount(){
        return m_pool.count();
    }

};

#endif // GROUPPOOL_H
