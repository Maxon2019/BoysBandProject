#include "bbproject.h"
#include "QtColorWidgets/color_wheel.hpp"
#include "ui_bbproject.h"
#include <iostream>

QColor image_default_color{255, 255, 255};
QSize image_default_size{1200, 675};
const int default_brush_thickness = 20;
const int default_eraser_size = 20;
const char * supported_formats{"Images (*.png *.xpm *.jpg *.bmp *.jpeg)"};

BBproject::BBproject(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BBproject)
{
    this->setWindowTitle("BBpaint");
    ui->setupUi(this);
    er_size = default_eraser_size;
    br_thickness = default_brush_thickness;
    fill_shape = false;
    image = new QPixmap(image_default_size);
    image->fill(image_default_color);
    ui->image_label->setFixedSize(image->size());
    ui->image_label->setPixmap(*image);
    ui->eraser_size->setText(QString::number(er_size));
    ui->brush_thickness->setText(QString::number(br_thickness));
    connect(ui->shape_fill, SIGNAL(stateChanged(int)), SLOT(fill_switched()));
    connect(ui->eraser_size, SIGNAL(editingFinished()), SLOT(eraser_edited()));
    connect(ui->brush_thickness, SIGNAL(editingFinished()), SLOT(brush_edited()));
    connect_buttons(ui->buttons, SLOT(clicked_tool()));
    connect_buttons(ui->eraser_modes, SLOT(clicked_eraser_mode()));
    connect_buttons(ui->shape_modes, SLOT(clicked_shape_mode()));
    connect_buttons(ui->brush_modes, SLOT(clicked_brush_mode()));
    connect_buttons(ui->effect_modes, SLOT(clicked_effect_mode()));
    path = new QString;
    connect_colors();
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

void BBproject::connect_buttons(QLayout *container, const char* slot){
    QList <QToolButton*> list = container->parentWidget()->findChildren<QToolButton*>();
    for(auto unit : list) connect(unit, SIGNAL(clicked()), slot);
}

void BBproject::connect_colors(){
    color_widgets::ColorWheel* cw1 = new color_widgets::ColorWheel(ui->brush_page);
    ui->brush_color_setter->insertWidget(0, cw1);
    connect(cw1, SIGNAL(colorSelected(QColor)), SLOT(color_switched()));

    color_widgets::ColorWheel* cw2 = new color_widgets::ColorWheel(ui->shapes_page);
    ui->shape_color_setter->insertWidget(0, cw2);
    connect(cw2, SIGNAL(colorSelected(QColor)), SLOT(color_switched()));

    color_widgets::ColorWheel* cw3 = new color_widgets::ColorWheel(ui->fill_page);
    ui->fill_color_setter->insertWidget(0, cw3);
    connect(cw3, SIGNAL(colorSelected(QColor)), SLOT(color_switched()));

    connect(ui->red_line_edit_1, SIGNAL(editingFinished()), SLOT(color_line_edit()));
    connect(ui->green_line_edit_1, SIGNAL(editingFinished()), SLOT(color_line_edit()));
    connect(ui->blue_line_edit_1, SIGNAL(editingFinished()), SLOT(color_line_edit()));

    connect(ui->red_line_edit_2, SIGNAL(editingFinished()), SLOT(color_line_edit()));
    connect(ui->green_line_edit_2, SIGNAL(editingFinished()), SLOT(color_line_edit()));
    connect(ui->blue_line_edit_2, SIGNAL(editingFinished()), SLOT(color_line_edit()));

    connect(ui->red_line_edit_3, SIGNAL(editingFinished()), SLOT(color_line_edit()));
    connect(ui->green_line_edit_3, SIGNAL(editingFinished()), SLOT(color_line_edit()));
    connect(ui->blue_line_edit_3, SIGNAL(editingFinished()), SLOT(color_line_edit()));
}

void BBproject::set_color(QColor color, int index){
    //here you do stuff with setting color, index is index of qStackedWidget page, aka tool id
    switch(index){
    case 0:

        break;
    default:

        break;
    }
}

void BBproject::color_switched(){
    color_widgets::ColorWheel* cw = qobject_cast<color_widgets::ColorWheel*>(sender());
    QList<QLineEdit*> list = cw->parentWidget()->findChildren<QLineEdit*>();
    int dif = 0;
    if(list.size()>3) dif = list.size()-3;
    list[0+dif]->setText(QString::number(cw->color().red()));
    list[1+dif]->setText(QString::number(cw->color().green()));
    list[2+dif]->setText(QString::number(cw->color().blue()));
    set_color(cw->color(), ui->tool_stack->currentIndex());
}

void BBproject::color_line_edit(){
    QLineEdit* line = qobject_cast<QLineEdit*>(sender());
    bool ok;
    int res = line->text().toInt(&ok);
    color_widgets::ColorWheel* cw = line->parentWidget()->findChild<color_widgets::ColorWheel*>();
    int r = cw->color().red(), g = cw->color().green(), b = cw->color().blue();
    QList<QLineEdit*> all_lines = line->parentWidget()->findChildren<QLineEdit*>();
    int id = all_lines.indexOf(line);
    if(all_lines.size()>3) id-=all_lines.size()-3;
    if(ok && res<=255 && res>=0) {
        switch(id){
        case 0:
            r = res;
            break;
        case 1:
            g = res;
            break;
        case 2:
            b = res;
            break;
        }
        cw->setColor(QColor(r,g,b));
        set_color(QColor(r,g,b), ui->tool_stack->currentIndex());
    }
    else {
        switch (id) {
        case 0:
            res = r;
            break;
        case 1:
            res = g;
            break;
        case 2:
            res = b;
            break;
        }
        line->setText(QString::number(res));
    }
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

void BBproject::clicked_eraser_mode(){
    QToolButton *b = qobject_cast<QToolButton*>(sender());
    if(!b->isCheckable()){
        uncheck_buttons(ui->eraser_modes);
        b->setCheckable(true);
        //write here to switch eraser shape
        switch (ui->eraser_modes->indexOf(b)) {
        case 0:
            std::cout<<"switching to square eraser mode\n";
            break;
        case 1:
            std::cout<<"switching to circle eraser mode\n";
            break;
        }
    }
    b->setChecked(true);
}

void BBproject::clicked_shape_mode(){
    QToolButton *b = qobject_cast<QToolButton*>(sender());
    if(!b->isCheckable()){
        uncheck_buttons(ui->shape_modes);
        b->setCheckable(true);
        //write here to switch shape
        switch (ui->shape_modes->indexOf(b)) {
        default:
            std::cout<<"shape mode selected\n";
            break;
        }
    }
    b->setChecked(true);
}

void BBproject::clicked_brush_mode(){
    QToolButton *b = qobject_cast<QToolButton*>(sender());
    if(!b->isCheckable()){
        uncheck_buttons(ui->brush_modes);
        b->setCheckable(true);
        //write here to switch brush
        switch (ui->brush_modes->indexOf(b)) {
        default:
            std::cout<<"brush mode selected\n";
            break;
        }
    }
    b->setChecked(true);
}

void BBproject::clicked_effect_mode(){
    QToolButton *b = qobject_cast<QToolButton*>(sender());
    if(!b->isCheckable()){
        uncheck_buttons(ui->effect_modes);
        b->setCheckable(true);
        //write here to switch effect
        switch (ui->effect_modes->indexOf(b)) {
        default:
            std::cout<<"effect mode selected\n";
            break;
        }
    }
    b->setChecked(true);
}

void BBproject::eraser_edited(){
    QLineEdit* line = qobject_cast<QLineEdit*>(sender());
    bool ok;
    int res = line->text().toInt(&ok);
    if(ok) er_size = res;
    else line->setText(QString::number(er_size));
    std::cout<<"new size is "<<er_size<<"\n";
    //write here to add functionality
}

void BBproject::brush_edited(){
    QLineEdit* line = qobject_cast<QLineEdit*>(sender());
    bool ok;
    int res = line->text().toInt(&ok);
    if(ok) br_thickness = res;
    else line->setText(QString::number(br_thickness));
    std::cout<<"new thickness is "<<br_thickness<<"\n";
    //write here to add functionality
}

void BBproject::fill_switched(){
    QCheckBox* box = qobject_cast<QCheckBox*>(sender());
    fill_shape = box->isChecked();
    std::cout<<"fill property is now "<<fill_shape<<"\n";
    //write here to add functionality
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

