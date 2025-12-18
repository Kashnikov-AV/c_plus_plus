#pragma once
#include <cmath>

struct point {
public:
	double x, y, z;
	double vx, vy, vz;
	double mass;
};

class c_vector {
public:
	point p1, p2;
	double length;
	double cx, cy, cz;

	// конструктор
	//c_vector() {
	//	p1 = nullptr;
	//	p2 = nullptr;
	//	length = 0.0;
	//	cx = 0.0; cy = 0.0; cz = 0.0;
	//};

	c_vector(point& t1, point& t2) {
		p1 = t1;
		p2 = t2;

		length = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z));

		cx = (p1.x - p2.x) / length;
		cy = (p1.y - p2.y) / length;
		cz = (p1.z - p2.z) / length;
	};
};
