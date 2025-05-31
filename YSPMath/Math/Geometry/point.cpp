/*
    Created by YSP on 2025-05-05.
*/
#include "point.h"
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

            Point3D::Point3D() :Point2D() {
                this->z = 0.0;
            }

            Point3D::Point3D(double x, double y, double z) :Point2D(x, y) {
                this->z = z;
            }

            Point3D::Point3D(const Point3D& other) :Point2D(other) {
                this->z = other.z;
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