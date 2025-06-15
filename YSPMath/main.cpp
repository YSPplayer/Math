/*
	Created by YSP on 2025-05-05.
*/
#include <iostream>
#include "Math/Geometry/point.h"
#include "Math/Geometry/line.h"
#include "Math/Geometry/triangle.h"
using namespace ysp::math::geometry;
int main() {
	//Point2D P(-481.1,-521.0);
	//Point2D P2(154.4,-10.3);
	//Line2D line2d(P, P2);
	//std::cout << P.ToString() << std::endl;
	//std::cout << P2.ToString() << std::endl;
	//std::cout << line2d.ToString() << std::endl;
	//line2d.Show();
	Point2D A(-481.1, -521.0);
	Point2D B(154.4, -190.3);
	Point2D C(200.0, -80.3);
	Triangle2D a(A,B,C);
	a.Show();
	return 0;
}

