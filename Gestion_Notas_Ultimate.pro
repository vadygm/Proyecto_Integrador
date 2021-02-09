QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    barraestadisticaestudiantes.cpp \
    dialog_save.cpp \
    main.cpp \
    prinsipal.cpp \
    staticbar.cpp \
    stidents.cpp

HEADERS += \
    barraestadisticaestudiantes.h \
    dialog_save.h \
    prinsipal.h \
    staticbar.h \
    stidents.h

FORMS += \
    dialog_save.ui \
    prinsipal.ui

TRANSLATIONS += \
    Gestion_Notas_Ultimate_es_EC.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
 Resourse.qrc
