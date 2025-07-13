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
                /// ���ص�ǰ�������е�����꣬numPoints�ǲ������������ص�����������͸ò����йأ����ֵӦ����ĳһ��ֵ��ƽ��
                /// </summary>
                std::vector<Point3D> Points(int numPoints) const;
                /// <summary>
                /// ���ݼ���t(0-PI)�ͷ�λ��p(0-2PI) ����ֵ������Բ������һ�������
                /// </summary>
                /// <returns></returns>
                Point3D Position(const Radian& t,const Radian& p) const;
                Point3D Position(const Angle& t, const Angle& p) const;
                
                Point3D Position(double t,double p) const;
            private:
                Point3D center;//�������������
                double radius;//����İ뾶
            };
        
        }
    }
}