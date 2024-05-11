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

private slots:
    void on_open_triggered();

    void on_save_triggered();

    void on_save_as_triggered();

    void on_close_triggered();

    void clicked_tool();

private:
    Ui::BBproject *ui;
    QPixmap *image;
    QString *path;
};
#endif // BBPROJECT_H
