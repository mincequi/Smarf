TEMPLATE = app

QT += charts qml quick quickcontrols2 svg widgets
CONFIG += c++17

SOURCES += main.cpp \
    CiotusMessage.cpp \
    CiotusTypes.cpp \
    HistoricalDataModel.cpp \
    InverterModel.cpp \
    LiveModel.cpp \
    Persistence.cpp \
    ThemeModel.cpp \
    qmlmqttclient.cpp \
    thirdparty/CayenneLPP/src/CayenneLPP.cpp \
    thirdparty/CayenneLPP/src/CayenneLPPByteBuffer.cpp \
    thirdparty/CayenneLPP/src/CayenneLPPMessage.cpp \
    thirdparty/CayenneLPP/src/CayenneLPPPolyline.cpp \
    thirdparty/CayenneLPP/src/CayenneLPPPowerMeasurement.cpp \
    thirdparty/CayenneLPP/src/SFloat16.cpp

HEADERS += \
    CiotusMessage.h \
    CiotusTypes.h \
    HistoricalDataModel.h \
    InverterModel.h \
    LiveModel.h \
    LiveModelPrivate.h \
    Persistence.h \
    ThemeModel.h \
    qmlmqttclient.h \
    thirdparty/CayenneLPP/src/CayenneLPP.h \
    thirdparty/CayenneLPP/src/CayenneLPPByteBuffer.h \
    thirdparty/CayenneLPP/src/CayenneLPPMessage.h \
    thirdparty/CayenneLPP/src/CayenneLPPPowerMeasurement.h \
    thirdparty/CayenneLPP/src/SFloat16.h

RESOURCES += qml.qrc

INCLUDEPATH += thirdparty/CayenneLPP/src

include(thirdparty/qmqtt/qmqtt.pri)
include(thirdparty/qmsgpack/qmsgpack.pri)

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
