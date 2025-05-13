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
            /// �����Σ����ⲻ��ͬһ��ֱ���ϵĵ�������������
            /// </summary>
            class Triangle : public Object {
            public:
                Triangle(const Point2D& a, const Point2D& b, const Point2D& c);
            private:
                /// <summary>
                /// �����ε������� ABC
                /// </summary>
                Point2D a;
                Point2D b;
                Point2D c;
                /// <summary>
                /// �����ε������� ABC
                /// </summary>
                Line2D la;
                Line2D lb;
                Line2D lc;
            };
        }
    }
}