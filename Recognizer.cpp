#include <QDebug>
#include <QPointF>
#include "Recognizer.h"
#include "zinnia.h"

#define NB_POINTS	1

Recognizer::Recognizer(){

}

Recognizer::~Recognizer(){

}

QString Recognizer::recognize(const QList<const QPainterPath*>& strokes){
	QString output;

	zinnia::Recognizer *recognizer = zinnia::Recognizer::create();
	if(!recognizer->open("/usr/local/lib/zinnia/model/tomoe/handwriting-ja.model")){
		qDebug() << recognizer->what();
	}else{
		// Get bounding rect of the strokes
		QPainterPath tempPath;
		foreach(const QPainterPath* p, strokes){
			tempPath.addPath(*p);
		}

		// Perform the recognition
		zinnia::Character *character = zinnia::Character::create();
		character->clear();
		character->set_width(tempPath.boundingRect().width());
		character->set_height(tempPath.boundingRect().height());
		qreal xOrigin = tempPath.boundingRect().x();
		qreal yOrigin = tempPath.boundingRect().y();

		for(int i=0; i<strokes.size(); i++){
			qreal step = 1/NB_POINTS;
			for(int j=0; j<=1; j+=step){
				QPointF cursor = strokes.at(i)->pointAtPercent(j);
				character->add(i, cursor.x()-xOrigin, cursor.y()-yOrigin);
			}
		}

		zinnia::Result *result = recognizer->classify(*character, 1);
		if(!result){
			qDebug() << recognizer->what();
		}else{
			for (size_t i = 0; i < result->size(); ++i) {
				output = QString::fromUtf8(result->value(i));
				//qDebug() << QString::fromUtf8(result->value(i)) << "\t" << result->score(i);
			}
			delete result;
			delete character;
			delete recognizer;
		}
	}

	return output;
}
