#include "bbproject.h"
#include "ui_bbproject.h"

QColor image_default_color{255, 255, 255};
QSize image_default_size{1200, 675};
const char * supported_formats{"Images (*.png *.xpm *.jpg *.bmp *.jpeg)"};

BBproject::BBproject(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BBproject)
{
    ui->setupUi(this);
    image = new QPixmap(image_default_size);
    image->fill(image_default_color);
    ui->image_label->setFixedSize(image->size());
    ui->image_label->setPixmap(*image);
    path = new QString;
}

BBproject::~BBproject()
{
    delete ui;
    image->~QPixmap();
    path->~QString();
}

void BBproject::on_open_triggered()
{
    *path = QFileDialog::getOpenFileName(this,
                                        tr("Open File"),
                                        "/home",
                                        tr(supported_formats));
    image->load(*path);
    ui->image_label->setFixedSize(image->size());
    ui->image_label->setPixmap(*image);
}

void BBproject::on_save_triggered()
{
    image->save(*path);
}


void BBproject::on_save_as_triggered()
{
    *path = QFileDialog::getSaveFileName(this,
                                         tr("Save File"),
                                         *path,
                                         tr(supported_formats));
    image->save(*path);
}


void BBproject::on_close_triggered()
{
    QPixmap scaled = image->scaled(image_default_size);
    image->~QPixmap();
    image = new QPixmap{scaled};
    image->fill(image_default_color);
    ui->image_label->setFixedSize(image->size());
    ui->image_label->setPixmap(*image);
    path->clear();
}

