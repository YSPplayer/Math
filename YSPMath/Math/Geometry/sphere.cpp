/*
    Created by YSP on 2025-07-1.
*/
#include "sphere.h"
#include <cmath>
namespace ysp {
    namespace math {
        namespace geometry {
            Sphere::Sphere(const Point3D& center, double radius):center(center), radius(radius){}
            std::vector<Point3D> Sphere::Points(int numPoints) const {
                std::vector<Point3D> points;
                //������ܵ���Ӧ���ǿ���ƽ������
                //samplesPerCircle��Ϊ�����ϵ��ܳ�
                int samplesPerCircle = sqrt(numPoints);  // ÿȦ���������������64��������8
                //ÿһ��ά���ϵĵ㶼��Ӧ0-pi֮���ά�ȣ��������ؾ���
                for (int i = 0; i < samplesPerCircle; ++i) {
                    for (int j = 0; j < samplesPerCircle; ++j) {
                        double x = (double)i / (double)samplesPerCircle;
                        double y = (double)j / (double)samplesPerCircle;//��ȡ��ӳ������
                        double p = x * M_PI * 2; //��λ�� ����
                        double t = y * M_PI; //���� ά��
                        points.push_back(Position(t, p));
                    }
                }
                return points;
            }
            Point3D Sphere::Position(const Radian& t, const Radian& p) const {
                return Position(t.Value(),p.Value());
            }


            Point3D Sphere::Position(const Angle& t, const Angle& p) const {
                return Position(t.ToRadian(),p.ToRadian());
            }


            Point3D Sphere::Position(double t, double p) const {
                return Point3D(center.X() + radius * sin(t) * cos(p), center.Y() + radius
                * sin(t) * sin(p) , center.Z() + radius * cos(t));
            }
        }
    }
}