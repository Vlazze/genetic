#include "grouppool.h"

groupPool::groupPool()
{
}

bool groupPool::init(QVector<group *> pool){
    m_pool = pool;
    return true;
}

groupPool* groupPool::createWithVector(QVector<group *> pool){
    groupPool *obj = new groupPool();
    if(obj && obj->init(pool)){
        return obj;
    }
    delete obj;
    return NULL;
}

QVector<group *>  groupPool::getGroupPool(){
//    //qt random initialization
//    QTime time = QTime::currentTime();
//    qsrand((uint)time.msec());

//    int index = qrand() % m_pool.size();
//    group *groupInst = m_pool.at(index);


//    return *groupInst;
    return m_pool;
}
