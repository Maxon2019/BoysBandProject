#include "bbproject.h"
#include "ui_bbproject.h"
#include <iostream>

QColor image_default_color{255, 255, 255};
QSize image_default_size{1200, 675};
const char * supported_formats{"Images (*.png *.xpm *.jpg *.bmp *.jpeg)"};

BBproject::BBproject(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BBproject)
{
    this->setWindowTitle("BBpaint");
    ui->setupUi(this);
    image = new QPixmap(image_default_size);
    image->fill(image_default_color);
    ui->image_label->setFixedSize(image->size());
    ui->image_label->setPixmap(*image);
    ui->mouse->setChecked(true);
    connect(ui->mouse, SIGNAL(clicked()), SLOT(clicked_tool()));
    connect(ui->shapes, SIGNAL(clicked()), SLOT(clicked_tool()));
    connect(ui->eraser, SIGNAL(clicked()), SLOT(clicked_tool()));
    connect(ui->brush, SIGNAL(clicked()), SLOT(clicked_tool()));
    connect(ui->fill, SIGNAL(clicked()), SLOT(clicked_tool()));
    connect(ui->effects, SIGNAL(clicked()), SLOT(clicked_tool()));
    connect(ui->text_red, SIGNAL(clicked()), SLOT(clicked_tool()));
    path = new QString;
}

BBproject::~BBproject()
{
    delete ui;
    image->~QPixmap();
    path->~QString();
}

void BBproject::uncheck_buttons(QLayout *container){
    QList <QToolButton*> list = container->parentWidget()->findChildren<QToolButton*>();
    for(auto unit : list) {unit->setChecked(false); unit->setCheckable(false);}
}

void BBproject::clicked_tool(){
    QToolButton *b = qobject_cast<QToolButton*>(sender());
    if(!b->isCheckable()){
        uncheck_buttons(ui->buttons);
        b->setCheckable(true);
        ui->tool_stack->setCurrentIndex(ui->buttons->indexOf(b));
        //write here to initialize tools
        switch (ui->buttons->indexOf(b)) {
        case 0:
            std::cout<<"switching to mouse tool\n";
            break;
        case 1:
            std::cout<<"switching to eraser tool\n";
            break;
        case 2:
            std::cout<<"switching to shapes tool\n";
            break;
        case 3:
            std::cout<<"switching to brush tool\n";
            break;
        case 4:
            std::cout<<"switching to fill tool\n";
            break;
        case 5:
            std::cout<<"switching to effects tool\n";
            break;
        case 6:
            std::cout<<"switching to text editor tool\n";
            break;
        }
    }
    b->setChecked(true);
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

