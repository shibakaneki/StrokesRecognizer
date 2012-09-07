#ifndef STROKESRECOGNIZER_H
#define STROKESRECOGNIZER_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QResizeEvent>

#include "SmoothCanvas.h"
#include "SGlobals.h"

#define DEFAULT_WIDTH	640
#define DEFAULT_HEIGHT	480

class StrokesRecognizer : public QWidget
{
    Q_OBJECT
public:
    StrokesRecognizer(QWidget *parent = 0);
    virtual ~StrokesRecognizer();

private slots:
    void onRecognizeClicked();
    void onClearClicked();

private:
    QHBoxLayout* mpLayout;
    QVBoxLayout* mpToolsLayout;
    SmoothCanvas* mpCanvas;
    QLabel* mpCharacterResult;
    QPushButton* mpRecognizeBttn;
    QPushButton* mpClearBttn;
};

#endif // STROKESRECOGNIZER_H
