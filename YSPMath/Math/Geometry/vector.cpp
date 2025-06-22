/*
    Created by YSP on 2025-05-11.
*/
#include "vector.h"
#include "point.h"
namespace ysp {
    namespace math {
        namespace geometry {
           Vector2D::Vector2D():Object(){
               x = 0.0;
               y = 0.0;
           }

           Vector2D::Vector2D(double x, double y):Object(){
               this->x = x;
               this->y = y;
           }

           Vector2D::Vector2D(const Vector2D& other) :Object() {
               this->x = other.x;
               this->y = other.y;
           }

           bool Vector2D::Equals(const Object& other) const {
               const Vector2D* vector2D = dynamic_cast<const Vector2D*>(&other);
               if (vector2D)
                   return this->x == vector2D->X() && this->y == vector2D->Y();
               return Object::Equals(other);
           }

           std::string Vector2D::ToString() const {
               return "Vector2D: {" + std::to_string(x) + "," + std::to_string(y) + "}";
           }

           Point2D Vector2D::ToPoint2D() const {
               return Point2D(x,y);
           }

           Vector3D::Vector3D() : Vector2D() {
               z = 0.0;
           }

           Vector3D::Vector3D(double x, double y, double z) : Vector2D(x, y) {
               this->z = z;
           }

           Vector3D::Vector3D(const Vector3D& other) : Vector2D(other) {
               this->z = other.z;
           }

           bool Vector3D::Equals(const Object& other) const {
               const Vector3D* vector3D = dynamic_cast<const Vector3D*>(&other);
               if (vector3D)
                   return this->x == vector3D->X() &&
                   this->y == vector3D->Y() &&
                   this->z == vector3D->Z();
               return Vector2D::Equals(other);
           }

           std::string Vector3D::ToString() const {
               return "Vector3D: {" + std::to_string(x) + "," +
                   std::to_string(y) + "," + std::to_string(z) + "}";
           }

        }
    }
}
