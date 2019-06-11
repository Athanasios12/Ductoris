QT -= gui

QT += testlib

CONFIG += c++17 console
CONFIG += test
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += ../Ductoris/src/army/ ../Ductoris/src/army/roman/ ../Ductoris/src/army/roman/units
HEADERS += \
    AbstractArmyFactoryTests.h \
    RomanArmyFactoryTests.h \
    ../Ductoris/src/army/roman/romanarmyfactory.h \
    ../Ductoris/src/army/roman/units/rLeader.h \
    ../Ductoris/src/army/roman/units/rswordsman.h \
    ../Ductoris/src/army/armyfactory.h \
    ../Ductoris/src/army/acher.h \
    ../Ductoris/src/army/armor.h \
    ../Ductoris/src/army/army.h \
    ../Ductoris/src/army/commander.h \
    ../Ductoris/src/army/equipment.h \
    ../Ductoris/src/army/equipmentfactory.h \
    ../Ductoris/src/army/javalinmen.h \
    ../Ductoris/src/army/officer.h \
    ../Ductoris/src/army/Person.h \
    ../Ductoris/src/army/skilltree.h \
    ../Ductoris/src/army/Soldier.h \
    ../Ductoris/src/army/spearman.h \
    ../Ductoris/src/army/swordsman.h \
    ../Ductoris/src/army/weapon.h \
    ../Ductoris/src/army/roman/units/rofficer.h \
    ../Ductoris/src/army/roman/units/rarcher.h \
    ../Ductoris/src/army/roman/units/rhorseman.h \
    ../Ductoris/src/army/roman/units/rskirmisher.h \
    ../Ductoris/src/army/roman/units/rspearman.h \
    romanleadertests.h \
    persontests.h \
    ../Ductoris/Ductoris.h
SOURCES += \
    AbstractArmyFactoryTests.cpp \
    RomanArmyFactoryTests.cpp \
    main.cpp \
    ../Ductoris/src/army/roman/romanarmyfactory.cpp \
    ../Ductoris/src/army/roman/units/rLeader.cpp \
    ../Ductoris/src/army/roman/units/rswordsman.cpp \
    ../Ductoris/src/army/armyfactory.cpp \
    ../Ductoris/src/army/acher.cpp \
    ../Ductoris/src/army/armor.cpp \
    ../Ductoris/src/army/army.cpp \
    ../Ductoris/src/army/commander.cpp \
    ../Ductoris/src/army/equipment.cpp \
    ../Ductoris/src/army/equipmentfactory.cpp \
    ../Ductoris/src/army/javalinmen.cpp \
    ../Ductoris/src/army/officer.cpp \
    ../Ductoris/src/army/Person.cpp \
    ../Ductoris/src/army/skilltree.cpp \
    ../Ductoris/src/army/Soldier.cpp \
    ../Ductoris/src/army/spearman.cpp \
    ../Ductoris/src/army/swordsman.cpp \
    ../Ductoris/src/army/weapon.cpp \
    ../Ductoris/src/army/roman/units/rofficer.cpp \
    ../Ductoris/src/army/roman/units/rarcher.cpp \
    ../Ductoris/src/army/roman/units/rhorseman.cpp \
    ../Ductoris/src/army/roman/units/rskirmisher.cpp \
    ../Ductoris/src/army/roman/units/rspearman.cpp \
    romanleadertests.cpp \
    persontests.cpp \
    ../Ductoris/Ductoris.cpp
