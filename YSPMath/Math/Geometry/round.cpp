/*
    Created by YSP on 2025-05-11.
*/
#include "round.h"
#include <cmath>
namespace ysp {
    namespace math {
        namespace geometry {
            Round2D::Round2D(const Point2D& center, double radius):Object(),
                center(center),radius(radius){
                
            }

            Point2D Round2D::Position(double value) const {
                return Point2D(center.X() + radius * cos(value), center.Y() + radius * sin(value));
            }

            Point2D Round2D::Position(const Angle& angle) const {
                return Position(angle.ToRadian().Value());
            }

            Point2D Round2D::Position(const Radian& angle) const {
                return Position(angle.Value());
            }
            
        }
    }
}