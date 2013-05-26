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
}

QVector< QVector<lesson*> > GAlgorithm::generateGenome(){

    //parameters
    int subjCount = 20;
    int roomCount = 20;
    int teacherCount = 10;
    int groupCount = 12;

    //test
        QVector<subject *> subjPool;
        QVector<room *> roomPoolInst;
        QVector<teacher *> teacherPoolInst;
        QVector<group *> groupPoolInst;

        qsrand(1);
        for (int i = 0; i < subjCount; i++){

            QSet<int> semesters;
            semesters.insert((qrand()%8)+1);
            semesters.insert((qrand()%8)+1);
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

        groupPool *groupPool1 = groupPool::createWithVector(groupPoolInst);
        //group grp = groupPool1->getGroupPool();

        subjectPool *subjectPool1 = subjectPool::createWithVector(subjPool);
        //subject sbj = subjectPool1->getRandomSubject(&grp);

        teacherPool *teacherPool1 = new teacherPool(teacherPoolInst);
        roomPool *roomPool1 = new roomPool(roomPoolInst);


        QVector< QVector<lesson*> > schedule;
        for (int i = 0; i < groupPool1->getCount(); i++) {
            schedule.append(QVector<lesson*>());
        }

        for (int i = 0; i < groupPool1->getCount(); i++){
            for (int j = 0; j < subjectPool1->getCount(); j++){
                subject* sbj = subjectPool1->getSubjectPool().at(j);
                if (!sbj->getSemesters().contains(groupPool1->getGroupPool().at(i)->getSemester())){
                    continue;
                }
                for (int k = 0; k < sbj->getCount(); k++){  //???
                    lesson* lsn = new lesson(groupPool1->getGroupPool().at(i),
                                             subjectPool1->getSubjectPool().at(j),
                                             teacherPool1->getRandomTeacher(),
                                             roomPool1->getRandomRoom(),
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

void GAlgorithm::generatePopulation(){

}
