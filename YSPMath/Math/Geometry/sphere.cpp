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
                for (int i = 0; i < samplesPerCircle; ++i) {
                    double t = M_PI * i / samplesPerCircle;  // ����[0,��]   ��ǰ��ռ���ܳ��Ķ���
                    //����Ƿ�λ�ǵ��ܳ�
                    int pointsAtLatitude = samplesPerCircle * sin(t);  // ��ǰγ�ȵĵ��� �ܳ�* sint(t)
                    if (pointsAtLatitude < 1) pointsAtLatitude = 1;
                    for (int j = 0; j < pointsAtLatitude; ++j) {
                        double p = 2 * M_PI * j / pointsAtLatitude;  // ��λ��[0,2��]
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