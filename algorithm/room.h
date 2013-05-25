#ifndef ROOM_H
#define ROOM_H

#include <cstddef>

enum TypeOfRoom{
    lectureRoom = 1,
    ourDepartmentRoom = 2,
    otherDepartmentRoom = 3
};

class room
{

    TypeOfRoom m_type;
    unsigned int m_number;
    unsigned int m_ID;

    bool init(unsigned int id, unsigned int number, TypeOfRoom type);

public:
    explicit room();

    //getters & setters
    TypeOfRoom getType(){
        return m_type;
    }
    unsigned int getNumber(){
        return m_number;
    }
    unsigned int getID(){
        return m_ID;
    }

    static room* create(unsigned int id, unsigned int number, TypeOfRoom type);
    
    
};

#endif // ROOM_H
