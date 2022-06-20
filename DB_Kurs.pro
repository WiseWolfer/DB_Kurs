QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    data_from_db.cpp \
    dialog.cpp \
    dialogabout.cpp \
    dialogadd.cpp \
    dialogedit.cpp \
    main.cpp \
    mainwindow.cpp \
    tableviewmodel.cpp

HEADERS += \
    data_from_db.h \
    dialog.h \
    dialogabout.h \
    dialogadd.h \
    dialogedit.h \
    mainwindow.h \
    tableviewmodel.h

FORMS += \
    dialog.ui \
    dialogabout.ui \
    dialogadd.ui \
    dialogedit.ui \
    mainwindow.ui

TRANSLATIONS += \
    DB_Kurs_ru_RU.ts\
    DB_Kurs_en_US.ts
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

DISTFILES += \
    DB_Kurs_en_US.qm \
    DB_Kurs_ru_RU.qm
