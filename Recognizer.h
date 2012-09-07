/*
 * Recognizer.h
 *
 *  Created on: Sep 7, 2012
 *      Author: kindov
 */

#ifndef RECOGNIZER_H_
#define RECOGNIZER_H_

#include <QString>
#include <QList>
#include <QPainterPath>

class Recognizer{
public:
	Recognizer();
	virtual ~Recognizer();

	QString recognize(const QList<const QPainterPath*>& strokes);
};

#endif /* RECOGNIZER_H_ */
