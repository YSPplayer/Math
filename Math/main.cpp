#include <iostream>
#include "Geometry/point.h"
using namespace ysp::math::geometry;
int main() {
	Point2D P;
	Point3D SS = {1, 2, 3};
	std::cout << SS.Print() << std::endl;
	std::cout << P.Print() << std::endl;
	return 0;
}

