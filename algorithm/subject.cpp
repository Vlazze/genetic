#include "subject.h"
#include <cstddef>
subject::subject()
{
}

bool subject::init(unsigned int id, QString title, unsigned int specialtyID, unsigned int count,
                   TypeOfSubject type, QSet<int> semesters){
    m_ID = id;
    m_title = title;
    m_count = count;
    m_type = type;
    m_specialtyID = specialtyID;
    m_semesters = semesters;
    resetCountCounter();
    return true;
}

subject* subject::create(unsigned int id, QString title, unsigned int specialtyID, unsigned int count,
                         TypeOfSubject type, QSet<int> semesters){
    subject *obj = new subject();
    if (obj != NULL && obj->init(id, title, specialtyID, count, type, semesters)){
        return obj;
    }
    delete obj;
    return NULL;
}
