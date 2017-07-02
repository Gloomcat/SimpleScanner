#-------------------------------------------------
#
# Project created by QtCreator 2017-06-29T12:21:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScannerQt
TEMPLATE = app

win32 {
    INCLUDEPATH += "D:\Deadcat\Work\boost_1_64_0"

    LIBS += "-LD:\Deadcat\Work\boost_1_64_0\stage\lib" \
            -llibboost_system-vc140-mt-gd-1_64 \
            -llibboost_filesystem-vc140-mt-gd-1_64 \
            -llibboost_date_time-vc140-mt-gd-1_64 \
}

SOURCES += main.cpp\
        scannerqt.cpp

HEADERS  += scannerqt.h \
    file_path_collector.h \
    thread_pool.h \
    threading_components.h \
    threading_service.h

FORMS    += scannerqt.ui
