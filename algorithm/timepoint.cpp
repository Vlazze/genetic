#include "timepoint.h"
#include <cstddef>
#include <QtCore>
timePoint::timePoint()
{
}

bool timePoint::init(unsigned int timeIndex){
    if(timeIndex > s_maxOverallTimeIndex)
        return false;
    if(timeIndex == 0)
        return false;
    m_overallTimeIndex = timeIndex;
    return true;
}

timePoint* timePoint::create(unsigned int timeIndex){
    timePoint *obj = new timePoint();
    if(obj && obj->init(timeIndex)){
        return obj;
    }
    delete obj;
    return NULL;
}

unsigned int timePoint::getRandomTimePoint(){
    //qt random initialization
//    QTime time = QTime::currentTime();
//    qsrand((uint)time.msec());

    return (qrand() % (timePoint::s_maxOverallTimeIndex - 1)) + 1;
}
