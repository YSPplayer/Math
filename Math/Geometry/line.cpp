//
// Created by YSP on 25-5-7.
//

#include "line.h"
#include <complex>

namespace ysp::math::geometry {
    Line2D::Line2D():Object() {
        startPoint = Point2D();
        endPoint = Point2D();
    }

    Line2D::Line2D(const Point2D &startPoint, const Point2D &endPoint):startPoint(startPoint),endPoint(endPoint),Object() {}

    bool Line2D::Equal(const Object &other) const {
        const Line2D* line2d = dynamic_cast<const Line2D*>(&other);
        if (line2d)
            return startPoint.Equal(line2d->StartPoint()) && endPoint.Equal(line2d->EndPoint());
        return Object::Equal(other);
    }

    //当前线段的长度
    double Line2D::Length() const {
        return std::sqrt(std::pow(startPoint.X() - endPoint.X(),2) + std::pow(startPoint.Y() - endPoint.Y(),2));
    }
}
