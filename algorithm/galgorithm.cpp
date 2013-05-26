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
        //end of test
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
