#ifndef LESSON_H
#define LESSON_H

#include "group.h"
#include "subject.h"
#include "teacher.h"
#include "room.h"
#include "timepoint.h"

class lesson
{
    unsigned int m_type;//?

    group *m_group;
    subject *m_subject;

    teacher *m_teacher;
    room *m_room;

    timePoint *m_timePoint;
    unsigned int m_timeIndex;

public:
    lesson(group* grp, subject* sbj, teacher* tchr, room* rm, int time);

    //getters & setters
    unsigned int getType(){
        return m_type;
    }
    group* getGroup(){
        return m_group;
    }
    subject* getSubject(){
        return m_subject;
    }
    teacher* getTeacher(){
        return m_teacher;
    }
    room* getRoom(){
        return m_room;
    }
    timePoint* getTimePoint(){
        return m_timePoint;
    }
    unsigned int getTimeIndex(){
        return m_timeIndex;
    }

};

#endif // LESSON_H
