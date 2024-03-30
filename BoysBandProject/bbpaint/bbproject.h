#ifndef BBPROJECT_H
#define BBPROJECT_H

#include <QMainWindow>

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

private:
    Ui::BBproject *ui;
};
#endif // BBPROJECT_H
