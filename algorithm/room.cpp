#include "room.h"
#include <cstddef>
room::room()
{
}

bool room::init(unsigned int id, unsigned int number, TypeOfRoom type){
    m_ID = id;
    m_number = number;
    m_type = type;
    return true;
}

room* room::create(unsigned int id, unsigned int number, TypeOfRoom type){
    room *obj = new room();
    if(obj && obj->init(id, number, type)){
        return obj;
    }
    delete obj;
    return NULL;
}
