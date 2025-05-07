//
// Created by YSP on 25-5-7.
//

#pragma once
#include "point.h"
#include  "../object.h"
namespace ysp::math::geometry {
    class Line2D : public Object {
    public:
        Line2D();
        Line2D(const Point2D& startPoint, const Point2D& endPoint);
        bool Equal(const Object &other) const override;
        //检查当前线段是否合法
        bool inline Iscoincide() const {
            return startPoint.Equal(endPoint);
        }

        Point2D inline StartPoint() const {
            return startPoint;
        }

        Point2D inline EndPoint() const {
            return endPoint;
        }
        double Length() const;
        //获取到当前线段的中点
        Point2D inline MidPoint() const {
            return (startPoint + endPoint) / 2;
        }
    private:
        Point2D startPoint;
        Point2D endPoint;
    };

}
