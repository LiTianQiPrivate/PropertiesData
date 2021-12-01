#include "CurvePlot.h"
#include <QVector>
#include "ModelRCSF.h"
CurvePlot::CurvePlot(QWidget *parent, QString className):QwtPlot(parent),PropertiesBase(className)
{

    setAutoFillBackground(true);
    //---------设置画布---------//
    backgroundCurve=new QwtPlotCanvas();
    backgroundCurve->setPalette(Qt::white);
    backgroundCurve->setBorderRadius(10);
    setCanvas( backgroundCurve );
    plotLayout()->setAlignCanvasToScales( true );

//    setAxisTitle(QwtPlot::yLeft, "Y" );
//    setAxisTitle(QwtPlot::xBottom, "X" );
    //----------------设置栅格线-------------------//
    grid = new QwtPlotGrid;
    grid->enableX( true );//设置网格线
    grid->enableY( true );
    grid->setMajorPen( Qt::black, 0, Qt::DotLine );
    grid->attach( this );

    zoomer = new QwtPlotZoomer( canvas() );
    zoomer->setMousePattern( QwtEventPattern::MouseSelect2,
        Qt::LeftButton ,Qt::ControlModifier );
    const QColor c( Qt::darkBlue );
    zoomer->setRubberBandPen(QColor(Qt::blue));
    //zoomer->setRubberBand(QwtPlotZoomer::CrossRubberBand);
    zoomer->setTrackerPen(QColor(Qt::black));
    panner = new QwtPlotPanner(canvas());
    panner->setMouseButton(Qt::RightButton);
    magnifier = new QwtPlotMagnifier( canvas() );
    magnifier->setAxisEnabled( QwtPlot::yRight, false );

    setAutoReplot( true );
}
CurvePlot::~CurvePlot()
{
    delete panner;
    delete magnifier;
    delete zoomer;
    delete grid;
    delete backgroundCurve;
}

void CurvePlot::resizeEvent(QResizeEvent *e)
{
    QwtPlot::resizeEvent(e);
    int thisW = this->width();
    int thisH = this->height();
}

void CurvePlot::setModelBases(std::vector<ModelBase *> modelObject)
{
    if(modelBases.size() >0)
    {
        modelBases.clear();
    }
    for(int i=0;i<modelObject.size();i++)
    {
        addModelBase(modelObject[i]);
    }
}

void CurvePlot::addModelBase(ModelBase *modelBase)
{
    modelBases.push_back(modelBase);

    for(int i = 0; i < modelBases.size(); i++)
    {
        ModelBase* object = modelBases[i];
        std::vector<Point2D> points = object->getPoint2D();
        for(int j = 0; j < points.size(); j++)
        {
            Point2D p = points[j];
            double x = p.x, y = p.y;
            if(xMin > x)
            {
                xMin = x;
            }
            if(xMax < x)
            {
                xMax = x;
            }
            if(yMin > y)
            {
                yMin = y;
            }
            if(yMax < y)
            {
                yMax = y;
            }
        }
    }
    setAxisScale(QwtPlot::yLeft,yMin,yMax);
    setAxisScale(QwtPlot::xBottom,xMin,xMax);
    QwtPlotCurve *curve = new QwtPlotCurve;
    curve->setTitle(modelBase->FileName());
    curve->setPen(modelBase->getColor());//设置曲线颜色 粗细
    curve->setRenderHint(QwtPlotItem::RenderAntialiased,true);//线条光滑化
    QVector<double> xVector, yVector;
    std::vector<Point2D> points = modelBase->getPoint2D();
    for(int j = 0; j < points.size(); j++)
    {
        Point2D p = points[j];
        xVector.push_back(p.x);
        yVector.push_back(p.y);
    }
    curve->setSamples(xVector, yVector);
    curve->attach( this );
    curve->setLegendAttribute(curve->LegendShowLine);//显示图例的标志，这里显示线的颜色。
    this->replot();
    setAutoReplot( true );//设置自动重画，相当于更新
    curves.push_back(curve);
}

void CurvePlot::setXTypeCurve(double x_Min, double x_Max, int x_Step)
{
    if(this->xMin > x_Min || x_Max > this->xMax || x_Step > fabs(this->xMax-this->xMin))
    {
        return ;
    }
    setAxisScale(QwtPlot::xBottom,x_Min,x_Max,x_Step);
}

void CurvePlot::setYTypeCurve(double y_Min, double y_Max, int y_Step)
{
    if(this->yMin > y_Min || y_Max > this->yMax || y_Step > fabs(this->yMax-this->yMin))
    {
        return ;
    }
    setAxisScale(QwtPlot::yLeft,y_Min,y_Max,y_Step);
}

void CurvePlot::setCurveFps(double fps)
{
    xMin = 10000000, xMax = -10000000;
    yMin = 10000000, yMax = -10000000;
    for(int i = 0; i < modelBases.size(); i++)
    {
        ModelBase* object = modelBases[i];
        if(object->getClassName() == "ModelRCSF")
        {
            ModelRCSF *rcsF = (ModelRCSF *)object;
            rcsF->setCurrentValue(fps);
            rcsF->setXStype(1);
            std::vector<Point2D> points = rcsF->getPoint2D();
            for(int j = 0; j < points.size(); j++)
            {
                Point2D p = points[j];
                double x = p.x, y = p.y;

                if(xMin > x)
                {
                    xMin = x;
                }
                if(xMax < x)
                {
                    xMax = x;
                }
                if(yMin > y)
                {
                    yMin = y;
                }
                if(yMax < y)
                {
                    yMax = y;
                }
            }
            QVector<double> xVector, yVector;
            for(int j = 0; j < points.size(); j++)
            {
                Point2D p = points[j];
                xVector.push_back(p.x);
                yVector.push_back(p.y);
            }

            curves[i]->setSamples(xVector,yVector);
        }
    }
    setAxisScale(QwtPlot::yLeft,yMin,yMax);
    setAxisScale(QwtPlot::xBottom,xMin,xMax);
    this->replot();
    setAutoReplot( true );//设置自动重画，相当于更新
}

void CurvePlot::setCurvePosition(double position)
{
    xMin = 10000000, xMax = -10000000;
    yMin = 10000000, yMax = -10000000;
    for(int i = 0; i < modelBases.size(); i++)
    {
        ModelBase* object = modelBases[i];
        if(object->getClassName() == "ModelRCSF")
        {
            ModelRCSF *rcsF = (ModelRCSF *)object;
            rcsF->setCurrentValue(position);
            rcsF->setXStype(0);
            std::vector<Point2D> points = rcsF->getPoint2D();
            for(int j = 0; j < points.size(); j++)
            {
                Point2D p = points[j];
                double x = p.x, y = p.y;

                if(xMin > x)
                {
                    xMin = x;
                }
                if(xMax < x)
                {
                    xMax = x;
                }
                if(yMin > y)
                {
                    yMin = y;
                }
                if(yMax < y)
                {
                    yMax = y;
                }
            }
            QVector<double> xVector, yVector;
            for(int j = 0; j < points.size(); j++)
            {
                Point2D p = points[j];
                xVector.push_back(p.x);
                yVector.push_back(p.y);
            }

            curves[i]->setSamples(xVector,yVector);
        }
    }
    setAxisScale(QwtPlot::yLeft,yMin,yMax);
    setAxisScale(QwtPlot::xBottom,xMin,xMax);
    this->replot();
    setAutoReplot( true );//设置自动重画，相当于更新
}



