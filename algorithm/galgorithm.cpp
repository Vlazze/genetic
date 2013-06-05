#include <QtCore>
#include "galgorithm.h"
#include "subjectpool.h"
#include "grouppool.h"
#include "teacherpool.h"
#include "grouppool.h"
#include "roompool.h"
#include "lesson.h"
#include "teacher.h"

GAlgorithm::GAlgorithm()
{
    m_groupPool = NULL;
    m_subjectPool = NULL;
    m_teacherPool = NULL;
    m_roomPool = NULL;
}

GAlgorithm::~GAlgorithm(){
    QVector< QVector <lesson*> > obj;
    QVector<lesson*> vec;
    for (int i = 0; i < m_population.count(); i++){
        obj = m_population[i];
        for (int j = 0; j < obj.count(); j++){
            vec = obj[j];
            qDeleteAll(vec);
        }
    }
}

//init pools with concrete values
void GAlgorithm::setPools(groupPool *gp, subjectPool *sp, teacherPool *tp, roomPool *rp){
    m_groupPool = gp;
    m_subjectPool = sp;
    m_teacherPool = tp;
    m_roomPool = rp;
}

//init pools with random values
void GAlgorithm::setPoolsWithRandomValues(int subjCount, int roomCount, int teacherCount, int groupCount){
    //parameters
//    int subjCount = 40;
//    int roomCount = 20;
//    int teacherCount = 10;
//    int groupCount = 12;

    //memory cleaning
    if(m_groupPool){
        delete m_groupPool;
    }
    if(m_subjectPool){
        delete m_subjectPool;
    }
    if(m_teacherPool){
        delete m_teacherPool;
    }
    if(m_roomPool){
        delete m_roomPool;
    }

    //test
        QVector<subject *> subjPool;
        QVector<room *> roomPoolInst;
        QVector<teacher *> teacherPoolInst;
        QVector<group *> groupPoolInst;

        for (int i = 0; i < subjCount; i++){

            QSet<int> semesters;
            int randSemester = (qrand()%8)+1;
            semesters.insert(randSemester);
            semesters.insert(randSemester+1);

            subject *subj = subject::create(i, "Subject"+QString::number(i), qrand()%2, qrand()%10,
                                            practiceSubject, semesters);
            subjPool.push_back(subj);
        }
        for (int i = 0; i < roomCount; i++){
            room *roomInst = room::create(i, qrand(), ourDepartmentRoom);
            roomPoolInst.push_back(roomInst);
        }
        for (int i = 0; i < teacherCount; i++){
            QSet<int> teacherCanTeach;

            for (int j = 0; j < 2; j++) {
                teacherCanTeach.insert(qrand() % subjCount);
            }

            teacher *teach = teacher::create(i, "Teacher"+QString::number(i), 0, qrand()%10, teacherCanTeach);
            teacherPoolInst.push_back(teach);
        }
//        for (int i = 0; i < groupCount; i++){
//            group *groupInst = group::create(i, (i%3)+1, (qrand()%8)+1, 0);
//            groupPoolInst.push_back(groupInst);
//        }
        groupPoolInst.push_back(group::create(1, 1, 1, 0));
        groupPoolInst.push_back(group::create(2, 2, 1, 0));
        groupPoolInst.push_back(group::create(3, 3, 1, 0));

        groupPoolInst.push_back(group::create(4, 1, 3, 0));
        groupPoolInst.push_back(group::create(5, 2, 3, 0));
        groupPoolInst.push_back(group::create(6, 3, 3, 0));

        groupPoolInst.push_back(group::create(7, 1, 5, 0));
        groupPoolInst.push_back(group::create(8, 2, 5, 0));
        groupPoolInst.push_back(group::create(9, 3, 5, 0));

        groupPoolInst.push_back(group::create(10, 1, 7, 0));
        groupPoolInst.push_back(group::create(11, 2, 7, 0));
        groupPoolInst.push_back(group::create(12, 3, 7, 0));

        m_groupPool = groupPool::createWithVector(groupPoolInst);
        m_subjectPool = subjectPool::createWithVector(subjPool);
        m_teacherPool = new teacherPool(teacherPoolInst);
        m_roomPool = new roomPool(roomPoolInst);
}

//genome generator
QVector< QVector<lesson*> > GAlgorithm::generateGenome(){

        QVector< QVector<lesson*> > schedule;
        for (int i = 0; i < m_groupPool->getCount(); i++) {
            schedule.append(QVector<lesson*>());
        }

        for (int i = 0; i < m_groupPool->getCount(); i++){
            for (int j = 0; j < m_subjectPool->getCount(); j++){
                subject* sbj = m_subjectPool->getSubjectPool().at(j);
                if (!sbj->getSemesters().contains(m_groupPool->getGroupPool().at(i)->getSemester())){
                    continue;
                }
                for (int k = 0; k < sbj->getCount(); k++){  //???
                    lesson* lsn = new lesson(m_groupPool->getGroupPool().at(i),
                                             m_subjectPool->getSubjectPool().at(j),
                                             m_teacherPool->getRandomTeacher(),
                                             m_roomPool->getRandomRoom(),
                                             timePoint::getRandomTimePoint()
                                             );
                    schedule[i].append(lsn);
                    sbj->decrementCountCounter();
                }
                sbj->resetCountCounter();
            }
        }

        return schedule;
}

void GAlgorithm::generatePopulation(int populationCount){
    m_populationCount = populationCount;

    for (int i = 0; i < m_populationCount; i++){
        m_population.push_back(generateGenome());
    }
}

QVector< QVector<lesson *> > GAlgorithm::getPopulationAtIndex(int index){
    return m_population.at(index);
}

unsigned long GAlgorithm::computeCollisionPenalty(QVector<QVector<lesson *> > genome){

    unsigned long returnValue = 0;

    //Conditions
    //Teacher can teach this subject
    //1 group 1 time 1 lesson
    unsigned long timeCollisionCount = 0;
    unsigned long teachersSubjectsCollitionCount = 0;
    for (int i = 0; i < genome.count(); i++){
        QVector<bool> timeMask;
        timeMask.fill(false, 60);
        for(int j = 0; j < genome[i].count(); j++){

            //Teacher can teach this subject
            if(!genome[i][j]->getTeacher()->getSubjectCanTeach().contains(genome[i][j]->getSubject()->getID())){
                teachersSubjectsCollitionCount += 100000;
            }

            //1 group 1 time 1 lesson
            if(timeMask.at(genome[i][j]->getTimeIndex()) == true){
                timeCollisionCount += 100000;
            } else {
                timeMask.replace(genome[i][j]->getTimeIndex(), true);
            }
        }
    }
    returnValue += timeCollisionCount;
    returnValue += teachersSubjectsCollitionCount;

    //Conditions
    //1 group 1 time 1 techer
    unsigned long teachersTimeCollisionCount = 0;
    for(int tn = 0; tn < m_teacherPool->getCount(); tn++){

        teacher *currentTeacher = m_teacherPool->getTeacherAtIndex(tn);
        QVector<bool> timeMask;
        timeMask.fill(false, 60);

        for(int i = 0; i < genome.count(); i++){
            for(int j = 0; j < genome[i].count(); j++){
                if(genome[i][j]->getTeacher()->getID() == currentTeacher->getID()){
                    if(timeMask.at(genome[i][j]->getTimeIndex()) == true){
                        teachersTimeCollisionCount += 100000;
                    } else {
                        timeMask.replace(genome[i][j]->getTimeIndex(), true);
                    }
                }
            }
        }
    }
    returnValue += teachersTimeCollisionCount;

    //Conditions
    //1 group 1 time 1 room
    unsigned long roomTimeCollisionCount = 0;
    for(int tn = 0; tn < m_roomPool->getCount(); tn++){

        room *currentRoom = m_roomPool->getRoomAtIndex(tn);
        QVector<bool> timeMask;
        timeMask.fill(false, 60);

        for(int i = 0; i < genome.count(); i++){
            for(int j = 0; j < genome[i].count(); j++){
                if(genome[i][j]->getRoom()->getID() == currentRoom->getID()){
                    if(timeMask.at(genome[i][j]->getTimeIndex()) == true){
                        roomTimeCollisionCount += 100000;
                    } else {
                        timeMask.replace(genome[i][j]->getTimeIndex(), true);
                    }
                }
            }
        }
    }
    returnValue += roomTimeCollisionCount;



    return returnValue;
}

unsigned long GAlgorithm::computeOptimizationPenalty(QVector<QVector<lesson *> > genome){
    return 0;
}

unsigned long GAlgorithm::fitnessFunction(QVector<QVector<lesson *> > genome){
    return computeCollisionPenalty(genome) + computeOptimizationPenalty(genome);
}

QVector<QVector<lesson *> > GAlgorithm::crossoverFunction(QVector<QVector<lesson *> > genome1, QVector<QVector<lesson *> > genome2){
    QVector< QVector<lesson *> > result = genome1;
    int genomeElementsCount = genome1.count();
    int breakPoint = qrand() % (genomeElementsCount - 2);
    for (int i = breakPoint; i < genomeElementsCount; i++){
        result.replace(i, genome2.at(i));
    }
    return result;
}

QVector<QVector<lesson *> > GAlgorithm::mutation(QVector<QVector<lesson *> > genome){
    QVector<QVector<lesson *> > mutant = generateGenome();
    int mutationIndex = qrand() % mutant.count();
    genome.replace(mutationIndex, mutant.at(mutationIndex));
    return genome;
}

void GAlgorithm::fitnessSortPopulation(){

    QVector<QVector<lesson *> > temp;

    for (int k = 1; k < m_population.count(); k++){
        for (int i = 0; i <m_population.count() - k; i++){
           if(fitnessFunction(m_population[i]) >  fitnessFunction(m_population[i+1])){
               temp = m_population[i];
               m_population.replace(i, m_population.at(i+1));
               m_population.replace(i+1, temp);
           }
        }
    }
}

//idiotism
void GAlgorithm::fitnessSortChildren(){

    QVector<QVector<lesson *> > temp;

    for (int k = 1; k < m_ChildPopulation.count(); k++){
        for (int i = 0; i <m_ChildPopulation.count() - k; i++){
           if(fitnessFunction(m_ChildPopulation[i]) >  fitnessFunction(m_ChildPopulation[i+1])){
               temp = m_ChildPopulation[i];
               m_ChildPopulation.replace(i, m_ChildPopulation.at(i+1));
               m_ChildPopulation.replace(i+1, temp);
           }
        }
    }
}

void GAlgorithm::runAlgorithm(int iterationCount){

    if(m_populationCount <= 1){
        return;
    }

    for(int i = 0; i < iterationCount; i++){

        //mutation
        for(int i = 0; i < m_population.count(); i++){
            m_population.replace(i, mutation(m_population.at(i)));
        }

        //crossingover
        for (int k = 0; k < m_population.count(); k++){
            for (int i = 0; i <m_population.count(); i++){
               if(k != i){
                    m_ChildPopulation.push_back(crossoverFunction(m_population.at(k), m_population.at(i)));
               }
            }
        }

        //fitness
        fitnessSortChildren();

        //selection
        m_population.remove(0, m_population.count() - 1);
        m_population.pop_back();

        for(int i = 0; i < m_populationCount; i++){
            m_population.push_back(m_ChildPopulation.at(i));
        }

    }
}
