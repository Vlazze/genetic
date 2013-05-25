#ifndef GROUP_H
#define GROUP_H

#include <QObject>

class group
{

    unsigned int m_ID;
    unsigned int m_number;
    unsigned int m_semester;

    unsigned int m_specialtyID;

    bool init(unsigned int id, unsigned int number,
              unsigned int semester, unsigned int specialtyID);

public:
    explicit group();

    //getters & setters
    unsigned int getID(){
        return m_ID;
    }
    unsigned int getNumber(){
        return m_number;
    }
    unsigned int getSemester(){
        return m_semester;
    }
    unsigned int getSpecialtyID(){
        return m_specialtyID;
    }


    static group* create(unsigned int id, unsigned int number,
                         unsigned int semester, unsigned int specialtyID);

    
};

#endif // GROUP_H
