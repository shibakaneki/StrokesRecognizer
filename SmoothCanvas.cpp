#include "SmoothCanvas.h"

SmoothCanvas::SmoothCanvas(QWidget *parent) : QWidget(parent)
	, defaultWidth(640)
	, defaultHeight(480)
	, penWidth(5)
	, m_bIsDrawing(false)
	, m_pCrntPath(NULL)
	, m_pCache(NULL)
{
	setStyleSheet("background-color: white;");
	resize(defaultWidth, defaultHeight);

	pen.setCapStyle(Qt::RoundCap);
	pen.setJoinStyle(Qt::RoundJoin);
	pen.setColor(Qt::black);
	pen.setWidth(5);
}

SmoothCanvas::~SmoothCanvas(){
	if(NULL != m_pCrntPath){
		delete m_pCrntPath;
		m_pCrntPath = NULL;
	}
}

void SmoothCanvas::paintEvent(QPaintEvent* ev){
	Q_UNUSED(ev);

	QPainter* p = new QPainter();
	p->begin(this);
	setupPainter(p);

	// Draw the cache
	if(NULL != m_pCache){
		p->drawPixmap(QPoint(), *m_pCache);
	}else{
		p->setPen(Qt::NoPen);
		p->setBrush(QBrush(Qt::white));
		p->drawRect(rect());
		setupPainter(p);
	}

	// Draw the current path
	if(NULL != m_pCrntPath){
		p->drawPath(*m_pCrntPath);
	}
	p->end();
}

void SmoothCanvas::mousePressEvent(QMouseEvent* ev){
	handlePressEvent(ev->posF());
}

void SmoothCanvas::mouseMoveEvent(QMouseEvent* ev){
	handleMoveEvent(ev->posF());
}

void SmoothCanvas::mouseReleaseEvent(QMouseEvent* ev){
	handleReleaseEvent(ev->posF());
}

void SmoothCanvas::tabletEvent(QTabletEvent* ev){
	switch(ev->type()){
	case QTabletEvent::TabletPress:
		handlePressEvent(QPointF(ev->pos()));
		break;
	case QTabletEvent::TabletMove:
		handleMoveEvent(QPointF(ev->pos()));
		break;
	case QTabletEvent::TabletRelease:
		handleReleaseEvent(QPointF(ev->pos()));
		break;
	default:
		break;
	}
}

void SmoothCanvas::handlePressEvent(QPointF pos){
	if(!m_bIsDrawing){
		m_bIsDrawing = true;
		m_lPoints.clear();
		sPoint* pt = new sPoint();
		pt->x = pos.x();
		pt->y = pos.y();
		m_lPoints.append(pt);
		generateCurrentPath();
		update();
	}
}

void SmoothCanvas::handleMoveEvent(QPointF pos){
	if(m_bIsDrawing){
		sPoint* pt = new sPoint();
		pt->x = pos.x();
		pt->y = pos.y();
		m_lPoints.append(pt);
		generateCurrentPath();
		update();
	}else{
		Q_UNUSED(pos);
	}
}

void SmoothCanvas::handleReleaseEvent(QPointF pos){
	if(m_bIsDrawing){
		sPoint* pt = new sPoint();
		pt->x = pos.x();
		pt->y = pos.y();
		m_lPoints.append(pt);

		generateCurrentPath();
		m_lPreviousPath << m_pCrntPath;

		//delete m_pCrntPath;
		m_pCrntPath = NULL;

		m_bIsDrawing = false;

		updateCache();
		update();
	}else{
		Q_UNUSED(pos);
	}
}

void SmoothCanvas::generateCurrentPath(){
	m_pCrntPath = new QPainterPath();
	if(!m_lPoints.empty()){
		if(m_lPoints.size() > 1){
			for(int i=m_lPoints.size()-2; i<m_lPoints.size(); i++){
				if(i>=0){
					if(i==0){
						m_lPoints.at(i)->dx = ((m_lPoints.at(i+1)->x - m_lPoints.at(i)->x) / SMOOTHING);
						m_lPoints.at(i)->dy = ((m_lPoints.at(i+1)->y - m_lPoints.at(i)->y) / SMOOTHING);
					}else if(i == m_lPoints.size()-1){
						m_lPoints.at(i)->dx = ((m_lPoints.at(i)->x - m_lPoints.at(i-1)->x) / SMOOTHING);
						m_lPoints.at(i)->dy = ((m_lPoints.at(i)->y - m_lPoints.at(i-1)->y) / SMOOTHING);
					}else{
						m_lPoints.at(i)->dx = ((m_lPoints.at(i + 1)->x - m_lPoints.at(i-1)->x) / SMOOTHING);
						m_lPoints.at(i)->dy = ((m_lPoints.at(i + 1)->y - m_lPoints.at(i-1)->y) / SMOOTHING);
					}
				}
			}
		}
	}

	bool first = true;
	for(int i=0; i<m_lPoints.size(); i++){
		sPoint pt = *m_lPoints.at(i);
		if(first){
			first = false;
			m_pCrntPath->moveTo(pt.x, pt.y);
		}else{
			sPoint prev = *m_lPoints.at(i-1);
			sPoint c0, c1;

			c0.x = prev.x + prev.dx;
			c0.y = prev.y + prev.dy;
			c1.x = pt.x - pt.dx;
			c1.y = pt.y - pt.dy;
			m_pCrntPath->cubicTo(c0.x, c0.y, c1.x, c1.y, pt.x, pt.y);
		}
	}
}

void SmoothCanvas::updateCache(){
	if(NULL != m_pCache){
		delete m_pCache;
	}
	m_pCache = new QPixmap(rect().width(), rect().height());
	QPainter* p = new QPainter();
	p->begin(m_pCache);
	p->setBrush(QBrush(Qt::white));
	p->setPen(Qt::white);
	p->drawRect(m_pCache->rect());
	setupPainter(p);

	foreach(QPainterPath* path, m_lPreviousPath){
		if(NULL != path){
			p->drawPath(*path);
		}
	}
	p->end();
}

void SmoothCanvas::setupPainter(QPainter* p){
	p->setPen(pen);
	p->setBrush(Qt::NoBrush);
	p->setRenderHints(QPainter::Antialiasing, true);
}

void SmoothCanvas::clear(){
	m_lPoints.clear();
	m_lPreviousPath.clear();
	updateCache();
	update();
}

QList<const QPainterPath*> SmoothCanvas::strokes(){
	QList<const QPainterPath*> strokes;

	foreach(QPainterPath* path, m_lPreviousPath){
		strokes << const_cast<const QPainterPath*>(path);
	}

	return strokes;
}
