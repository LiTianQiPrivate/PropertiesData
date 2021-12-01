#ifndef CURVEPLOT_H
#define CURVEPLOT_H
#include "qwt_plot.h"
#include "qwt_plot_canvas.h"
#include "qwt_plot_grid.h"
#include "qwt_plot_curve.h"
#include "qwt_plot_zoomer.h"
#include "qwt_plot_magnifier.h"
#include "qwt_plot_panner.h"
#include "qwt_plot_layout.h"
#include "ModelBase.h"
#include "PropertiesBase.h"

class CurvePlot : public QwtPlot,public PropertiesBase
{
    Q_OBJECT
public:
    CurvePlot(QWidget *parent = nullptr, QString className = "CurvePlot");
    ~CurvePlot();
    void resizeEvent(QResizeEvent *e);
    void setModelBases(std::vector<ModelBase *> modelObject);
    void addModelBase(ModelBase *modelBase);
    void setXTypeCurve(double x_Min, double x_Max, int x_Step);
    void setYTypeCurve(double y_Min, double y_Max, int y_Step);
    void setCurveFps(double fps);
    void setCurvePosition(double position);
    void setXName(QString str)
    {
        setAxisTitle(QwtPlot::xBottom,str);
    }
    void setYName(QString str)
    {
        setAxisTitle(QwtPlot::yLeft,str);
    }
private:
    QwtPlotCanvas* backgroundCurve = nullptr; // 画布
    QwtPlotGrid *grid = nullptr; // 网格线
    QwtPlotZoomer* zoomer = nullptr;
    QwtPlotMagnifier *magnifier = nullptr;
    QwtPlotPanner *panner = nullptr;
    std::vector<QwtPlotCurve *> curves;
    std::vector<ModelBase *> modelBases;
    double xMin = 10000000, xMax = -10000000;
    double yMin = 10000000, yMax = -10000000;
};

#endif // CURVEPLOT_H
