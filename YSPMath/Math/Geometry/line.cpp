/*
    Created by YSP on 2025-05-05.
*/
#include "line.h"
#include <complex>
#include "vector.h"
#include "../../Visualization/glwindow.h"
#include <util.h>
using namespace ysp::gl::visualization;
namespace ysp {
    namespace math {
        namespace geometry {
            Line2D::Line2D() :Object() {
                startPoint = Point2D();
                endPoint = Point2D();
            }

            Line2D::Line2D(const Line2D& line2D) :Object() {
                startPoint = line2D.StartPoint();
                endPoint = line2D.EndPoint();
            }

            Line2D::Line2D(const Line2D* line2D) :Object() {
                startPoint = line2D->StartPoint();
                endPoint = line2D->EndPoint();
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
                return Legnth(startPoint,endPoint);
            }

            double Line2D::Legnth(const Point2D& a, const Point2D& b) {
                return std::sqrt(std::pow(a.X() - b.X(), 2) + std::pow(a.Y() - b.Y(), 2));
            }

            std::string Line2D::ToString() const {
                return "Line2D: { points: [" + startPoint.ToString() + "," + endPoint.ToString() + "] [length:" +
                    std::to_string(Length()) + "]}";
            }

            void Line2D::Show() {
                GlWindow::Show(Util::Packing(new int(GL_SHOW_TYPE_LINE2D),new Line2D(this)));
            }

            /// <summary>
            /// 获取最大点和最小点中最大值和最小值拼接的新点
            /// </summary>
            /// <param name="min"></param>
            /// <param name="max"></param>
            void Line2D::GetPointMinMax(Point2D& min, Point2D& max) {
                std::vector<Point2D> points = { startPoint,endPoint };
                Point2D::GetMinMax(points.data(), points.size(),min,max);
            }


            void Line2D::Rotate(const Point2D& center, const Angle& angle) {
                startPoint = startPoint.Rotate(center, angle);
                endPoint = endPoint.Rotate(center, angle);
            }
        }
    }
}
