TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lsqlite3

SOURCES += \
    client.c

include(deployment.pri)
qtcAddDeployment()

HEADERS +=

