#-------------------------------------------------
#
# Project created by QtCreator 2012-01-12T12:12:24
#
#-------------------------------------------------

QT       += core gui network xml

TARGET = GuiSample
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../UpdateSystem/release/ -lUpdateSystem
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../UpdateSystem/debug/ -lUpdateSystem

INCLUDEPATH += $$PWD/../UpdateSystem/include
DEPENDPATH += $$PWD/../UpdateSystem/include

#win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../UpdateSystem/release/libUpdateSystem.a
#else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../UpdateSystem/debug/libUpdateSystem.a
