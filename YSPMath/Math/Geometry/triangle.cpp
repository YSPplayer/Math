/*
    Created by YSP on 2025-05-05.
*/
#include "triangle.h"
#include "../../Visualization/glwindow.h"
#include <util.h>
using namespace ysp::gl::visualization;
namespace ysp {
    namespace math {
        namespace geometry {
            Triangle2D::Triangle2D(const Point2D& a, const Point2D& b, const Point2D& c):Object(),
            a(a),b(b),c(c){
                //通过是否平行来检查三点是否不共线
                ab = Line2D(a, b);
                ac = Line2D(a, c);
                bc = Line2D(b, c);
                valid = ab.IsParallel(ac);
            }

            Triangle2D::Triangle2D(const Triangle2D* triangle2D) : Triangle2D(triangle2D ? triangle2D->A() : Point2D(),
                triangle2D ? triangle2D->B() : Point2D(),
                triangle2D ? triangle2D->C() : Point2D()) {
                if (!triangle2D) valid = false;
            }

            Triangle2D::Triangle2D(Triangle2D& triangle2D):Triangle2D(&triangle2D){
            }

            Triangle2D::Triangle2D() : Triangle2D(Point2D(),Point2D(),Point2D()) {
            }

            /// <summary>
            /// 获取最大点和最小点中最大值和最小值拼接的新点
            /// </summary>
            /// <param name="min"></param>
            /// <param name="max"></param>
            void Triangle2D::GetPointMinMax(Point2D& min, Point2D& max) {
                std::vector<Point2D> points = { a,b,c };
                Point2D::GetMinMax(points.data(), points.size(), min, max);
            }

            void Triangle2D::Rotate(const Point2D& center, const Angle& angle) {
                // 旋转三个顶点
                a = a.Rotate(center, angle);
                b = b.Rotate(center, angle);
                c = c.Rotate(center, angle);
                // 更新三条边
                ab = Line2D(a, b);
                ac = Line2D(a, c);
                bc = Line2D(b, c);
            }

            void Triangle2D::Show() {
                GlWindow::Show(Util::Packing(new int(GL_SHOW_TYPE_TRIANGLE2D), new Triangle2D(this)));
            }
        }
    }
}