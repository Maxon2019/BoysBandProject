#include "bbproject.h"
#include "ui_bbproject.h"

BBproject::BBproject(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BBproject)
{
    ui->setupUi(this);
}

BBproject::~BBproject()
{
    delete ui;
}
