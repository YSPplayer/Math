/*
    Created by YSP on 2025-05-25.
*/
#pragma once
#include <util.h>
#include "../Math/Geometry/line.h"
#include "./Geometry/model.h"
#include "../Math/Geometry/triangle.h"
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
                    vboData.attributeIndex = 2;
                    vboData.type = GL_EBO_TYPE_VECTOR;
                    vboData.usage = GL_DYNAMIC_DRAW;
                    Point2D min;
                    Point2D max;
                    geometry->GetPointMinMax(min, max);
                    Point2D::SetMinMaxNextPowerOfTen2D(min, max);
                    Point2D nstart = geometry->StartPoint();
                    Point2D nend = geometry->EndPoint();
                    float nmin = N_MIN;
                    float namx = N_MAX;
                    nstart = Point2D::Normalize(nstart, min, max,nmin,namx);
                    nend = Point2D::Normalize(nend, min, max, nmin, namx);
                    vboData.data.push_back(nstart.X());
                    vboData.data.push_back(nstart.Y());
                    vboData.data.push_back(nend.X());
                    vboData.data.push_back(nend.Y());
                    Model* model = new Model;
                    model->SetVShader(V_Line2DShader);
                    model->SetFShader(F_Line2DShader);
                    model->SetGeometry(geometry);
                    model->SetVBOS({ vboData });
                    model->Build(GL_SHOW_TYPE_LINE2D);
                    model->SetName("Line2D");
                    return model;
                };

                static Model* BuildModelTriangle2D(Triangle2D* geometry) {
                    VBOData vboData;
                    vboData.attributeIndex = 2;
                    vboData.type = GL_EBO_TYPE_VECTOR;
                    Point2D min;
                    Point2D max;
                    geometry->GetPointMinMax(min, max);
                    Point2D::SetMinMaxNextPowerOfTen2D(min, max);
                    float nmin = N_MIN;
                    float namx = N_MAX;
                    Point2D a = Point2D::Normalize(geometry->A(), min, max, nmin, namx);
                    Point2D b = Point2D::Normalize(geometry->B(), min, max, nmin, namx);
                    Point2D c = Point2D::Normalize(geometry->C(), min, max, nmin, namx);
                    PushVector(vboData.data, { a,b,b,c,c,a});
                    Model* model = new Model;
                    model->SetVShader(V_Line2DShader);
                    model->SetFShader(F_Line2DShader);
                    model->SetGeometry(geometry);
                    model->SetVBOS({ vboData });
                    model->Build(GL_SHOW_TYPE_TRIANGLE2D);
                    model->SetName("Triangle2D");
                    return model;
                }

                template <typename T>
                static Model* BuildModel2DAxis(T* geometry) {
                    VBOData vboData;
                    vboData.attributeIndex = 2;
                    vboData.type = GL_EBO_TYPE_VECTOR;  
                    Point2D min;
                    Point2D max;
                    geometry->GetPointMinMax(min, max);
                    Point2D::SetMinMaxNextPowerOfTen2D(min, max);
                    Point2D nstartx = {min.X(),0};
                    Point2D nendx = { max.X(),0 }; 
                    Point2D nstarty = {0, min.Y() };
                    Point2D nendy = {0, max.Y() };
                    float nmin = N_MIN;
                    float namx = N_MAX;
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
                    for (int i = 0; i < drawsize + 1; ++i) {
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