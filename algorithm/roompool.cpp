#include "roompool.h"

roomPool::roomPool(QVector<room *> pool)
{
    m_pool = pool;
}

room* roomPool::getRandomRoom(){
    //qt random initialization
//    QTime time = QTime::currentTime();
//    qsrand((uint)time.msec());

    return m_pool.at((qrand() % (m_pool.count() - 1)) +1);
}
