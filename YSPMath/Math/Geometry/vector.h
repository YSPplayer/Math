/*
    Created by YSP on 2025-05-11.
*/
#pragma once
#include <object.h>
namespace ysp {
    namespace math {
        namespace geometry {
            class Point2D;
            /*
              二维向量，表示从原点(0,0)指向点的箭头，不表示点的位置，而表示的是点移动的值，
              比如点A(1,2) + 向量B(3,2)的数学意义是：点(1,2)先向右平移3个单位，再向上平移2个单位，
              得到新的位置点C(4,4)
            */
            class Vector2D : public Object {
                public:
                    Vector2D();
                    Vector2D(double x, double y);
                    Vector2D(const Vector2D& other);
                    
                    /// <summary>
                    /// 检查2个二维的向量是否相等，即x和y是否相等
                    /// </summary>
                    /// <param name="other"></param>
                    /// <returns></returns>
                    bool Equals(const Object& other) const override;

                    /// <summary>
                    /// 检查当前向量是否为零向量
                    /// </summary>
                    /// <returns></returns>
                    inline bool IsZero() {
                        return x == 0.0 && y == 0.0;
                    }
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
                    /// 向量的外项积（叉乘），返回两个向量所组成的平行四边形的面积，判断2个向量是否平行
                    /// </summary>
                    /// <param name="other"></param>
                    /// <returns></returns>
                    double inline Cross(const Vector2D& other) const {
                        return x * other.y - other.x * y;
                    }

                    /// <summary>
                    /// 向量的内项积（点乘），B点到A点的投影(从B点往A所在的线段做垂线，交点就是投影点)的长度* A的长度
                    /// </summary>
                    /// <param name="other"></param>
                    /// <returns></returns>
                    double inline Dot(const Vector2D& other) const {
                        return x * other.x + y * other.y;
                    }

                    Point2D ToPoint2D() const;
                protected:
                    double x;
                    double y;
            };

            class Vector3D : public Vector2D {
            public:
                Vector3D();
                Vector3D(double x, double y, double z);
                Vector3D(const Vector3D& other);

                /// <summary>
               /// 检查3D向量是否相等，即x、y和z是否都相等
               /// </summary>
               /// <param name="other"></param>
               /// <returns></returns>
                bool Equals(const Object& other) const override;

                /// <summary>
                /// 检查当前向量是否为零向量
                /// </summary>
                /// <returns></returns>
                inline bool IsZero() {
                    return x == 0.0 && y == 0.0 && z == 0.0;
                }

                /// <summary>
                /// 向量的外项积（叉乘），返回一个结果向量，这个向量垂直于当前2个向量组成的平面，结果向量的模长等于平面的面积
                /// </summary>
                /// <param name="other"></param>
                /// <returns></returns>
                Vector3D inline Cross(const Vector3D& other) const {
                    return Vector3D(
                        this->y * other.z - other.z * this->y,
                        this->z * other.x - other.x * this->z,
                        this->x * other.y - other.y * this->x
                    );
                }

                /// <summary>
                /// 内项积
                /// </summary>
                /// <param name="other"></param>
                /// <returns></returns>
                double inline Dot(const Vector3D& other) const {
                    return x * other.x + y * other.y + z * other.z;
                }

                /// <summary>
                /// 获取打印向量的信息
                /// </summary>
                /// <returns></returns>
                std::string ToString() const override;

                /// <summary>
                /// 返回坐标Z的值
                /// </summary>
                /// <returns></returns>
                inline double Z() const {
                    return this->z;
                }
            protected:
                double z;
            };
        }
    }
}