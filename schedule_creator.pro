#-------------------------------------------------
#
# Project created by QtCreator 2013-05-03T08:50:26
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = schedule_creator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dboperations.cpp \
    subjecthoursview.cpp \
    algorithm/timepoint.cpp \
    algorithm/teacherpool.cpp \
    algorithm/teacher.cpp \
    algorithm/subjectpool.cpp \
    algorithm/subject.cpp \
    algorithm/roompool.cpp \
    algorithm/room.cpp \
    algorithm/lesson.cpp \
    algorithm/grouppool.cpp \
    algorithm/group.cpp \
    schedule_constructor.cpp \
    algorithm/galgorithm.cpp

HEADERS  += mainwindow.h \
    dboperations.h \
    subjecthoursview.h \
    algorithm/timepoint.h \
    algorithm/teacherpool.h \
    algorithm/teacher.h \
    algorithm/subjectpool.h \
    algorithm/subject.h \
    algorithm/roompool.h \
    algorithm/room.h \
    algorithm/lesson.h \
    algorithm/grouppool.h \
    algorithm/group.h \
    schedule_constructor.h \
    algorithm/galgorithm.h

FORMS    += mainwindow.ui \
    schedule_constructor.ui \
    subjecthoursview.ui
