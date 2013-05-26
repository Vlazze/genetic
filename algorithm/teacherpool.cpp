#include "teacherpool.h"

teacherPool::teacherPool(QVector<teacher *> tch)
{
    m_pool = tch;
}

teacher* teacherPool::getRandomTeacher(){
    //qt random initialization
//    QTime time = QTime::currentTime();
//    qsrand((uint)time.msec());

    return m_pool.at((qrand() % (m_pool.count() - 1)) +1);

//    teacher *teach = NULL;

//    for(int i = 0; i < this->m_pool.count(); i++){
//        if( m_pool.at(i)->getSemester().contains(sbj->getSemesters()) &&
//            m_pool.at(i)->getSpecialtyID() == sbj->getSpecialtyID()){

//            teach = m_pool.at(i);
//            break;
//        }
//    }
//    return *teach;
}
