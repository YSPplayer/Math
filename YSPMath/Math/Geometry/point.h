/*
    Created by YSP on 2025-05-05.
*/
#pragma once
#include <object.h>
#include "../Geometry/vector.h"
#include "degrees.h"
#include <util.h>
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
                std::string ToString() const override;

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
                /// 让当前坐标点沿着point点逆时针旋转angle度，返回旋转之后的坐标
                /// </summary>
                /// <param name="point"></param>
                /// <param name="angle"></param>
                /// <returns></returns>
                Point2D Rotate(const Point2D& center,const Angle& angle);

                /// <summary>
                /// 归一化坐标点到n和m的公式
                /// </summary>
                /// <param name="point"></param>
                /// <param name="min_bounds"></param>
                /// <param name="max_bounds"></param>
                /// <returns></returns>
                static Point2D Normalize(const Point2D& point, const Point2D& min_bounds, const Point2D& max_bounds,
                    float target_min = -1.0f, float target_max = 1.0f) {
                    float normalized_x = (target_max - target_min) * (point.x - min_bounds.x) / (max_bounds.x - min_bounds.x) + target_min;
                    float normalized_y = (target_max - target_min) * (point.y - min_bounds.y) / (max_bounds.y - min_bounds.y) + target_min;
                    return Point2D(normalized_x, normalized_y);
                }

                /// <summary>
                /// 反归一化公式，输出归一化之后坐标的真实值
                /// </summary>
                /// <param name="normalized_point">归一化后的点</param>
                /// <param name="min_bounds">原始最小边界</param>
                /// <param name="max_bounds">原始最大边界</param>
                /// <param name="normalized_min">归一化时使用的最小值，默认-1.0f</param>
                /// <param name="normalized_max">归一化时使用的最大值，默认1.0f</param>
                /// <returns>原始坐标系中的点</returns>
                static Point2D Denormalize(const Point2D& normalized_point,
                    const Point2D& min_bounds,
                    const Point2D& max_bounds,
                    float normalized_min = -1.0f,
                    float normalized_max = 1.0f) {
                    // 反归一化公式：value = (normalized - normalized_min) * (max - min) / (normalized_max - normalized_min) + min
                    float real_x = (normalized_point.x - normalized_min) * (max_bounds.x - min_bounds.x)
                        / (normalized_max - normalized_min) + min_bounds.x;
                    float real_y = (normalized_point.y - normalized_min) * (max_bounds.y - min_bounds.y)
                        / (normalized_max - normalized_min) + min_bounds.y;
                    return Point2D(real_x, real_y);
                }

                /// <summary>
                /// 获取到当前2个点之后的最大整数点
                /// </summary>
                /// <param name="min"></param>
                /// <param name="max"></param>
                static void SetMinMaxNextPowerOfTen2D(Point2D& min, Point2D& max) {
                    double min_x = std::abs(Util::NextPowerOfTen(min.X()));
                    double min_y = std::abs(Util::NextPowerOfTen(min.Y()));
                    double max_x = std::abs(Util::NextPowerOfTen(max.X()));
                    double max_y = std::abs(Util::NextPowerOfTen(max.Y()));
                    double maxValue = std::max({ min_x,min_y,max_x,max_y });
                    double minValue = -maxValue;
                    min = { minValue,minValue };
                    max = { maxValue,maxValue };
                };

                /// <summary>
                /// 遍历创建最大值点和最小值点
                /// </summary>
                /// <param name="points"></param>
                /// <param name="size"></param>
                /// <param name="min"></param>
                /// <param name="max"></param>
                static void GetMinMax(Point2D* points,int size,Point2D& min,Point2D& max);
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
                std::string ToString() const override;
            private:
                double z;
            };

        }
    }
}