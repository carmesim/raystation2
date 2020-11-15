TEMPLATE = app
CONFIG += console c++98
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        ray.cpp \
        sphere.cpp \
        vector.cpp

HEADERS += \
    light.h \
    material.h \
    ray.h \
    sphere.h \
    vector.h
