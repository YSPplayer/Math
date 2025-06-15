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
                Acute,//���
                Right,//ֱ��
                Abtuse,//�۽�
                Flat,//ƽ��
                Reflex,//�Ž�
                Round,//�ܽ�
                Surpass,//��Խ ����360 ��С��0
            };
            class Radian;
            /// <summary>
            /// �Ƕ� 
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
                /// �ѵ�ǰ�Ƕȹ�һ����0-360��
                /// </summary>
                /// <returns></returns>
                Angle Normalize() const;

               /// <summary>
               /// �Ƕ�ת����
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
            /// ����
            /// </summary>
            class Radian {
            public:
                Radian(double value) :value(value) {
                };

                inline double Value() const {
                    return value;
                }

                /// <summary>
                /// �ѵ�ǰ���ȹ�һ����0-2PI��
                /// </summary>
                /// <returns></returns>
                Radian Normalize() const;

                /// <summary>
                /// ����ת�Ƕ�
                /// </summary>
                Angle ToAngle() const;
            private:
                double value;
            };
        }
    }
}