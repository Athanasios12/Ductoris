QT += quick
CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    src/army/acher.cpp \
    src/army/armor.cpp \
    src/army/army.cpp \
    src/army/commander.cpp \
    src/army/equipment.cpp \
    src/army/equipmentfactory.cpp \
    src/army/javalinmen.cpp \
    src/army/officer.cpp \
    src/army/Person.cpp \
    src/army/skilltree.cpp \
    src/army/Soldier.cpp \
    src/army/spearman.cpp \
    src/army/swordsman.cpp \
    src/army/weapon.cpp \
    src/army/roman/units/rswordsman.cpp \
    src/army/roman/units/rofficer.cpp \
    src/army/roman/romanarmyfactory.cpp \
    src/army/roman/rleaderskilltree.cpp \
    src/army/roman/units/rLeader.cpp \
    src/army/roman/units/rspearman.cpp \
    src/army/roman/units/rarcher.cpp \
    src/army/roman/units/rhorseman.cpp \
    src/army/roman/units/rskirmisher.cpp \
    Ductoris.cpp \
    src/army/armyfactory.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/army/acher.h \
    src/army/armor.h \
    src/army/army.h \
    src/army/commander.h \
    src/army/equipment.h \
    src/army/equipmentfactory.h \
    src/army/javalinmen.h \
    src/army/officer.h \
    src/army/Person.h \
    src/army/skilltree.h \
    src/army/Soldier.h \
    src/army/spearman.h \
    src/army/swordsman.h \
    src/army/weapon.h \
    src/army/roman/units/rswordsman.h \
    src/army/roman/units/rofficer.h \
    src/army/roman/romanarmyfactory.h \
    src/army/roman/rleaderskilltree.h \
    src/army/roman/units/rLeader.h \
    src/army/roman/units/rspearman.h \
    src/army/roman/units/rarcher.h \
    src/army/roman/units/rhorseman.h \
    src/army/roman/units/rskirmisher.h \
    Ductoris.h \
    src/army/armyfactory.h \
    globaldata.h

INCLUDEPATH += src/army/ \
               src/army/roman \
               src/army/roman/units \
               src/army/roman/units/equipment
