/*
    Created by YSP on 2025-05-11.
*/
#pragma once
#include <object.h>
#include "point.h"
#include "line.h"
namespace ysp {
    namespace math {
        namespace geometry {
            /// <summary>
            /// 三角形，任意不在同一条直线上的点可以组成三角形
            /// </summary>
            class Triangle : public Object {
            public:
                Triangle(const Point2D& a, const Point2D& b, const Point2D& c);
            private:
                /// <summary>
                /// 三角形的三个点 ABC
                /// </summary>
                Point2D a;
                Point2D b;
                Point2D c;
                /// <summary>
                /// 三角形的三条边 ABC
                /// </summary>
                Line2D la;
                Line2D lb;
                Line2D lc;
            };
        }
    }
}