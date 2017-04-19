TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += main.cpp \
    rb_multi_set.cpp \
    priority_queue.cpp \
    text_stat.cpp

HEADERS += \
    rb_multi_set.h \
    priority_queue.h \
    text_stat.h
