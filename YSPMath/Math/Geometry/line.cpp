/*
    Created by YSP on 2025-05-05.
*/
#include "line.h"
#include <complex>
#include "vector.h"
namespace ysp {
    namespace math {
        namespace geometry {
            Line2D::Line2D() :Object() {
                startPoint = Point2D();
                endPoint = Point2D();
            }

            Line2D::Line2D(const Point2D& startPoint, const Point2D& endPoint) :startPoint(startPoint), endPoint(endPoint), Object() {}

            bool Line2D::Equals(const Object& other) const {
                const Line2D* line2d = dynamic_cast<const Line2D*>(&other);
                if (line2d)
                    return startPoint.Equals(line2d->StartPoint()) && endPoint.Equals(line2d->EndPoint());
                return Object::Equals(other);
            }

            bool Line2D::IsParallel(const Line2D& line) {
                const Vector2D& v1 = endPoint - startPoint;
                const Vector2D& v2 = line.endPoint - line.startPoint;
                //如果两个向量相乘为0，说明所组成的平行四边型的面积为0，说明没有办法组成，平行
                return v1 * v2 == 0.0;
            }

            double Line2D::Length() const {
                return std::sqrt(std::pow(startPoint.X() - endPoint.X(), 2) + std::pow(startPoint.Y() - endPoint.Y(), 2));
            }

            std::string Line2D::Print() const {
                return "Line2D: { points: [" + startPoint.Print() + "," + endPoint.Print() + "] [length:" +
                    std::to_string(Length()) + "]}";
            }

            void Line2D::Show() {


            }
        }
    }
}
