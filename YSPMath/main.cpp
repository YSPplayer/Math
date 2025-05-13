/*
	Created by YSP on 2025-05-05.
*/
#include <iostream>
#include "Math/Geometry/point.h"
#include "Math/Geometry/line.h"
using namespace ysp::math::geometry;
int main() {
	Point2D P;
	Point2D P2(16.0,49.3);
	Line2D line2d(P, P2);
	std::cout << line2d.Print() << std::endl;
	return 0;
}

