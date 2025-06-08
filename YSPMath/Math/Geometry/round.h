/*
    Created by YSP on 2025-06-2.
*/
#pragma once
#include <object.h>
#include "point.h"
#include "degrees.h"
namespace ysp {
    namespace math {
        namespace geometry {
            /*
               圆是‌到定点（圆心）距离等于定长（半径）的所有点的集合‌
            */
            class Round2D : public Object {
            public:
                Round2D(const Point2D& center, double radius);
                inline double Radius() {
                    return radius;
                }

                inline Point2D Center() {
                    return center;
                }

                /// <summary>
                /// 根据默认值(角度)，返回圆上任意一点的坐标
                /// </summary>
               /// <returns></returns>
                Point2D Position(double value) const;

                /// <summary>
                /// 根据角度，返回圆上任意一点的坐标
                /// </summary>
                /// <returns></returns>
                Point2D Position(const Angle& angle) const;

                /// <summary>
                /// 根据弧度，返回圆上任意一点的坐标
                /// </summary>
                /// <returns></returns>
                Point2D Position(const Radian& angle) const;
            private:
                Point2D center;//圆的中心坐标
                double radius;//圆的半径
            };
        }
    }
}