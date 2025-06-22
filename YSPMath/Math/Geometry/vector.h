/*
    Created by YSP on 2025-05-11.
*/
#pragma once
#include <object.h>
namespace ysp {
    namespace math {
        namespace geometry {
            class Point2D;
            /*
              ��ά��������ʾ��ԭ��(0,0)ָ���ļ�ͷ������ʾ���λ�ã�����ʾ���ǵ��ƶ���ֵ��
              �����A(1,2) + ����B(3,2)����ѧ�����ǣ���(1,2)������ƽ��3����λ��������ƽ��2����λ��
              �õ��µ�λ�õ�C(4,4)
            */
            class Vector2D : public Object {
                public:
                    Vector2D();
                    Vector2D(double x, double y);
                    Vector2D(const Vector2D& other);
                    
                    /// <summary>
                    /// ���2����ά�������Ƿ���ȣ���x��y�Ƿ����
                    /// </summary>
                    /// <param name="other"></param>
                    /// <returns></returns>
                    bool Equals(const Object& other) const override;

                    /// <summary>
                    /// ��鵱ǰ�����Ƿ�Ϊ������
                    /// </summary>
                    /// <returns></returns>
                    inline bool IsZero() {
                        return x == 0.0 && y == 0.0;
                    }
                    /// <summary>
                   /// ��ȡ��ӡ�����Ϣ
                   /// </summary>
                   /// <returns></returns>
                    std::string ToString() const override;

                    /// <summary>
                    /// ��������X��ֵ
                    /// </summary>
                    /// <returns></returns>
                    inline double X() const {
                        return this->x;
                    }

                    /// <summary>
                    /// ��������Y��ֵ
                    /// </summary>
                    /// <returns></returns>
                    inline double Y() const {
                        return this->y;
                    }

                    /// <summary>
                    /// ���������������ˣ�������������������ɵ�ƽ���ı��ε�������ж�2�������Ƿ�ƽ��
                    /// </summary>
                    /// <param name="other"></param>
                    /// <returns></returns>
                    double inline Cross(const Vector2D& other) const {
                        return x * other.y - other.x * y;
                    }

                    /// <summary>
                    /// ���������������ˣ���B�㵽A���ͶӰ(��B����A���ڵ��߶������ߣ��������ͶӰ��)�ĳ���* A�ĳ���
                    /// </summary>
                    /// <param name="other"></param>
                    /// <returns></returns>
                    double inline Dot(const Vector2D& other) const {
                        return x * other.x + y * other.y;
                    }

                    Point2D ToPoint2D() const;
                protected:
                    double x;
                    double y;
            };

            class Vector3D : public Vector2D {
            public:
                Vector3D();
                Vector3D(double x, double y, double z);
                Vector3D(const Vector3D& other);

                /// <summary>
               /// ���3D�����Ƿ���ȣ���x��y��z�Ƿ����
               /// </summary>
               /// <param name="other"></param>
               /// <returns></returns>
                bool Equals(const Object& other) const override;

                /// <summary>
                /// ��鵱ǰ�����Ƿ�Ϊ������
                /// </summary>
                /// <returns></returns>
                inline bool IsZero() {
                    return x == 0.0 && y == 0.0 && z == 0.0;
                }

                /// <summary>
                /// ���������������ˣ�������һ��������������������ֱ�ڵ�ǰ2��������ɵ�ƽ�棬���������ģ������ƽ������
                /// </summary>
                /// <param name="other"></param>
                /// <returns></returns>
                Vector3D inline Cross(const Vector3D& other) const {
                    return Vector3D(
                        this->y * other.z - other.z * this->y,
                        this->z * other.x - other.x * this->z,
                        this->x * other.y - other.y * this->x
                    );
                }

                /// <summary>
                /// �����
                /// </summary>
                /// <param name="other"></param>
                /// <returns></returns>
                double inline Dot(const Vector3D& other) const {
                    return x * other.x + y * other.y + z * other.z;
                }

                /// <summary>
                /// ��ȡ��ӡ��������Ϣ
                /// </summary>
                /// <returns></returns>
                std::string ToString() const override;

                /// <summary>
                /// ��������Z��ֵ
                /// </summary>
                /// <returns></returns>
                inline double Z() const {
                    return this->z;
                }
            protected:
                double z;
            };
        }
    }
}