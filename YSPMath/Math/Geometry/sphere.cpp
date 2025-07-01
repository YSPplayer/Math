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
                for (int i = 0; i < samplesPerCircle; ++i) {
                    double t = M_PI * i / samplesPerCircle;  // 极角[0,π]   当前点占比周长的多少
                    //这个是方位角的周长
                    int pointsAtLatitude = samplesPerCircle * sin(t);  // 当前纬度的点数 周长* sint(t)
                    if (pointsAtLatitude < 1) pointsAtLatitude = 1;
                    for (int j = 0; j < pointsAtLatitude; ++j) {
                        double p = 2 * M_PI * j / pointsAtLatitude;  // 方位角[0,2π]
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