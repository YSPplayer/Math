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
                //如果两个向量外项积(叉乘)为0，说明所组成的平行四边型的面积为0，说明没有办法组成，平行
                return v1.Cross(v2) == 0.0;
            }

            bool Line2D::IsVertical(const Line2D& line) {
                //如果内项积为0，则表示2条线段垂直
                const Vector2D& v1 = endPoint - startPoint;
                const Vector2D& v2 = line.endPoint - line.startPoint;
                return v1.Dot(v2) == 0.0;
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

            void Line2D::Move(const Vector2D& vector) {
                startPoint = startPoint.Move(vector);
                endPoint = endPoint.Move(vector);
            }

            void Line2D::Scale(double value) {
                startPoint = startPoint.Scale(value);
                endPoint = endPoint.Scale(value);
            }


            Line3D::Line3D() :Object() {
                startPoint = Point3D();
                endPoint = Point3D();
            }

            Line3D::Line3D(const Line3D& line3D) : Line3D(line3D) {}

            Line3D::Line3D(const Line3D* line3D) : Line3D(line3D) {}

            Line3D::Line3D(const Point3D& startPoint, const Point3D& endPoint)
                : startPoint(startPoint), endPoint(endPoint) {}


            bool Line3D::Equals(const Object& other) const {
                const Line3D* line3d = dynamic_cast<const Line3D*>(&other);
                if (line3d)
                    return startPoint.Equals(line3d->startPoint) &&
                    endPoint.Equals(line3d->endPoint);
                return Object::Equals(other);
            }

            double Line3D::Length() const {
                return Length(startPoint, endPoint);
            }

            double Line3D::Length(const Point3D& a, const Point3D& b) {
                return std::sqrt(std::pow(a.X() - b.X(), 2) +
                    std::pow(a.Y() - b.Y(), 2) +
                    std::pow(a.Z() - b.Z(), 2));
            }

            /// <summary>
            /// 三维平面上，向量外项积叉积的结果的模长就等于组成的平行四边形的面积
            /// </summary>
            /// <param name="line"></param>
            /// <returns></returns>
            bool Line3D::IsParallel(const Line3D& line) {
                const Vector3D& v1 = endPoint - startPoint;
                const Vector3D& v2 = line.endPoint - line.startPoint;
                return v1.Cross(v2).IsZero();

            }

            bool Line3D::IsVertical(const Line3D& line) {
                const Vector3D& v1 = endPoint - startPoint;
                const Vector3D& v2 = line.endPoint - line.startPoint;
                return v1.Dot(v2) == 0.0;
            }


        }
    }
}
