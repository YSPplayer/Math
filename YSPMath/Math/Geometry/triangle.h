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
            /// �����Σ����ⲻ��ͬһ��ֱ���ϵĵ�(�����ߵ�������)�������������
            /// </summary>
            class Triangle2D : public Object {
            public:
                Triangle2D(const Point2D& a, const Point2D& b, const Point2D& c);
                Triangle2D(const Triangle2D* triangle2D);
                Triangle2D(Triangle2D& triangle2D);
                Triangle2D();
                /// <summary>
                /// ��鵱ǰ�������Ƿ�Ϊ��Ч������
                /// </summary>
                /// <returns></returns>
                bool inline IsValid() const {
                    return valid;
                }

                /// <summary>
                /// ��������������ߵĳ���
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
                /// ��ȡ���������Ե�ǰ��Ϊ�������������(�����Ƕ���ͶԱ��߶ε��е�����ɵ��߶�)
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
                /// ��ȡ�����ε�������
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
                /// ��ȡ�����ε�������
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
                /// �ѵ�ǰ�߶���תΧ��center��תangle�Ƕ�
                /// </summary>
                void Rotate(const Point2D& center, const Angle& angle);

                /// <summary>
                /// ���߶�ƽ�Ƶ�ָ����λ��
                /// </summary>
                /// <param name="vector"></param>
                void Move(const Vector2D& vector);

                void Show();

                Point2D inline MidPoint() const {
                    return Point2D((a.X() + b.X() + c.X()) / 3, (a.Y() + b.Y() + c.Y()) / 3);
                }
            private:

                /// <summary>
                /// �����ε������� abc
                /// </summary>
                Point2D a;
                Point2D b;
                Point2D c;

                /// <summary>
                /// �����ε������� ABC
                /// </summary>
                Line2D ab;
                Line2D ac;
                Line2D bc;
                bool valid;
            };
        }
    }
}