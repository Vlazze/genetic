#ifndef SUBJECTPOOL_H
#define SUBJECTPOOL_H

#include "subject.h"
#include "group.h"

class subjectPool
{

    QVector<subject *> m_pool;
    bool init(QVector<subject *> pool);

public:
    explicit subjectPool();

    ~subjectPool(){
        qDeleteAll(m_pool);
    }

    static subjectPool* createWithVector(QVector<subject *> pool);

    subject getRandomSubject(group *grp) const;

    QVector<subject *> getSubjectPool() {
        return m_pool;
    }

    int getCount(){
        return m_pool.count();
    }

    bool isHereAnySubject();
    
    
};

#endif // SUBJECTPOOL_H
