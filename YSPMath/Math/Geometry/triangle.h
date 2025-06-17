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
            /// 三角形，任意不在同一条直线上的点(不共线的三个点)可以组成三角形
            /// </summary>
            class Triangle2D : public Object {
            public:
                Triangle2D(const Point2D& a, const Point2D& b, const Point2D& c);
                Triangle2D(const Triangle2D* triangle2D);
                Triangle2D(Triangle2D& triangle2D);
                Triangle2D();
                /// <summary>
                /// 检查当前三角形是否为无效三角形
                /// </summary>
                /// <returns></returns>
                bool inline IsValid() const {
                    return valid;
                }

                /// <summary>
                /// 获得三角形三条边的长度
                /// </summary>
                /// <returns></returns>
                double inline ABLength() const {
                    return ab.Length();
                }
                double inline ACLength() const {
                    return ac.Length();
                }
                double inline BCLength() const {
                    return bc.Length();
                }

                /// <summary>
                /// 获取到三角形以当前点为顶点的三条中线(中线是顶点和对边线段的中点所组成的线段)
                /// </summary>
                /// <returns></returns>
                Line2D inline AM() const {
                    return Line2D(a, bc.MidPoint());
                }

                Line2D inline BN() const {
                    return Line2D(b, ac.MidPoint());
                }

                Line2D inline CP() const {
                    return Line2D(c, ab.MidPoint());
                }

                /// <summary>
                /// 获取三角形的三个点
                /// </summary>
                Point2D inline A() const {
                    return a;
                }

                Point2D inline B() const {
                    return b;
                }

                Point2D inline C() const {
                    return c;
                }

                /// <summary>
                /// 获取三角形的三条边
                /// </summary>
                Line2D inline AB() const {
                    return ab;
                }

                Line2D inline AC() const {
                    return ac;
                }

                Line2D inline BC() const {
                    return bc;
                }

                void GetPointMinMax(Point2D& min, Point2D& max);

                /// <summary>
                /// 把当前线段旋转围绕center旋转angle角度
                /// </summary>
                void Rotate(const Point2D& center, const Angle& angle);

                /// <summary>
                /// 把线段平移到指定的位置
                /// </summary>
                /// <param name="vector"></param>
                void Move(const Vector2D& vector);

                void Show();

                Point2D inline MidPoint() const {
                    return Point2D((a.X() + b.X() + c.X()) / 3, (a.Y() + b.Y() + c.Y()) / 3);
                }
            private:

                /// <summary>
                /// 三角形的三个点 abc
                /// </summary>
                Point2D a;
                Point2D b;
                Point2D c;

                /// <summary>
                /// 三角形的三条边 ABC
                /// </summary>
                Line2D ab;
                Line2D ac;
                Line2D bc;
                bool valid;
            };
        }
    }
}