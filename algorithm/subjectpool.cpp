#include "subjectpool.h"
#include <cstddef>
subjectPool::subjectPool()
{
}

bool subjectPool::init(QVector<subject *> pool){
    m_pool = pool;
    return true;
}

subjectPool* subjectPool::createWithVector(QVector<subject *> pool){
    subjectPool *obj = new subjectPool();
    if(obj && obj->init(pool)){
        return obj;
    }
    delete obj;
    return NULL;
}

subject subjectPool::getRandomSubject(group *grp) const{
    //qt random initialization
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    subject *subj = NULL;

    for(int i = 0; i < this->m_pool.count(); i++){
        if( m_pool.at(i)->getCountCounter() &&
            m_pool.at(i)->getSemesters().contains(grp->getSemester()) &&
            m_pool.at(i)->getSpecialtyID() == grp->getSpecialtyID()){

            subj = m_pool.at(i);
            break;
        }
    }

    subj->decrementCountCounter();
    return *subj;
}

bool subjectPool::isHereAnySubject()
{
    foreach (subject *subj, m_pool) {
        if (subj->getCountCounter()) {
            return true;
        }
    }
    return false;
}
