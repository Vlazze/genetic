#ifndef GALGORITHM_H
#define GALGORITHM_H

#include <QtCore>
#include "lesson.h"

class GAlgorithm
{
    int m_populationCount;
    int m_iterationCount;
    int m_mutationRate;
    QVector<lesson *> m_population;

public:
    GAlgorithm();

    void generatePopulation();
};

#endif // GALGORITHM_H
