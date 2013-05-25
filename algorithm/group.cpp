#include "group.h"
#include <cstddef>
group::group()
{
}

bool group::init(unsigned int id, unsigned int number,
                 unsigned int semester, unsigned int specialtyID){
    m_ID = id;
    m_number = number;
    m_semester = semester;
    m_specialtyID = specialtyID;
    return true;
}

group* group::create(unsigned int id, unsigned int number,
                     unsigned int semester, unsigned int specialtyID){
    group *obj = new group();
    if(obj && obj->init(id, number, semester, specialtyID)){
        return obj;
    }
    delete obj;
    return NULL;
}
