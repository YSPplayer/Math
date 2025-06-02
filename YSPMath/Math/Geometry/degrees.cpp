/*
    Created by YSP on 2025-06-02.
*/
#include "degrees.h"
namespace ysp {
    namespace math {
        namespace geometry {
            Angle Radian::ToAngle() {
                return Angle(value * (180.0 / M_PI));
            }

            Radian Angle::ToRadian() {
                return Radian(value * (M_PI / 180.0));
            }
        }
    }
}