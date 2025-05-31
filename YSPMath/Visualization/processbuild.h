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
                    Point2D::SetMinMaxNextPowerOfTen2D(min, max);
                    Point2D nstart = geometry->StartPoint();
                    Point2D nend = geometry->EndPoint();
                    float nmin = -0.9f;
                    float namx = 0.9f;
                    nstart = Point2D::Normalize(nstart, min, max,nmin,namx);
                    nend = Point2D::Normalize(nend, min, max, nmin, namx);
                    vboData.data.push_back(nstart.X());
                    vboData.data.push_back(nstart.Y());
                    vboData.data.push_back(nend.X());
                    vboData.data.push_back(nend.Y());
                    Model* model = new Model;
                    model->SetVShader(V_Line2DShader);
                    model->SetFShader(F_Line2DShader);
                    model->SetVBOS({ vboData });
                    model->Build(GL_SHOW_TYPE_LINE2D);
                    model->SetName("Line2D");
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
                    Point2D::SetMinMaxNextPowerOfTen2D(min, max);
                    //获取到最小值和最大值，用这2个值来可视化坐标轴
                    Point2D nstartx = {min.X(),0};
                    Point2D nendx = { max.X(),0 }; 
                    Point2D nstarty = {0, min.Y() };
                    Point2D nendy = {0, max.Y() };
                    float nmin = -0.9f;
                    float namx = 0.9f;
                    nstartx = Point2D::Normalize(nstartx, min, max, nmin,namx);
                    nendx = Point2D::Normalize(nendx, min, max, nmin, namx);
                    nstarty = Point2D::Normalize(nstarty, min, max, nmin, namx);
                    nendy = Point2D::Normalize(nendy, min, max, nmin, namx);
                    double xdistance = nendx.X() - nstartx.X();
                    double ydistance = nendy.Y() - nstarty.Y();
                    int drawsize = 12;
                    double xstep = xdistance / (double)drawsize;
                    double ystep = ydistance / (double)drawsize;
                    vboData.includes["AxisX"].clear();
                    vboData.includes["AxisY"].clear();
                    //绘制标注轴
                    for (int i = 0; i < drawsize + 1; ++i) {//2端物体 = 中间物体  + 1
                        Point2D stepstartX(nstartx.X() + i * xstep,0);
                        Point2D stependX(stepstartX.X(), ydistance / 80.0);
                        Point2D stepstartY(0, nstarty.Y() + i * ystep);
                        Point2D stependY(xdistance / 80.0, stepstartY.Y());
                        int index = vboData.data.size() > 0 ? vboData.data.size() - 1 : 0;
                        PushVector(vboData.data, { stepstartX,stependX,stepstartY,stependY });
                        vboData.includes["AxisX"].push_back(i * 8 + 0);
                        vboData.includes["AxisY"].push_back(i * 8 + 4);
                    }
                    PushVector(vboData.data, { nstartx,nendx,nstarty,nendy });
                    Model* model = new Model;
                    model->SetVShader(V_Line2DShader);
                    model->SetFShader(F_Line2DShader);
                    model->SetVBOS({ vboData });
                    model->Build(GL_SHOW_TYPE_LINE2D);
                    model->SetName("Line2DAxis");
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
            };
        }
    }
}