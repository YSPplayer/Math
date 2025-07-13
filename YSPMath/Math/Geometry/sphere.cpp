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
                //球体的总点数应该是可以平方根的
                //samplesPerCircle作为极角上的周长
                int samplesPerCircle = sqrt(numPoints);  // 每圈采样数，如果传入64，则结果是8
                //每一个维度上的点都对应0-pi之间的维度，所以外层控经度
                for (int i = 0; i < samplesPerCircle; ++i) {
                    for (int j = 0; j < samplesPerCircle; ++j) {
                        double x = (double)i / (double)samplesPerCircle;
                        double y = (double)j / (double)samplesPerCircle;//获取到映射区间
                        double p = x * M_PI * 2; //方位角 经度
                        double t = y * M_PI; //极角 维度
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