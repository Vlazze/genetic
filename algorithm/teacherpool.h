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

    ~teacherPool(){
        qDeleteAll(m_pool);
    }

    teacher* getRandomTeacher();
    teacher* getTeacherAtIndex(int index){
        return m_pool.at(index);
    }

    //getters & setters
    int getCount(){
        return m_pool.count();
    }
};

#endif // TEACHERPOOL_H
