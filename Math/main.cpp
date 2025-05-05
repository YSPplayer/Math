#include <iostream>
#include "Geometry/point.h"
using namespace ysp::math::geometry;
int main() {
	Point2D P;
	Point3D SS = {1, 2, 3};
	std::cout << "value:" << P.X() << ":"  << P.Y() << "" << std::endl;
	std::cout << "value:" << SS.X() << ":"  << SS.Y() << "" << SS.Z() << "" << std::endl;
	return 0;
}

