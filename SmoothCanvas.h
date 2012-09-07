#ifndef SMOOTHCANVAS_H
#define SMOOTHCANVAS_H

#include <QWidget>
#include <QColor>
#include <QBrush>
#include <QPen>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QTabletEvent>
#include <QPointF>
#include <QList>
#include <QPainter>
#include <QPixmap>

#define SMOOTHING			6

typedef struct{
	qreal x;
	qreal y;
	float dx;
	float dy;
}sPoint;

class SmoothCanvas : public QWidget
{
    Q_OBJECT

public:
    SmoothCanvas(QWidget *parent = 0);
    virtual ~SmoothCanvas();
    void clear();
    QList<const QPainterPath*> strokes();

    int defaultWidth;
    int defaultHeight;
    int penWidth;
    QPen pen;
    QBrush brush;

protected:
    virtual void paintEvent(QPaintEvent* ev);
    virtual void mousePressEvent(QMouseEvent* ev);
    virtual void mouseMoveEvent(QMouseEvent* ev);
    virtual void mouseReleaseEvent(QMouseEvent* ev);
    virtual void tabletEvent(QTabletEvent* ev);

private:
    void handlePressEvent(QPointF pos);
    void handleMoveEvent(QPointF pos);
    void handleReleaseEvent(QPointF pos);
    void generateCurrentPath();
    void updateCache();
    void setupPainter(QPainter* p);

    bool m_bIsDrawing;
    QList<sPoint*> m_lPoints;
    QPainterPath* m_pCrntPath;
    QList<QPainterPath*> m_lPreviousPath;
    QPixmap* m_pCache;
};

#endif // SMOOTHCANVAS_H
