/*
    Created by YSP on 2025-06-02.
*/
#pragma once
#include <object.h>
namespace ysp {
    namespace math {
        namespace geometry {
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif // !M_PI
          
            enum AngleType {
                Acute,//锐角
                Right,//直角
                Abtuse,//钝角
                Flat,//平角
                Reflex,//优角
                Round,//周角
                Surpass,//超越 大于360 或小于0
            };
            class Radian;
            /// <summary>
            /// 角度 
            /// </summary>
            class Angle {
            public:
                Angle(double value) :value(value){
                    SetType();
                };

                inline double Value() const {
                    return value;
                }
                inline double& Value() {
                    return value;
                }
                inline AngleType Type() const {
                    return type;
                }

                /// <summary>
                /// 把当前角度归一化到0-360度
                /// </summary>
                /// <returns></returns>
                Angle Normalize() const;

               /// <summary>
               /// 角度转弧度
               /// </summary>
                Radian ToRadian() const;
            private:
                double value;
                AngleType type;
                void SetType() {
                    if (value > 0.0 && value < 90.0) type = Acute;
                    else if (value == 90.0) type = Right;
                    else if (value > 90.0 && value < 180.0) type = Abtuse;
                    else if (value == 180.0) type = Flat;
                    else if (value > 180.0 && value < 360.0) type = Reflex;
                    else if (value == 360.0) type = Round;
                    else type == Surpass;
                }
            };

            /// <summary>
            /// 弧度
            /// </summary>
            class Radian {
            public:
                Radian(double value) :value(value) {
                };

                inline double Value() const {
                    return value;
                }

                /// <summary>
                /// 把当前弧度归一化到0-2PI度
                /// </summary>
                /// <returns></returns>
                Radian Normalize() const;

                /// <summary>
                /// 弧度转角度
                /// </summary>
                Angle ToAngle() const;
            private:
                double value;
            };
        }
    }
}