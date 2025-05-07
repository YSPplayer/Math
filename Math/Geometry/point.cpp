//
// Created by YSP on 25-5-5.
//
#include "point.h"
namespace ysp::math::geometry {
    Point2D::Point2D():Object() {
        x = 0.0;
        y = 0.0;
    }

    Point2D::Point2D(double x, double y):Object() {
        this->x = x;
        this->y = y;
    }

    Point2D::Point2D(const Point2D &other):Object() {
        this->x = other.x;
        this->y = other.y;
    }

    bool Point2D::Equal(const Object &other) const {
        const Point2D* point2d = dynamic_cast<const Point2D*>(&other);
        if (point2d)
            return this->x == point2d->X() && this->y == point2d->Y();
        return Object::Equal(other);

    }
    std::string Point2D::Print() const {
        return "{" + std::to_string(x) + "," + std::to_string(y) + "}";
    }

    Point3D::Point3D():Point2D() {
        this->z = 0.0;
    }

    Point3D::Point3D(double x, double y, double z):Point2D(x,y) {
        this->z = z;
    }

    Point3D::Point3D(const Point3D &other):Point2D(other) {
        this->z = other.z;
    }

    bool Point3D::Equal(const Object &other) const {
        const Point3D* point3d = dynamic_cast<const Point3D*>(&other);
        if (point3d) return point3d->z == this->z && Point2D::Equal(other);
        return Object::Equal(other);
    }

    std::string Point3D::Print() const {
        return "{" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "}";
    }
}
