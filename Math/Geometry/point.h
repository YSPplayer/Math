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
        inline double X() const  {
            return this->x;
        }
        inline double Y() const  {
            return this->y;
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
    private:
        double z;
    };

}
