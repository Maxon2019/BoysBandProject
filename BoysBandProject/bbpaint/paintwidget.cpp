#include "paintwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEngine>
#include <math.h>
#include <iostream>

const int max_width = 1280;
const int max_height = 720;

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    isDrawing=false;
    filling = false;
    circle_style = false;
    changed = false;
    pen_type = 0;

    myPen=QPen(Qt::black,1,Qt::SolidLine);
    myBrush=QBrush(Qt::white, Qt::SolidPattern);
    BrushRadius=20;

    image=QImage(max_width ,max_height ,QImage::Format_ARGB32_Premultiplied) ;
    image.fill(qRgb(255, 255, 255));
    reset();
}

PaintWidget::~PaintWidget(){

}

void PaintWidget::setImage(QImage newImage)
{
    image=newImage;
    reset();
    update();
}

QImage PaintWidget::getImage()
{
    return original_image;
}

void PaintWidget::setActiveTool(int activeTool)
{
    ActiveTool=activeTool;
    update();
}

void PaintWidget::clearAll()
{
    image=QImage(1600 ,900 ,QImage::Format_ARGB32_Premultiplied) ;
    image.fill(qRgb(255, 255, 255));
    reset();
    update();
}

void PaintWidget::setBrush(QBrush changeBrush)
{
    myBrush=changeBrush;
    update();
}

void PaintWidget::setPen(QPen changePen)
{
    myPen=changePen;
    update();
}

void PaintWidget::setPenWidth(int width)
{
    myPen.setWidth(width);
    BrushRadius=width;
    update();
}

void PaintWidget::setColor(QColor color)
{
    myPen.setColor(color);
    myBrush.setColor(color);
    update();
}

void PaintWidget::setPenStyle(Qt::PenStyle style){
    myPen.setStyle(style);
}

void PaintWidget::setBrushStyle(Qt::BrushStyle style){
    myBrush.setStyle(style);
}

void PaintWidget::rotate(int angle){
    changed = true;
    QTransform transform;
    transform.rotate(angle);
    QImage rotatedImage = original_image.transformed(transform);
    original_image = rotatedImage;
    original_size = original_image.size();
    image = original_image.scaled(original_size*zoom_k);
    update();
}

void PaintWidget::mirror(bool horizontal){
    changed = true;
    original_image.mirror(horizontal, !horizontal);
    image = original_image.scaled(original_size*zoom_k);
    update();
}

void PaintWidget::reset(){
    zoom_k = 1;
    original_size = image.size();
    original_image = image;
}

void PaintWidget::performZoom(qreal k){
    zoom_k *= k;
    zoom_k = zoom_k>20 ? 20 : zoom_k;
    zoom_k = zoom_k<0.1 ? 0.1 : zoom_k;
    image = original_image.scaled(original_size*zoom_k);
    update();
}

void PaintWidget::wheelEvent(QWheelEvent *event){
    qreal angle = event->angleDelta().y()/120;
    performZoom(std::pow(1.2, angle));
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton )
    {
        MP1=event->pos();
        isDrawing=true;
        //MP2=MP1;
        if (ActiveTool==201)
        {
            QColor oldClr, newClr;
            oldClr=image.pixel(MP1);
            newClr=myBrush.color();
            //Fill(oldClr, newClr, MP2);
            Fill2(oldClr.rgb(), newClr.rgb(), MP1.x(), MP1.y());
            update();
        }
    if(ActiveTool==101 || ActiveTool==102 || ActiveTool==103){
        DrawFigure(event->pos(),event->pos());
        update();
    }
    }
event->accept();
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event){
    if ( event->buttons() == Qt::LeftButton )
    {
        if (isDrawing==true && (ActiveTool==101 || ActiveTool==102 || ActiveTool==103))
            DrawFigure(event->pos(),event->pos());
    }
    update();
    event->accept();
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    MP2=event->pos();
    if (event->button()==Qt::LeftButton)
    {
    if (isDrawing)
    {
        switch (ActiveTool)
        {
        case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
        {
            DrawFigure(MP1,MP2);
            break;
        }
        }

    }
    }
    isDrawing=false;
    update();
    event->accept();
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    QPainter pnt(this);
    QRect dirtyRect = event->rect();
    pnt.drawImage(dirtyRect, image, dirtyRect);
}

void PaintWidget::DrawFigure(QPoint a, QPoint b)
{
    changed = true;
    QPainter pnt(&original_image);
    QPen mod_pen = myPen;
    a = QPoint(a.x()/zoom_k, a.y()/zoom_k);
    b = QPoint(b.x()/zoom_k, b.y()/zoom_k);
    mod_pen.setWidthF(myPen.width());
    pnt.setPen(mod_pen);
    if (filling) pnt.setBrush(myBrush);
    switch (ActiveTool)
    {
    case 1: // line
    {
        pnt.drawLine(a,b);
        break;
    }
    case 2: // rect
    {
        pnt.drawRect(QRect(a, b));
        break;
    }
    case 3: // arrow
    {
        QLineF main{b, a}, left{b, a}, right{b, a};
        qreal angle = main.angle();
        left.setAngle(angle+30);
        left.setLength(10);
        right.setAngle(angle-30);
        right.setLength(10);
        pnt.drawLine(main);
        pnt.drawLine(left);
        pnt.drawLine(right);
        break;
    }
    case 4: // ellipse
    {
        pnt.drawEllipse(QRect(a, b));
        break;
    }
    case 5: // round rect
        pnt.drawRoundedRect(QRect(a, b), 20, 20);
        break;
    case 6: // mars
    {
        QBrush bb(Qt::NoBrush);
        pnt.setBrush(bb);
        qreal x = abs(b.x() - a.x()), y = abs(b.y() - a.y()), r = sqrt(x*x + y*y);
        pnt.drawEllipse(QPointF(a), r, r);
        QLineF main, left, right;
        left.setP1(QPointF(a.x() + r, a.y() - r));
        left.setAngle(180);
        left.setLength(r / 4);
        right.setP1(QPointF(a.x() + r, a.y() - r));
        right.setAngle(-90);
        right.setLength(r / 4);
        main.setP1(QPointF(a.x() + r, a.y() - r));
        main.setAngle(-135);
        main.setLength(r*sqrt(2) - r);
        pnt.drawLine(left);
        pnt.drawLine(right);
        pnt.drawLine(main);
        break;
    }
    case 7: // triangle
    {
        QPoint A{a.x(), b.y()}, B{(a.x()+b.x())/2, a.y()}, C{b};
        QPolygon polygon;
        polygon << A << B << C;
        pnt.drawPolygon(polygon);
        break;
    }
    case 8: // star
    {
        QPoint A{(a.x()+b.x())/2, a.y()}, B{a.x()-24*(a.x()-b.x())/25, a.y()-7*(a.y()-b.y())/20}, C{a.x()-4*(a.x()-b.x())/5, a.y()-9*(a.y()-b.y())/10},
            D{a.x()-(a.x()-b.x())/5, a.y()-9*(a.y()-b.y())/10}, E{a.x()-(a.x()-b.x())/25, a.y()-7*(a.y()-b.y())/20},
            F{a.x()-13*(a.x()-b.x())/20, a.y()-7*(a.y()-b.y())/20}, G{a.x()-7*(a.x()-b.x())/10, a.y()-11*(a.y()-b.y())/20}, H{(a.x()+b.x())/2, a.y()-7*(a.y()-b.y())/10},
            I{a.x()-3*(a.x()-b.x())/10, a.y()-11*(a.y()-b.y())/20}, J{a.x()-7*(a.x()-b.x())/20, a.y()-7*(a.y()-b.y())/20};
        QPolygon polygon;
        polygon << A << F << B << G << C << H << D << I << E << J;
        pnt.drawPolygon(polygon);
        break;
    }
    case 9: // david star
    {
        QPoint A{(a.x()+b.x())/2, a.y()}, B{a.x()-19*(a.x()-b.x())/20, a.y()-3*(a.y()-b.y())/4}, C{a.x()-(a.x()-b.x())/20, a.y()-3*(a.y()-b.y())/4},
            D{(a.x()+b.x())/2, b.y()}, E{b.x()+19*(a.x()-b.x())/20, b.y()+3*(a.y()-b.y())/4}, F{b.x()+(a.x()-b.x())/20, b.y()+3*(a.y()-b.y())/4};
        QPolygon polygon1, polygon2;
        polygon1 << A << B << C;
        polygon2 << D << E << F;
        pnt.drawPolygon(polygon1);
        pnt.drawPolygon(polygon2);
        break;
    }

    case 101:
    {
        pnt.setCompositionMode(QPainter::CompositionMode_Clear);
        QPen whitePen;
        whitePen.setWidth(myPen.widthF());
        pnt.setPen(whitePen);
        if(circle_style){
            QBrush bb(Qt::SolidPattern);
            pnt.setBrush(bb);
            pnt.drawEllipse(b,(int)myPen.widthF(),(int)myPen.widthF());
        }
        else pnt.drawLine(a,b);
        break;
    }
    case 102: // spray
    {
        QPen sprayPen;
        sprayPen.setColor(pnt.pen().color());
        sprayPen.setWidth(1);
        pnt.setPen(sprayPen);
        for(int i = 1; i<=BrushRadius*BrushRadius;i++)
        {
            int randomx, randomy;
            randomx=rand() % (BrushRadius) -  BrushRadius/2;
            randomy=rand() % (BrushRadius) - BrushRadius/2;
            if (randomx*randomx+randomy*randomy<=BrushRadius*BrushRadius/4)
            {
                {
                    pnt.drawPoint(b.x()+randomx,b.y()+randomy);
                    pnt.drawPoint(b.x()+randomx,b.y()-randomy);
                }
            }
        break;
        }
    }
    case 103:{
        switch(pen_type){
        case 0:{
            pnt.drawLine(a,b);
            break;
        }
        case 1:{
            QColor brcolor;
            brcolor = myPen.color();
            QBrush bb(brcolor, Qt::SolidPattern);
            pnt.setBrush(bb);
            pnt.drawEllipse(b,(int)(myPen.widthF()),(int)(myPen.widthF()));
            break;
        }
        case 2:{
            QPen tpen(Qt::NoPen);
            tpen.setWidth(mod_pen.widthF());
            pnt.setPen(tpen);
            pnt.setBrush(myBrush);
            pnt.drawEllipse(b,(int)(myPen.widthF()),(int)(myPen.widthF()));
            break;
        }
        case 3:{
            QColor brcolor(myPen.color().red(), myPen.color().green(), myPen.color().blue(), 15);
            QBrush bb(brcolor, Qt::SolidPattern);
            QPen tpen(Qt::NoPen);
            tpen.setWidth(mod_pen.widthF());
            pnt.setPen(tpen);
            pnt.setBrush(bb);
            pnt.drawEllipse(b,(int)(myPen.widthF()),(int)(myPen.widthF()));
            break;
        }
        }
    }
    case 201: // fill
    {
        break;
    }
    }

    int rad = (20 / 2) + 2;
    performZoom(1);
    update(QRect(a, b).normalized().adjusted(-rad, -rad, +rad, +rad));
}

void PaintWidget::Fill(QColor oldClr, QColor newClr, QPoint p)
{
    changed = true;
    QPainter pnt(&image);
    pnt.setPen(QPen(newClr));

    if (image.pixel(p) == oldClr.rgb() &&
          image.pixel(p) != newClr.rgb() )
       {

          pnt.drawPoint(p);

          Fill(oldClr,newClr,QPoint(p.x()+1,p.y()));


          Fill(oldClr,newClr,QPoint(p.x(),p.y()+1));


          Fill(oldClr,newClr,QPoint(p.x()-1,p.y()));


          Fill(oldClr,newClr,QPoint(p.x(),p.y()-1));

       }


    update();

}


void PaintWidget::Fill2(QRgb oldColor, QRgb newColor, int x, int y)
{
    changed = true;
    if (oldColor == newColor) return;

            QStack<QPoint> stk;
            QPoint pt;

            int y1;
            bool spanLeft, spanRight;

            stk.push(QPoint(x/zoom_k, y/zoom_k));

            while (!stk.empty()) {
                pt = stk.pop();
                x = pt.x();
                y = pt.y();

                y1 = y;
                while (y1 >= 0 && original_image.pixel(x, y1) == oldColor) y1--;
                y1++;

                spanLeft = spanRight = false;
                while (y1 < original_image.height() && original_image.pixel(x, y1) == oldColor) {
                    original_image.setPixel(x, y1, newColor);
                    if (!spanLeft && x > 0 && original_image.pixel(x-1, y1) == oldColor) {
                        stk.push(QPoint(x-1, y1));
                        spanLeft = true;
                    } else if(spanLeft && x > 0 && original_image.pixel(x-1, y1) != oldColor) {
                        spanLeft = false;
                    }
                    if (!spanRight && x < (original_image.width() - 1) && original_image.pixel(x+1, y1) == oldColor) {
                        stk.push(QPoint(x+1, y1));
                        spanRight = true;
                    } else if(spanRight && (x < original_image.width() - 1) && original_image.pixel(x+1, y1) != oldColor) {
                        spanRight = false;
                    }
                    y1++;
                }
            }
            image = original_image.scaled(original_size*zoom_k);
}

