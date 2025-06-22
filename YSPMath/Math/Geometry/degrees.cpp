/*
    Created by YSP on 2025-06-02.
*/
#include "degrees.h"
namespace ysp {
    namespace math {
        namespace geometry {
            Angle Radian::ToAngle() const {
                return Angle(value * (180.0 / M_PI));
            }

            Angle Angle::Normalize() const {
                double angle = fmod(value,360.0);
                return (value < 0) ? angle + 360.0 : angle;
            }

            Radian Angle::ToRadian() const {
                return Radian(value * (M_PI / 180.0));
            }

            Radian Radian::Normalize() const {
                const double twoPI = 2.0 * M_PI;
                double radian = fmod(value, twoPI);
                return (radian < 0) ? radian + twoPI : radian; 
            }
        }
    }
}