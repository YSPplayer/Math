/*
    Created by YSP on 2025-05-11.
*/
#pragma once
#include <object.h>
namespace ysp {
    namespace math {
        namespace geometry {
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
                    /// �����������������������������ɵ�ƽ���ı��ε����
                    /// </summary>
                    /// <param name="other"></param>
                    /// <returns></returns>
                    double inline operator*(const Vector2D& other) const {
                        return x * other.y - other.x * y;
                    }
                protected:
                    double x;
                    double y;
            };
        }
    }
}