/*
    Created by YSP on 2025-05-11.
*/
#include "round.h"
#include <cmath>
namespace ysp {
    namespace math {
        namespace geometry {
            Round2D::Round2D(const Point2D& center, double radius):Object(),
                center(center),radius(radius){
                
            }

            std::vector<Point2D> Round2D::CirclePoints(int numPoints) const {
                std::vector<Point2D> points;
                double angleStep = 2 * M_PI / numPoints; //²½³¤
                for (int i = 0; i < numPoints; ++i) {
                    double angle = i * angleStep;
                    points.push_back(Position(angle));
                }
                return points;
            }

            Point2D Round2D::Position(double value) const {
                return Point2D(center.X() + radius * cos(value), center.Y() + radius * sin(value));
            }

            Point2D Round2D::Position(const Angle& angle) const {
                return Position(angle.ToRadian().Value());
            }

            Point2D Round2D::Position(const Radian& angle) const {
                return Position(angle.Value());
            }
            
        }
    }
}