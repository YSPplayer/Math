//
// Created by YSP on 25-5-5.
//
#pragma once
#include "../object.h"
namespace ysp::math::geometry {
    /*
     * 点是构成几何图形最基本的单元
     *
     */
    class Point2D:public Object {
    public:
        Point2D();
        Point2D(double x, double y);
        Point2D(const Point2D& other);
        bool Equal(const Object &other) const override;
        std::string Print() const override;
        inline double X() const  {
            return this->x;
        }
        inline double Y() const  {
            return this->y;
        }

        //两个点相加
        Point2D inline operator+(const Point2D& other) const {
            return Point2D(x + other.x, y + other.y);
        };

        //两个点相减
        Point2D inline operator-(const Point2D& other) const {
            return Point2D(x - other.x, y - other.y);
        }

        //两个点相乘
        Point2D inline operator*(const Point2D& other) const {
            return Point2D(x * other.x, y * other.y);
        }

        //坐标和标量相乘
        Point2D inline operator*(double scalar) const {
            return Point2D(x * scalar, y * scalar);
        }
        //坐标和标量相除
        Point2D inline operator/(const Point2D& other) const {
            if (other.x == 0 || other.y == 0) {
                throw std::runtime_error("Division by zero");
            }
            return Point2D(x / other.x, y / other.y);
        }
        //坐标和标量相除
        Point2D inline operator/(double scalar) const {
            if (scalar == 0) {
                throw std::runtime_error("Division by zero");
            }
            return Point2D(x / scalar, y / scalar);
        }
    protected:
        double x;
        double y;
    };

    class Point3D:public Point2D {
    public:
        inline double Z() {
            return this->z;
        }
        Point3D();
        Point3D(double x, double y,double z);
        Point3D(const Point3D& other);
        bool Equal(const Object &other) const override;
        std::string Print() const override;
    private:
        double z;
    };

}
