#ifndef SUBJECT_H
#define SUBJECT_H

#include <QtCore>

enum TypeOfSubject{
    lectureSubject = 1,
    practiceSubject = 2
};

class subject
{

private:
    unsigned int m_count;
    unsigned int m_countCounter;

    unsigned int m_ID;
    unsigned int m_specialtyID;
    QString m_title;

    QSet<int> m_semesters;

    TypeOfSubject m_type;

    bool init(unsigned int id, QString title, unsigned int specialtyID,
              unsigned int count,
              TypeOfSubject type, QSet<int> coursesSemesters);

public:
    explicit subject();
    
    ~subject(){
    }

    //getters & setters
    unsigned int getCount(){
        return m_count;
    }
    unsigned int getCountCounter(){
        return m_countCounter;
    }
    void resetCountCounter(){
        m_countCounter = m_count;
    }
    void decrementCountCounter(){
        m_countCounter--;
    }

    QString getTitle(){
        return m_title;
    }
    unsigned int getID(){
        return m_ID;
    }

    TypeOfSubject getType(){
        return m_type;
    }

    QSet<int> getSemesters(){
        return m_semesters;
    }

    unsigned int getSpecialtyID(){
        return m_specialtyID;
    }

    static subject* create(unsigned int id, QString title, unsigned int specialtyID,
                           unsigned int count,
                           TypeOfSubject type, QSet<int> coursesSemesters);

    
};

#endif // subject_H
