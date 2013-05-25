#include "teacher.h"
#include <cstddef>
teacher::teacher()
{
}

bool teacher::init(unsigned int id, QString name, unsigned int lectureLoad, unsigned int practiceLoad, QSet<int> subjectsCanTeach){
    m_ID = id;
    m_name = name;
    m_subjectsCanTeach = subjectsCanTeach;
    m_lectureLoad = lectureLoad;
    m_practiceLoad = practiceLoad;
    resetLectureLoadCounter();
    resetPracticeLoadCounter();
    return true;
}

teacher *teacher::create(unsigned int id, QString name, unsigned int lectureLoad, unsigned int practiceLoad, QSet<int> subjectsCanTeach){
    teacher *obj = new teacher();
    if(obj && obj->init(id, name, lectureLoad, practiceLoad, subjectsCanTeach)){
        return obj;
    }
    delete obj;
    return NULL;
}
