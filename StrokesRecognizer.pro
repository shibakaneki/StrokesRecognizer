TEMPLATE = app
TARGET = StrokesRecognizer
QT += core \
    gui
HEADERS += Recognizer.h \
    SGlobals.h \
    SmoothCanvas.h \
    StrokesRecognizer.h
SOURCES += Recognizer.cpp \
    SmoothCanvas.cpp \
    main.cpp \
    StrokesRecognizer.cpp
FORMS += 
RESOURCES += 
LIBS += -lzinnia
INCLUDEPATH += ../../SDK/zinnia-0.06