#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QPoint>
#include <QPainter>
#include <QWidget>
#include <QMouseEvent>
#include <QStack>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:


    explicit PaintWidget(QWidget *parent = 0);
    ~PaintWidget();

    int ActiveTool;
    int BrushSize;
    int PenSize;
    bool filling, circle_style, changed;
    int pen_type;

    void setImage(QImage newImage);
    QImage getImage();

public slots:
    void setActiveTool(int activeTool);
    void clearAll();

    void setBrush(QBrush changeBrush);
    void setPen(QPen changePen);
    void setPenWidth(int width);
    void setColor(QColor color);
    void setPenStyle(Qt::PenStyle style);
    void setBrushStyle(Qt::BrushStyle style);
    void rotate(int angle);
    void mirror(bool horizontal);
    void reset();


protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent  (QMouseEvent *event);
    void mouseMoveEvent   (QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void performZoom(qreal k);
    void DrawFigure(QPoint a, QPoint b);
    void Fill(QColor oldClr, QColor newClr, QPoint p);
    void Fill2(QRgb oldColor, QRgb newColor, int x, int y);



private:
  QImage image;
  bool isDrawing;
  QPoint MP1,MP2;
  QPen myPen;
  QBrush myBrush;

  int BrushRadius;
  qreal zoom_k;
  QSize original_size;
  QImage original_image;

};

#endif // PAINTER_H
