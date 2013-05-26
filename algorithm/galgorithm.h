#ifndef GALGORITHM_H
#define GALGORITHM_H

#include <QtCore>
#include "lesson.h"
#include "grouppool.h"
#include "roompool.h"
#include "subjectpool.h"
#include "teacherpool.h"

class GAlgorithm
{
    //slgorithm settings
    int m_populationCount;
    int m_iterationCount;
    int m_mutationRate;
    QVector< QVector< QVector<lesson *> > > m_population;

    //pools
    groupPool *m_groupPool;
    subjectPool *m_subjectPool;
    teacherPool *m_teacherPool;
    roomPool *m_roomPool;

public:
    GAlgorithm();
    ~GAlgorithm();
    //pool processing methods
    void setPools(groupPool *gp, subjectPool *sp, teacherPool *tp, roomPool *rp);
    void setPoolsWithRandomValues(int subjCount, int roomCount, int teacherCount, int groupCount);

    //setters and getters
    QVector< QVector<lesson *> > getPopulationAtIndex(int index);

    int getPopulationCount(){
        return m_populationCount;
    }

    //algorithm parameters methods
    void generatePopulation(int populationCount);
    QVector<QVector<lesson *> > generateGenome();
};

#endif // GALGORITHM_H
