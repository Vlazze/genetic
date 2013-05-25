#ifndef TIMEPOINT_H
#define TIMEPOINT_H

class timePoint
{
    unsigned int m_overallTimeIndex;

    bool init(unsigned int timeIndex);

public:
    explicit timePoint();

    static const unsigned int s_maxOverallTimeIndex = 60;
    static unsigned int getRandomTimePoint();
    static timePoint* create(unsigned int timeIndex);
    
};

#endif // TIMEPOINT_H
