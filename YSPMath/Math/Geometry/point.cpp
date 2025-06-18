/*
    Created by YSP on 2025-05-05.
*/
#include <cmath>
#include "point.h"
#include "line.h"
namespace ysp {
    namespace math {
        namespace geometry {
            Point2D::Point2D() :Object() {
                x = 0.0;
                y = 0.0;
            }

            Point2D::Point2D(double x, double y) :Object() {
                this->x = x;
                this->y = y;
            }

            Point2D::Point2D(const Point2D& other) :Object() {
                this->x = other.x;
                this->y = other.y;
            }

            bool Point2D::Equals(const Object& other) const {
                const Point2D* point2d = dynamic_cast<const Point2D*>(&other);
                if (point2d)
                    return this->x == point2d->X() && this->y == point2d->Y();
                return Object::Equals(other);

            }

            std::string Point2D::ToString() const {
                return "Point2D: {" + std::to_string(x) + "," + std::to_string(y) + "}";
            }

            Point2D Point2D::Rotate(const Point2D& center, const Angle& angle) {
                //// 如果当前点就是旋转中心，直接返回中心点（无需旋转）
                //if (this->Equals(center)) return Point2D(center.X(), center.Y());

                //// 1. 将当前点视为以center为圆心的圆上的点
                //// 2. 计算当前点到圆心的距离（即圆的半径）
                //double r = Line2D::Legnth(*this, center);

                //// 3. 计算当前点在圆上的极角（使用atan2自动处理象限）
                ////    atan2(y,x)返回[-π,π]的值，Normalize()将其转换到[0,2π]范围
                //const Radian& rad = Radian(atan2(this->Y() - center.Y(), this->X() - center.X())).Normalize();

                //// 4. 将要旋转的角度转换为弧度（并标准化）
                //const Radian& rotaterad = angle.Normalize().ToRadian();

                //// 5. 计算旋转后的最终角度（标准化到[0,2π]）
                //double resultrad = Radian(rad.Value() + rotaterad.Value()).Normalize().Value();

                //// 6. 计算旋转后的新坐标（极坐标转笛卡尔坐标）
                //return Point2D(center.X() + r * cos(resultrad), center.Y() + r * sin(resultrad));
                // 如果当前点就是旋转中心，直接返回中心点（无需旋转）
                if (this->Equals(center)) return *this;
                // 转换为相对坐标
                double dx = this->X() - center.X();
                double dy = this->Y() - center.Y();
                // 计算旋转量（提前转换为弧度并标准化）
                double rad = angle.Normalize().ToRadian().Value();
                double cosTheta = cos(rad);
                double sinTheta = sin(rad);
                // 应用旋转矩阵
                return Point2D(
                    center.X() + dx * cosTheta - dy * sinTheta,
                    center.Y() + dx * sinTheta + dy * cosTheta
                );
            }

            Point2D Point2D::Move(const Vector2D& vector) {

                return *this + vector;
            }

            Point2D Point2D::Scale(double value) {
                return (*this) * value;
            }


            void Point2D::GetMinMax(Point2D* points, int size, Point2D& min, Point2D& max) {
                double min_x = std::numeric_limits<double>::max();
                double min_y = std::numeric_limits<double>::max();
                double max_x = std::numeric_limits<double>::lowest();
                double max_y = std::numeric_limits<double>::lowest();
                for (int i = 0; i < size; ++i) {
                    const Point2D& point = points[i];
                    min_x = std::min(min_x, point.X());
                    min_y = std::min(min_y, point.Y());
                    max_x = std::max(max_x, point.X());
                    max_y = std::max(max_y, point.Y());
                }
                min = Point2D(min_x,min_y);
                max = Point2D(max_x, max_y);
            }

            Point2D Point3D::ToPoint2D() const {
                return Point2D(x,y);
            }

            Point3D::Point3D() :Point2D() {
                this->z = 0.0;
            }

            Point3D::Point3D(double x, double y, double z) :Point2D(x, y) {
                this->z = z;
            }

            Point3D::Point3D(const Point3D& other) :Point2D(other) {
                this->z = other.z;
            }

            Point3D::Point3D(const Point2D& other) :Point2D(other) {
                this->z = 0.0;
            }

            bool Point3D::Equals(const Object& other) const {
                const Point3D* point3d = dynamic_cast<const Point3D*>(&other);
                if (point3d) return point3d->z == this->z && Point2D::Equals(other);
                return Object::Equals(other);
            }

            std::string Point3D::ToString() const {
                return "{" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "}";
            }
        }
    }
}