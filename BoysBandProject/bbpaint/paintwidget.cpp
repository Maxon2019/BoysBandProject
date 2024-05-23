#include "paintwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEngine>

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    isDrawing=false;
    //BrushShape=bshEllipse;

    myPen=QPen(Qt::black,1,Qt::SolidLine);
    myBrush=QBrush(Qt::white, Qt::SolidPattern);
    BrushRadius=20;

    image=QImage(1500,1500,QImage::Format_ARGB32_Premultiplied) ;
    image.fill(qRgb(255, 255, 255));
}

PaintWidget::~PaintWidget()
{

}

void PaintWidget::setImage(QImage newImage)
{
    image=newImage;
    update();
}

QImage PaintWidget::getImage()
{
    return image;
}

void PaintWidget::setActiveTool(int activeTool)
{
    ActiveTool=activeTool;
    update();
}

void PaintWidget::clearAll()
{
    image.fill(qRgb(255, 255, 255));
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
    BrushRadius=width*3;
    update();
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton )
    {

        MP1=event->pos();
        isDrawing=true;
        //MP2=MP1;
        if (ActiveTool==7)
        {
            QColor oldClr, newClr;
            oldClr=image.pixel(MP1);
            newClr=myBrush.color();
            //Fill(oldClr, newClr, MP2);
            Fill2(oldClr.rgb(), newClr.rgb(), MP1.x(), MP1.y());
            update();

        }
    }
event->accept();
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    qreal X,Y;
    X=event->pos().x();
    Y=event->pos().y();

    if ( event->buttons() == Qt::LeftButton )
    {
    if (isDrawing==true)
    {
        switch (ActiveTool)
        {
        case 4:
        {
            DrawFigure(event->pos(),event->pos());
            break;
        }
        case 5:
        {
            DrawFigure(event->pos(),event->pos());
            break;
        }
        case 8:
        {
            DrawFigure(event->pos(),event->pos());
            break;
        }
        }
    }

    }
    update();
    event->accept();
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    MP2=event->pos();
    int i;
    if (event->button()==Qt::LeftButton)
    {
    if (isDrawing)
    {
        switch (ActiveTool)
        {
        case 1: case 2: case 3: case 6:
        {
            DrawFigure(MP1,MP2);
            break;
        }
       /* case 7: // заливка
        {
            //QPainter pnt(&image);
            QColor oldClr, newClr;
            oldClr=image.pixel(MP2);
            newClr=myBrush.color();
            //Fill(oldClr, newClr, MP2);
            Fill2(oldClr, newClr, MP2);
            break;
        } */
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
    QPainter pnt(&image);
    pnt.setPen(myPen);
    pnt.setBrush(myBrush);
    switch (ActiveTool)
    {
    case 1:
    {
        pnt.drawLine(a,b);
        break;
    }
        case 4:
    {
        QColor brClr;
        brClr=myPen.color();
        QBrush bb(brClr, Qt::SolidPattern);
        pnt.setBrush(bb);
        pnt.drawEllipse(b,myPen.widthF(),myPen.widthF());
        //pnt.drawLine(a,b);
        break;
    }
    case 2:
    {
        pnt.drawEllipse(QRectF(a.x(),a.y(),b.x(),b.y()));
        break;
    }
    case 3:
    {
        pnt.drawRoundedRect(QRectF(a.x(),a.y(),b.x(),b.y()),20,20);
        break;
    }
    case 5:
    {
        QPen whitePen(Qt::white);
        whitePen.setWidth(myPen.widthF());
        pnt.setPen(whitePen);;
        pnt.drawLine(a,b);
        break;
    }
    case 6:
    {
        pnt.drawRect(QRectF(a.x(),a.y(),b.x(),b.y()));
        break;
    }
    case 7: // fill
    {
        break;
    }
    case 8: // spray
    {
        bool sign=false;
        QPen sprayPen;
        sprayPen.setColor(pnt.pen().color());
        sprayPen.setWidth(1);
        pnt.setPen(sprayPen);

              for(int i=1; i<=BrushRadius;i++)
              {
                  int randomx, randomy;
                  randomx=rand() % BrushRadius*2 ;
                  randomy=rand() % BrushRadius*2 ;
if (randomx*randomx+randomy*randomy<=BrushRadius*BrushRadius*4)
{
                  if (sign==false)
                  {
                      pnt.drawPoint(b.x()+randomx,b.y()+randomy);
                      pnt.drawPoint(b.x()+randomx,b.y()-randomy);
                      sign=true;
                  }
                  else
                  {
                      pnt.drawPoint(b.x()-randomx,b.y()-randomy);
                      pnt.drawPoint(b.x()-randomx,b.y()+randomy);
                      sign=false;
                  }
}

              }
        break;
    }
    }

    int rad = (20 / 2) + 2;
    update(QRect(a, b).normalized().adjusted(-rad, -rad, +rad, +rad));
}

void PaintWidget::Fill(QColor oldClr, QColor newClr, QPoint p)
{
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
    if (oldColor == newColor) return;

            QStack<QPoint> stk;
            QPoint pt;

            int y1;
            bool spanLeft, spanRight;

            stk.push(QPoint(x, y));

            while (!stk.empty()) {
                pt = stk.pop();
                x = pt.x();
                y = pt.y();

                y1 = y;
                while (y1 >= 0 && image.pixel(x, y1) == oldColor) y1--;
                y1++;

                spanLeft = spanRight = false;
                while (y1 < image.height() && image.pixel(x, y1) == oldColor) {
                    image.setPixel(x, y1, newColor);
                    if (!spanLeft && x > 0 && image.pixel(x-1, y1) == oldColor) {
                        stk.push(QPoint(x-1, y1));
                        spanLeft = true;
                    } else if(spanLeft && x > 0 && image.pixel(x-1, y1) != oldColor) {
                        spanLeft = false;
                    }
                    if (!spanRight && x < (image.width() - 1) && image.pixel(x+1, y1) == oldColor) {
                        stk.push(QPoint(x+1, y1));
                        spanRight = true;
                    } else if(spanRight && (x < image.width() - 1) && image.pixel(x+1, y1) != oldColor) {
                        spanRight = false;
                    }
                    y1++;
                }
            }
}

