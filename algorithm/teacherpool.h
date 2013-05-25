#ifndef TEACHERPOOL_H
#define TEACHERPOOL_H

#include <QtCore>
#include "teacher.h"
#include "subject.h"

class teacherPool
{
    QVector<teacher *> m_pool;
public:
    teacherPool(QVector<teacher *> tch);

    teacher* getRandomTeacher();

    //getters & setters
    int getCount(){
        return m_pool.count();
    }
};

#endif // TEACHERPOOL_H
