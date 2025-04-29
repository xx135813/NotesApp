QT += core gui sql widgets  # Add 'widgets' to ensure Qt GUI module is linked

CONFIG += c++11

TARGET = NotesApp
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Additional configurations for MOC
MOC_DIR = moc

# Add any other necessary paths or files
INCLUDEPATH += .

# For debugging
QMAKE_CXXFLAGS += -g
