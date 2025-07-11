/*
    Created by YSP on 2025-05-05.
*/
#pragma once
#include "point.h"
#include <object.h>
namespace ysp {
    namespace math {
        namespace geometry {
            class Line2D : public Object {
            public:
                Line2D();
                Line2D(const Line2D& line2D);
                Line2D(const Line2D* line2D);
                Line2D(const Point2D& startPoint, const Point2D& endPoint);

                /// <summary>
                /// 检查线段是否相等，根据距离来判断
                /// </summary>
                /// <param name="other"></param>
                /// <returns></returns>
                bool Equals(const Object& other) const override;
                
                /// <summary>
                /// 检查当前线段是否是有效的,返回True表示有效，如果线段上两点重合则表示这个线段是无效的
                /// </summary>
                /// <returns></returns>
                bool inline IsValid() const {
                    return !startPoint.Equals(endPoint);
                }

                /// <summary>
                /// 检查2条线段之间的关系是否平行
                /// </summary>
                /// <returns></returns>
                bool IsParallel(const Line2D& line);

                /// <summary>
                /// 检查2条线段是否垂直
                /// </summary>
                /// <param name="line"></param>
                /// <returns></returns>
                bool IsVertical(const Line2D& line);

                /// <summary>
                /// 返回线段开始的点 
                /// </summary>
                /// <returns></returns>
                Point2D inline StartPoint() const {
                    return startPoint;
                }

                /// <summary>
                /// 返回线段结束的点
                /// </summary>
                /// <returns></returns>
                Point2D inline EndPoint() const {
                    return endPoint;
                }
                
                /// <summary>
                /// 计算当前线段的长度，勾股定理  ----|
                /// </summary>
                /// <returns></returns>
                double Length() const;
                
                /// <summary>
                /// 计算2点之间的距离长度
                /// </summary>
                /// <param name="a"></param>
                /// <param name="b"></param>
                /// <returns></returns>
                static double Legnth(const Point2D& a,const Point2D& b);
                /// <summary>
                /// 获取到当前线段的中点，M = (A.x + (B.x - A.x) / 2, A.y + (B.y - A.y))
                /// 化简可得M = ((A.x + B.x) / 2,(A.y + B.y) / 2)
                /// </summary>
                /// <returns></returns>
                Point2D inline MidPoint() const {
                    return Point2D((startPoint.X() + endPoint.X()) / 2, (startPoint.Y() + endPoint.Y()) / 2);
                }

                /// <summary>
                /// 获取打印线段的信息
                /// </summary>
                /// <returns></returns>
                std::string ToString() const override;

                /// <summary>
                /// 可视化线段
                /// </summary>
                void Show();

                /// <summary>
                 /// 遍历创建最大值点和最小值点 从X得Y，由因到果。数能描述世界，
                 /// </summary>
                 /// <param name="points"></param>
                 /// <param name="size"></param>
                 /// <param name="min"></param>
                 /// <param name="max"></param>
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

                /// <summary>
                /// 缩放模型
                /// </summary>
                /// <param name="value"></param>
                void Scale(double value);
            private:
                Point2D startPoint;
                Point2D endPoint;
            };

            class Line3D : public Object {
            public:
                Line3D();
                Line3D(const Line3D& line3D);
                Line3D(const Line3D* line3D);
                Line3D(const Point3D& startPoint, const Point3D& endPoint);

                /// <summary>
                /// 检查线段是否相等，根据距离来判断
                /// </summary>
                bool Equals(const Object& other) const override;

                /// <summary>
                /// 返回线段开始的三维点
                /// </summary>
                Point3D inline StartPoint() const {
                    return startPoint;
                }

                /// <summary>
                /// 返回线段结束的三维点
                /// </summary>
                Point3D inline EndPoint() const {
                    return endPoint;
                }

                /// <summary>
                /// 计算当前三维线段的长度，三维空间勾股定理
                /// </summary>
                double Length() const;

                /// <summary>
                /// 计算两个三维点之间的距离
                /// </summary>
                static double Length(const Point3D& a, const Point3D& b);

                /// <summary>
                /// 获取三维线段的中点
                /// </summary>
                Point3D inline MidPoint() const {
                    return Point3D(
                        (startPoint.X() + endPoint.X()) / 2,
                        (startPoint.Y() + endPoint.Y()) / 2,
                        (startPoint.Z() + endPoint.Z()) / 2
                    );
                }

                /// <summary>
                /// 检查两条三维线段是否平行
                /// </summary>
                bool IsParallel(const Line3D& line);

                /// <summary>
                /// 检查是否垂直
                /// </summary>
                bool IsVertical(const Line3D& line);


                /// <summary>
                /// 把当前三维线段围绕指定轴旋转指定角度
                /// </summary>
                void Rotate(const Point3D& center, const Vector3D& axis, const Angle& angle);

                /// <summary>
                /// 把三维线段平移到指定的位置
                /// </summary>
                void Move(const Vector3D& vector);

                /// <summary>
                /// 缩放三维线段
                /// </summary>
                void Scale(double value);

                /// <summary>
                /// 获取打印三维线段的信息
                /// </summary>
                std::string ToString() const override;
            private:
                Point3D startPoint;
                Point3D endPoint;
            };

        }
    }
}
