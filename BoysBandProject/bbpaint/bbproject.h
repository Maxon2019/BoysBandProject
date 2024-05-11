#ifndef BBPROJECT_H
#define BBPROJECT_H

#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QPixmap>
#include <QLabel>
#include <QAbstractButton>

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
    void connect_buttons(QLayout *container, const char* slot);

private slots:
    void on_open_triggered();

    void on_save_triggered();

    void on_save_as_triggered();

    void on_close_triggered();

    void clicked_tool();

    void clicked_eraser_mode();
    void clicked_shape_mode();
    void clicked_brush_mode();
    void clicked_effect_mode();

    void eraser_edited();
    void brush_edited();

    void fill_switched();


private:
    Ui::BBproject *ui;
    QPixmap *image;
    QString *path;
    int er_size, br_thickness;
    bool fill_shape;
};
#endif // BBPROJECT_H
