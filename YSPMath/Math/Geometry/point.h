/*
    Created by YSP on 2025-05-05.
*/
#pragma once
#include <object.h>
#include "../Geometry/vector.h"
namespace ysp {
    namespace math {
        namespace geometry {
            /*
             点是构成几何图形最基本的单元
             二维点的数学意义，表示的是二维平面空间内某一个具体的位置，是位置的概念
             */
            class Point2D :public Object {
            public:
                Point2D();
                Point2D(double x, double y);
                Point2D(const Point2D& other);

                /// <summary>
                /// 检查2个二维的点是否相等，即x和y是否相等
                /// </summary>
                /// <param name="other"></param>
                /// <returns></returns>
                bool Equals(const Object& other) const override;

                /// <summary>
                /// 获取打印点的信息
                /// </summary>
                /// <returns></returns>
                std::string Print() const override;

                /// <summary>
                /// 返回坐标X的值
                /// </summary>
                /// <returns></returns>
                inline double X() const {
                    return this->x;
                }

                /// <summary>
                /// 返回坐标Y的值
                /// </summary>
                /// <returns></returns>
                inline double Y() const {
                    return this->y;
                }

                /// <summary>
                /// 点和向量相加，表示点朝着这个方向移动了这么多的距离，结果返回移动后的点
                /// </summary>
                /// <param name="other"></param>
                /// <returns></returns>
                Point2D inline operator+(const Vector2D& other) const {
                    return Point2D(x + other.X(), y + other.Y());
                };

                /// <summary>
                /// 点和向量相减，表示点朝着这个方向移动了这么多的距离，结果返回移动后的点
                /// </summary>
                /// <param name="other"></param>
                /// <returns></returns>
                Point2D inline operator-(const Vector2D& other) const {
                    return Point2D(x - other.X(), y - other.Y());
                }

                /// <summary>
                /// 点和点相减，表示的是两点之间的移动状态，返回的是一个向量
                /// </summary>
                /// <param name="other"></param>
                /// <returns></returns>
                Vector2D inline operator-(const Point2D& other) const {
                    return Vector2D(x - other.X(), y - other.Y());
                }

                //坐标和标量相乘
                Point2D inline operator*(double scalar) const {
                    return Point2D(x * scalar, y * scalar);
                }

                //坐标和标量相除
                Point2D inline operator/(double scalar) const {
                    if (scalar == 0) {
                        throw std::runtime_error("Division by zero");
                    }
                    return Point2D(x / scalar, y / scalar);
                }

                /// <summary>
                /// 归一化坐标点到-1和1的公式
                /// </summary>
                /// <param name="point"></param>
                /// <param name="min_bounds"></param>
                /// <param name="max_bounds"></param>
                /// <returns></returns>
                static Point2D Normalize(const Point2D& point, const Point2D& min_bounds, const Point2D& max_bounds) {
                    // 归一化公式：normalized = 2.0 * (value - min) / (max - min) - 1.0
                    float normalized_x = 2.0f * (point.x - min_bounds.x) / (max_bounds.x - min_bounds.x) - 1.0f;
                    float normalized_y = 2.0f * (point.y - min_bounds.y) / (max_bounds.y - min_bounds.y) - 1.0f;
                    return Point2D(normalized_x, normalized_y);
                }
            protected:
                double x;
                double y;
            };

            class Point3D :public Point2D {
            public:
                inline double Z() {
                    return this->z;
                }
                Point3D();
                Point3D(double x, double y, double z);
                Point3D(const Point3D& other);
                bool Equals(const Object& other) const override;
                std::string Print() const override;
            private:
                double z;
            };

        }
    }
}