#pragma once

#include "qmath.h"

#include <QPointF>

inline double scalemultiplier = 5;

inline double scale = 1;
inline double standardsize = 16; //Pixels
inline double aspectratio = 1023/895.0;
inline double scalefactor = scale * standardsize;

static double toRadians(const double deg) { return deg*M_PI/180.0; }
static double toDegrees(const double rad) { return (rad / M_PI ) * 180.0; }

static QPointF findIntersection(const double m1, const double q1, const double m2, const double q2) {

	double x = (q1 - q2) / (m2 - m1);
	return QPointF(x, q1 + (x * m1));

}

static double pitagoricDistance(QPointF p1, QPointF p2) {
	return sqrt(pow(p1.x() - p2.x(), 2) + pow(p1.y() - p2.y(), 2));
}

template<typename Base, typename T>
bool instanceof(const T* ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

template <class T>
static T clamp(T valore, T min, T max) {
	return valore > max ? max : valore < min ? min : valore;
}