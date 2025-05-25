/*
    Created by YSP on 2025-05-25.
*/
#pragma once
namespace ysp {
    class Color {
    private:
        unsigned char r, g, b, a;  // 0-255��Χ

    public:
        // ���캯��
        Color() : r(0), g(0), b(0), a(255) {}
        Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255)
            : r(red), g(green), b(blue), a(alpha) {}

        // ��ȡ��ɫ����
        unsigned char R() const { return r; }
        unsigned char G() const { return g; }
        unsigned char B() const { return b; }
        unsigned char A() const { return a; }

        // ������ɫ����
        void SetR(unsigned char value) { r = value; }
        void SetG(unsigned char value) { g = value; }
        void SetB(unsigned char value) { b = value; }
        void SetA(unsigned char value) { a = value; }

        // ��һ����ɫֵ��0.0-1.0��Χ
        float RF() const { return r / 255.0f; }
        float GF() const { return g / 255.0f; }
        float BF() const { return b / 255.0f; }
        float AF() const { return a / 255.0f; }

        // ����������ɫ
        void SetColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255) {
            r = red; g = green; b = blue; a = alpha;
        }
    };

    class Style {
    public:
        inline static const Color DefaultColor = Color(41, 224, 63); //C++17��׼
    };
}