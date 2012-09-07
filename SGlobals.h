#ifndef SGLOBALS_H
#define SGLOBALS_H

#include <QDebug>
#include <QString>
#include <QFile>

// Strings
#define ON_CANVAS				"SCanvas"
#define ON_BUTTON				"SButton"
#define ON_LABELBOX				"SLabelBox"

// Macros
#define DELETEPTR(ptr) if(NULL != ptr){ \
    delete ptr; \
    ptr = NULL; \
    }

#define SETUP_STYLESHEET { \
    QString style; \
    QFile f(":/style.qss"); \
    if(f.exists()) \
    { \
        if(f.open(QIODevice::ReadOnly)) \
        { \
            style = QString(f.readAll()); \
            setStyleSheet(style); \
        } \
    } \
}

#endif // SGLOBALS_H
