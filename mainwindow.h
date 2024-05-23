#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <paintwidget.h>

#include <QtGui>
#include <QMainWindow>
#include <QMouseEvent>
#include <QMessageBox>
#include <QSpinBox>
#include <QLabel>
#include <QColorDialog>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void createActions();
    void createMenus();
    void drawBtnIcons();
    QPixmap pixForBrush(QBrush brush);
    QPixmap pixForPen(QPen pen);
    QPixmap pixForColor(QColor color);
    QToolBar* myToolBar();

private slots:

   /* void setBrushColor(QColor color);
    void setPenColor(QColor color);
    void setBrushSize(int size);
    void setPenWidth(int width); */

    void openFile();
    void saveFile();
    void closeEvent(QCloseEvent *event);
    void aboutEvent();

    void changeBrushColor();
    void changePenColor();
   // void changeBrushSize(int value);
    void changePenWidth(int value);


    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_6_clicked();

signals:
    void getActiveTool(int a);
    void changePen(QPen newPen);
    void changeBrush(QBrush newBrush);

private:
    Ui::MainWindow *ui;
    PaintWidget *paintwid;

    QMenu *fileMenu;
    QMenu *correctMenu;
    QMenu *infoMenu;

    QAction *openAct;
    QAction *saveAct;
    QAction *closeAct;
    QAction *clearAct;
    QAction *aboutAct;

    QSpinBox* penWidthValue;

    QPushButton *colorBtn1;
    QPushButton *colorBtn2;

    QPen pen;
    QBrush brush;

};

#endif // MAINWINDOW_H
