#pragma once

#include "qmath.h"

#include <QPoint>

static double scale = 5;
static double standardsize = 16; //Pixels
static double scalefactor = scale * standardsize;

static double toRadians(const double deg) { return deg*M_PI/180.0; }
static double toDegrees(const double rad) { return (rad / M_PI ) * 180.0; }

static QPoint findIntersection(const double m1, const double q1, const double m2, const double q2) {

	double x = (q1 - q2) / (m2 - m1);
	return QPoint(x, q1 + (x * m1));

}

static double pitagoricDistance(QPoint p1, QPoint p2) {
	return sqrt(pow(p1.x() - p2.x(), 2) + pow(p1.y() - p2.y(), 2));
}

template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}
