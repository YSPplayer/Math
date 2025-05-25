/*
    Created by YSP on 2025-05-25.
*/
#pragma once
#include <util.h>
#include "../Math/Geometry/line.h"
#include "./Geometry/model.h"
#include "./Geometry/data.h"
#include "./Shader/strshader.h"
using namespace ysp::math::geometry;
using namespace ysp::gl::geometry;
namespace ysp {
    namespace gl {
        namespace visualization {
            class ProcBuild {
            public:
                static Model* BuildModelLine2D(Line2D* geometry) {
                    VBOData vboData;
                    vboData.attributeIndex = 2;//2个点组成一个几何图形
                    vboData.type = GL_EBO_TYPE_VECTOR;
                    Point2D min;
                    Point2D max;
                    geometry->GetPointMinMax(min, max);
                    SetMinMaxNextPowerOfTen2D(min, max);
                    Point2D nstart = geometry->StartPoint();
                    Point2D nend = geometry->EndPoint();
                    nstart = Point2D::Normalize(nstart, min, max);
                    nend = Point2D::Normalize(nend, min, max);
                    vboData.data.push_back(nstart.X());
                    vboData.data.push_back(nstart.Y());
                    vboData.data.push_back(nend.X());
                    vboData.data.push_back(nend.Y());
                    Model* model = new Model;
                    model->SetVShader(V_Line2DShader);
                    model->SetFShader(F_Line2DShader);
                    model->SetVBOS({ vboData });
                    model->Build(GL_SHOW_TYPE_LINE2D);
                    return model;
                };

                /// <summary>
                /// 构建模型坐标轴
                /// </summary>
                /// <param name="geometry"></param>
                /// <returns></returns>
                static Model* BuildModelLine2DAxis(Line2D* geometry) {
                    VBOData vboData;
                    vboData.attributeIndex = 2;//2个点组成一个几何图形
                    vboData.type = GL_EBO_TYPE_VECTOR;
                    Point2D min;
                    Point2D max;
                    geometry->GetPointMinMax(min, max);
                    SetMinMaxNextPowerOfTen2D(min, max);
                    //获取到最小值和最大值，用这2个值来可视化坐标轴
                    Point2D nstartx = {min.X(),0};
                    Point2D nendx = { max.X(),0 };
                    Point2D nstarty = {0, min.Y() };
                    Point2D nendy = {0, max.Y() };
                    nstartx = Point2D::Normalize(nstartx, min, max);
                    nendx = Point2D::Normalize(nendx, min, max);
                    nstarty = Point2D::Normalize(nstarty, min, max);
                    nendy = Point2D::Normalize(nendy, min, max);
                    PushVector(vboData.data, { nstartx,nendx,nstarty,nendy });
                    Model* model = new Model;
                    model->SetVShader(V_Line2DShader);
                    model->SetFShader(F_Line2DShader);
                    model->SetVBOS({ vboData });
                    model->Build(GL_SHOW_TYPE_LINE2D);
                    return model;
                }
            private:
                ProcBuild() {};
                static void  PushVector(std::vector<float>& vector,const std::vector<Point2D>& datas) {
                    for (int i = 0; i < datas.size(); ++i) {
                        vector.push_back(datas[i].X());
                        vector.push_back(datas[i].Y());
                    }
                };
                static void SetMinMaxNextPowerOfTen2D(Point2D& min, Point2D& max) {
                    double min_x = std::abs(Util::NextPowerOfTen(min.X()));
                    double min_y = std::abs(Util::NextPowerOfTen(min.Y()));
                    double max_x = std::abs(Util::NextPowerOfTen(max.X()));
                    double max_y = std::abs(Util::NextPowerOfTen(max.Y()));
                    double maxValue = std::max({ min_x,min_y,max_x,max_y });
                    double minValue = -maxValue;
                    min = { minValue,minValue };
                    max = { maxValue,maxValue };
                };
            };
        }
    }
}