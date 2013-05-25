#include "lesson.h"

lesson::lesson(group *grp, subject *sbj, teacher *tchr, room *rm, int time)
{
    m_group = grp;
    m_subject = sbj;
    m_teacher = tchr;
    m_room = rm;
    m_timeIndex = time;
}
