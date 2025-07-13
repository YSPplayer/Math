/*
    Created by YSP on 2025-07-1.
*/
#pragma once
#include <object.h>
#include "point.h"
#include "degrees.h"
namespace ysp {
    namespace math {
        namespace geometry {
            class Sphere : public Object {
            public:
                Sphere(const Point3D& center,double radius);

                /// <summary>
                /// 返回当前球上所有点的坐标，numPoints是采样个数，返回点的坐标数量和该参数有关，这个值应该是某一个值的平方
                /// </summary>
                std::vector<Point3D> Points(int numPoints) const;
                /// <summary>
                /// 根据极角t(0-PI)和方位角p(0-2PI) 弧度值，返回圆上任意一点的坐标
                /// </summary>
                /// <returns></returns>
                Point3D Position(const Radian& t,const Radian& p) const;
                Point3D Position(const Angle& t, const Angle& p) const;
                
                Point3D Position(double t,double p) const;
            private:
                Point3D center;//球体的中心坐标
                double radius;//球体的半径
            };
        
        }
    }
}