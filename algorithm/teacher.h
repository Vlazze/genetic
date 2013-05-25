#ifndef TEACHER_H
#define TEACHER_H

#include <QObject>

class teacher
{
    unsigned int m_lectureLoad;
    unsigned int m_lectureLoadCounter;

    unsigned int m_practiceLoad;
    unsigned int m_practiceLoadCounter;

    unsigned int m_ID;
    QString m_name;

    bool init(unsigned int id, QString name,
              unsigned int lectureLoad, unsigned int practiceLoad);

public:
    explicit teacher();
    
    //getters & setters
    unsigned int getLectureLoad(){
        return m_lectureLoad;
    }
    unsigned int getPracticeLoad(){
        return m_practiceLoad;
    }
    unsigned int getLectureLoadCounter(){
        return m_lectureLoadCounter;
    }
    void resetLectureLoadCounter(){
        m_lectureLoadCounter = m_lectureLoad;
    }
    unsigned int getPracticeLoadCounter(){
        return m_practiceLoadCounter;
    }
    void resetPracticeLoadCounter(){
        m_practiceLoadCounter = m_practiceLoad;
    }
    unsigned int getID(){
        return m_ID;
    }
    QString getName(){
        return m_name;
    }

    static teacher* create(unsigned int id, QString name,
                           unsigned int lectureLoad, unsigned int practiceLoad);
    
};

#endif // TEACHER_H
