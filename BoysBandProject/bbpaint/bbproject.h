#ifndef BBPROJECT_H
#define BBPROJECT_H

#include "QtGui/qpen.h"
#include "QtWidgets/qboxlayout.h"
#include "paintwidget.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QPixmap>
#include <QLabel>
#include <QAbstractButton>
#include <QMessageBox>
#include <QStyleFactory>

QT_BEGIN_NAMESPACE
namespace Ui {
class BBproject;
}
QT_END_NAMESPACE

class BBproject : public QMainWindow
{
    Q_OBJECT

public:
    BBproject(QWidget *parent = nullptr);
    ~BBproject();
    void uncheck_buttons(QLayout *container);
    int get_checked_button(QLayout *container);
    void connect_buttons(QLayout *container, const char* slot);
    void addListItem(QHBoxLayout** list, int &count);
    void connect_colors();
    void set_color(QColor color, int index);
    void drawBtnIcons(QColor color = Qt::black);
    QPixmap pixForBrush(QColor color, QBrush brush);
    QPixmap pixForPen(QColor color, QPen pen);
    void uncheck_buttons_l(QLayout *container);
    void connect_buttons_l(QLayout *container, const char* slot);
    int get_checked_button_l(QLayout *container);
    void connect_all();

private slots:
    void on_open_triggered();

    void on_save_triggered();

    void on_save_as_triggered();

    void on_close_triggered();

    void clicked_tool();

    void clicked_eraser_mode();
    void clicked_shape_mode();
    void clicked_brush_mode();
    void clicked_fill_effect_mode();
    void clicked_outline_effect_mode();

    void eraser_edited();
    void brush_edited();
    void shape_edited();

    void fill_switched();

    void color_switched();

    void color_line_edit();

    void rotate_clockwise_clicked();
    void rotate_counter_clockwise_clicked();
    void mirror_hor_clicked();
    void mirror_ver_clicked();

    void on_light_triggered();

    void on_dark_triggered();

    void closeEvent(QCloseEvent *);

private:
    Ui::BBproject *ui;
    QPixmap *image;
    QString *path;
    int er_size, br_thickness, sh_thickness;
    bool fill_shape;
    PaintWidget *paintwid;
};
#endif // BBPROJECT_H
