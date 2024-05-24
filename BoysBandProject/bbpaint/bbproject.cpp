#include "bbproject.h"
#include "QtColorWidgets/color_wheel.hpp"
#include "ui_bbproject.h"
#include <iostream>


QColor lightGray{235, 235, 235};
QColor darkGray{50, 50, 50};
QPalette light_palette(lightGray, lightGray);
QPalette dark_palette(darkGray, darkGray);
QSize image_default_size{1200, 675};
const int default_brush_thickness = 7;
const int default_eraser_size = 7;
const char * supported_formats{"Images (*.png *.xpm *.jpg *.bmp *.jpeg)"};

BBproject::BBproject(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BBproject)
{
    this->setWindowTitle("Blue Lines - Безымянный");
    this->setWindowIcon(QIcon(":/icons/mars-double.png"));
    this->setPalette(light_palette);
    ui->setupUi(this);
    er_size = default_eraser_size;
    br_thickness = default_brush_thickness;
    fill_shape = false;
    paintwid = new PaintWidget;
    ui->verticalLayout_2->addWidget(paintwid);
    ui->eraser_size->setText(QString::number(er_size));
    ui->brush_thickness->setText(QString::number(br_thickness));
    connect(ui->shape_fill, SIGNAL(stateChanged(int)), SLOT(fill_switched()));
    connect(ui->eraser_size, SIGNAL(editingFinished()), SLOT(eraser_edited()));
    connect(ui->brush_thickness, SIGNAL(editingFinished()), SLOT(brush_edited()));
    connect_buttons(ui->buttons, SLOT(clicked_tool()));
    connect_buttons(ui->eraser_modes, SLOT(clicked_eraser_mode()));
    connect_buttons(ui->shape_modes, SLOT(clicked_shape_mode()));
    connect_buttons(ui->brush_modes, SLOT(clicked_brush_mode()));
    connect_buttons_l(ui->fill_effects, SLOT(clicked_fill_effect_mode()));
    connect_buttons_l(ui->outline_effects, SLOT(clicked_outline_effect_mode()));
    path = new QString;
    connect_colors();
    drawBtnIcons();
}

BBproject::~BBproject()
{
    delete ui;
    path->~QString();
}

void BBproject::uncheck_buttons(QLayout *container){
    QList <QToolButton*> list = container->parentWidget()->findChildren<QToolButton*>(QString(), Qt::FindDirectChildrenOnly);
    for(auto unit : list) {unit->setChecked(false); unit->setCheckable(false);}
}

int BBproject::get_checked_button(QLayout *container){
    QList <QToolButton*> list = container->parentWidget()->findChildren<QToolButton*>(QString(), Qt::FindDirectChildrenOnly);
    for(auto unit : list) {if(unit->isChecked()) return list.indexOf(unit);}
    return -1;
}

void BBproject::connect_buttons(QLayout *container, const char* slot){
    QList <QToolButton*> list = container->parentWidget()->findChildren<QToolButton*>(QString(), Qt::FindDirectChildrenOnly);
    for(auto unit : list) connect(unit, SIGNAL(clicked()), slot);
}

void BBproject::uncheck_buttons_l(QLayout *container){
    for(int i = 0; i<container->count(); i++){
        auto unit = qobject_cast<QToolButton*>(container->itemAt(i)->widget());
        unit->setChecked(false);
        unit->setCheckable(false);
    }
}

int BBproject::get_checked_button_l(QLayout *container){
    for(int i = 0; i<container->count(); i++){
        auto unit = qobject_cast<QToolButton*>(container->itemAt(i)->widget());
        if(unit->isChecked()) return i;
    }
    return -1;
}

void BBproject::connect_buttons_l(QLayout *container, const char* slot){
    for(int i = 0; i<container->count(); i++){
        auto unit = qobject_cast<QToolButton*>(container->itemAt(i)->widget());
        connect(unit, SIGNAL(clicked()), slot);
    }
}

void BBproject::connect_colors(){
    color_widgets::ColorWheel* cw1 = new color_widgets::ColorWheel(ui->brush_page);
    ui->brush_color_setter->insertWidget(0, cw1);
    connect(cw1, SIGNAL(colorSelected(QColor)), SLOT(color_switched()));

    color_widgets::ColorWheel* cw2 = new color_widgets::ColorWheel(ui->eraser_page);
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
    paintwid->setColor(color);
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
    int id;
    if(!b->isCheckable()){
        uncheck_buttons(ui->buttons);
        b->setCheckable(true);
        ui->tool_stack->setCurrentIndex(ui->buttons->indexOf(b));
        //write here to initialize tools
        switch (ui->buttons->indexOf(b)) {
        case 0:
            std::cout<<"switching to mouse tool\n";
            paintwid->setActiveTool(-1);
            break;
        case 1:
            std::cout<<"switching to eraser tool\n";
            paintwid->setActiveTool(101);
            paintwid->setPenWidth(er_size);
            break;
        case 2:
            std::cout<<"switching to shapes tool\n";
            set_color(ui->eraser_page->findChild<color_widgets::ColorWheel*>()->color(), 0);
            paintwid->setPenWidth(3);
            id = get_checked_button(ui->shape_modes);
            switch (id) {
            case 0:
                paintwid->setActiveTool(1);
                break;
            case 2:
                paintwid->setActiveTool(2);
                break;
            case 3:
                paintwid->setActiveTool(3);
                break;
            case 4:
                paintwid->setActiveTool(4);
                break;
            case 5:
                paintwid->setActiveTool(5);
                break;
            case 7:
                paintwid->setActiveTool(7);
                break;
            default:
                paintwid->setActiveTool(-1);
                break;
            }
            break;
        case 3:
            std::cout<<"switching to brush tool\n";
            set_color(ui->brush_page->findChild<color_widgets::ColorWheel*>()->color(), 0);
            paintwid->setPenWidth(br_thickness);
            id = get_checked_button(ui->brush_modes);
            switch (id) {
            case 0:
                paintwid->setActiveTool(103);
                break;
            case 1:
                paintwid->setActiveTool(102);
                break;
            case 2:
                paintwid->setActiveTool(103);
                break;
            case 3:
                paintwid->setActiveTool(103);
                break;
            case 4:
                paintwid->setActiveTool(103);
                break;
            default:
                paintwid->setActiveTool(-1);
                break;
            }
            break;
        case 4:
            std::cout<<"switching to fill tool\n";
            set_color(ui->fill_page->findChild<color_widgets::ColorWheel*>()->color(), 0);
            paintwid->setActiveTool(201);
            break;
        case 5:
            std::cout<<"switching to effects tool\n";
            paintwid->setActiveTool(-1);
            break;
        case 6:
            std::cout<<"switching to text editor tool\n";
            paintwid->setActiveTool(-1);
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
            paintwid->circle_style = false;
            break;
        case 1:
            std::cout<<"switching to circle eraser mode\n";
            paintwid->circle_style = true;
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
        case 0:
            paintwid->setActiveTool(1);
            break;
//        case 1: star
//            break;
        case 2:
            paintwid->setActiveTool(2);
            break;
        case 3:
            paintwid->setActiveTool(3);
            break;
        case 4:
            paintwid->setActiveTool(4);
            break;
        case 5:
            paintwid->setActiveTool(5);
            break;
        case 7:
            paintwid->setActiveTool(7);
            break;
        default:
            paintwid->setActiveTool(-1);
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
        case 0:
            paintwid->setActiveTool(103);
            paintwid->pen_type = 0;
            break;
        case 1:
            paintwid->setActiveTool(102);
            paintwid->pen_type = -1;
            break;
        case 2:
            paintwid->setActiveTool(103);
            paintwid->pen_type = 1;
            break;
        case 3:
            paintwid->setActiveTool(103);
            paintwid->pen_type = 2;
            break;
        case 4:
            paintwid->setActiveTool(103);
            paintwid->pen_type = 3;
            break;
        default:
            paintwid->setActiveTool(-1);
            break;
        }
    }
    b->setChecked(true);
}

void BBproject::clicked_fill_effect_mode(){
    QToolButton *b = qobject_cast<QToolButton*>(sender());
    if(!b->isCheckable()){
        uncheck_buttons_l(ui->fill_effects);
        b->setCheckable(true);
        //write here to switch effect
        switch (ui->fill_effects->indexOf(b)) {
        case 0:
            paintwid->setBrushStyle(Qt::SolidPattern);
            break;
        case 1:
            paintwid->setBrushStyle(Qt::Dense5Pattern);
            break;
        case 2:
            paintwid->setBrushStyle(Qt::HorPattern);
            break;
        case 3:
            paintwid->setBrushStyle(Qt::VerPattern);
            break;
        case 4:
            paintwid->setBrushStyle(Qt::CrossPattern);
            break;
        case 5:
            paintwid->setBrushStyle(Qt::DiagCrossPattern);
            break;
        }
    }
    b->setChecked(true);
}

void BBproject::clicked_outline_effect_mode(){
    QToolButton *b = qobject_cast<QToolButton*>(sender());
    if(!b->isCheckable()){
        uncheck_buttons_l(ui->outline_effects);
        b->setCheckable(true);
        //write here to switch effect
        switch (ui->outline_effects->indexOf(b)) {
        case 0:
            paintwid->setPenStyle(Qt::DashDotDotLine);
            break;
        case 1:
            paintwid->setPenStyle(Qt::DotLine);
            break;
        case 2:
            paintwid->setPenStyle(Qt::DashDotLine);
            break;
        case 3:
            paintwid->setPenStyle(Qt::DashLine);
            break;
        case 4:
            paintwid->setPenStyle(Qt::SolidLine);
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
    paintwid->setPenWidth(er_size);
}

void BBproject::brush_edited(){
    QLineEdit* line = qobject_cast<QLineEdit*>(sender());
    bool ok;
    int res = line->text().toInt(&ok);
    if(ok) br_thickness = res;
    else line->setText(QString::number(br_thickness));
    std::cout<<"new thickness is "<<br_thickness<<"\n";
    paintwid->setPenWidth(br_thickness);
    //write here to add functionality
}

void BBproject::fill_switched(){
    QCheckBox* box = qobject_cast<QCheckBox*>(sender());
    fill_shape = box->isChecked();
    std::cout<<"fill property is now "<<fill_shape<<"\n";
    paintwid->filling = fill_shape;
    //write here to add functionality
}

void BBproject::on_open_triggered()
{
    if (paintwid->changed){
        QMessageBox* saveMessage = new QMessageBox(QMessageBox::Question,
                                                   tr("Внимание"),
                                                   tr("Сохранить изменения в открытом файле?"),
                                                   QMessageBox::Yes | QMessageBox::No |QMessageBox::Cancel);
        saveMessage->setWindowIcon(QIcon(":/icons/double_mars.png"));
        int n = saveMessage->exec();
        delete saveMessage;
        if (n == QMessageBox::Yes)
            on_save_triggered();
        if (n == QMessageBox::Cancel)
            return;
    }
    *path = QFileDialog::getOpenFileName(this,
                                        tr("Открыть файл"),
                                        tr("/home"),
                                        tr(supported_formats));
    if (!path->isNull()){
        paintwid->setImage(QImage(*path));
        this->setWindowTitle("Blue Lines - " + *path);
    }
}

void BBproject::on_save_triggered()
{
    if (path->isNull()){
        on_save_as_triggered();
        return;
    }
    paintwid->getImage().save(*path);
    paintwid->changed = false;
}


void BBproject::on_save_as_triggered()
{
    *path = QFileDialog::getSaveFileName(this,
                                         tr("Сохранить файл"),
                                         *path,
                                         tr(supported_formats));
    paintwid->getImage().save(*path);
    paintwid->changed = false;
}


void BBproject::on_close_triggered()
{
    if (paintwid->changed){
        QMessageBox* saveMessage = new QMessageBox(QMessageBox::Question,
                                                   tr("Внимание"),
                                                   tr("Сохранить изменения перед закрытием?"),
                                                   QMessageBox::Yes | QMessageBox::No |QMessageBox::Cancel);
        saveMessage->setWindowIcon(QIcon(":/icons/double_mars.png"));
        int n = saveMessage->exec();
        delete saveMessage;
        if (n == QMessageBox::Yes)
            on_save_triggered();
        if (n == QMessageBox::Cancel)
            return;
    }
    path->clear();
    paintwid->clearAll();
}


void BBproject::on_light_triggered()
{
    this->setPalette(light_palette);
    ui->mouse->setIcon(QIcon(":/icons/cursor.png"));
    ui->eraser->setIcon(QIcon(":/icons/eraser.png"));
    ui->fill->setIcon(QIcon(":/icons/fill.png"));
    ui->shapes->setIcon(QIcon(":/icons/shapes.png"));
    ui->brush->setIcon(QIcon(":/icons/brush.png"));
    ui->text_red->setIcon(QIcon(":/icons/text.png"));
    ui->effects->setIcon(QIcon(":/icons/effects.png"));
    ui->rotate_clockwise->setIcon(QIcon(":/icons/rotate-right.png"));
    ui->rotate_counterclockwise->setIcon(QIcon(":/icons/rotate-left.png"));
    ui->horizontal_mirror->setIcon(QIcon(":/icons/reflect-horizontal.png"));
    ui->vertical_mirror->setIcon(QIcon(":/icons/reflect-vertical.png"));
    ui->eraser_circle->setIcon(QIcon(":/icons/circle.png"));
    ui->eraser_square->setIcon(QIcon(":/icons/square.png"));
    ui->shape_line->setIcon(QIcon(":/icons/line.png"));
    ui->shape_spline->setIcon(QIcon(":/icons/spline.png"));
    ui->shape_circle->setIcon(QIcon(":/icons/circle.png"));
    ui->shape_round_rect->setIcon(QIcon(":/icons/rounded-rectangle.png"));
    ui->shape_rectangle->setIcon(QIcon(":/icons/rectangle.png"));
    ui->shape_triangle->setIcon(QIcon(":/icons/triangle.png"));
    ui->shape_curved->setIcon(QIcon(":/icons/curved.png"));
    ui->pencil->setIcon(QIcon(":/icons/pencil.png"));
    ui->highlighter->setIcon(QIcon(":/icons/highlighter.png"));
    ui->chalk->setIcon(QIcon(":/icons/chalk.png"));
    ui->brush_1->setIcon(QIcon(":/icons/brush-1.png"));
    ui->brush_2->setIcon(QIcon(":/icons/brush-2.png"));
}


void BBproject::on_dark_triggered()
{
    this->setPalette(dark_palette);
    ui->mouse->setIcon(QIcon(":/icons/cursor-white.png"));
    ui->eraser->setIcon(QIcon(":/icons/eraser-white.png"));
    ui->fill->setIcon(QIcon(":/icons/fill-white.png"));
    ui->shapes->setIcon(QIcon(":/icons/shapes-white.png"));
    ui->brush->setIcon(QIcon(":/icons/brush-white.png"));
    ui->text_red->setIcon(QIcon(":/icons/text-white.png"));
    ui->effects->setIcon(QIcon(":/icons/effects-white.png"));
    ui->rotate_clockwise->setIcon(QIcon(":/icons/rotate-right-white.png"));
    ui->rotate_counterclockwise->setIcon(QIcon(":/icons/rotate-left-white.png"));
    ui->horizontal_mirror->setIcon(QIcon(":/icons/reflect-horizontal-white.png"));
    ui->vertical_mirror->setIcon(QIcon(":/icons/reflect-vertical-white.png"));
    ui->eraser_circle->setIcon(QIcon(":/icons/circle-white.png"));
    ui->eraser_square->setIcon(QIcon(":/icons/square-white.png"));
    ui->shape_line->setIcon(QIcon(":/icons/line-white.png"));
    ui->shape_spline->setIcon(QIcon(":/icons/spline-white.png"));
    ui->shape_circle->setIcon(QIcon(":/icons/circle-white.png"));
    ui->shape_round_rect->setIcon(QIcon(":/icons/rounded-rectangle-white.png"));
    ui->shape_rectangle->setIcon(QIcon(":/icons/rectangle-white.png"));
    ui->shape_triangle->setIcon(QIcon(":/icons/triangle-white.png"));
    ui->shape_curved->setIcon(QIcon(":/icons/curved-white.png"));
    ui->pencil->setIcon(QIcon(":/icons/pencil-white.png"));
    ui->highlighter->setIcon(QIcon(":/icons/highlighter-white.png"));
    ui->chalk->setIcon(QIcon(":/icons/chalk-white.png"));
    ui->brush_1->setIcon(QIcon(":/icons/brush-1-white.png"));
    ui->brush_2->setIcon(QIcon(":/icons/brush-2-white.png"));
}

void BBproject::closeEvent(QCloseEvent *event)
{
    if (paintwid->changed){
        QMessageBox* saveMessage = new QMessageBox(QMessageBox::Question,
                                                   tr("Внимание"),
                                                   tr("Сохранить изменения перед выходом?"),
                                                   QMessageBox::Yes | QMessageBox::No |QMessageBox::Cancel);
        saveMessage->setWindowIcon(QIcon(":/icons/double_mars.png"));
        int n = saveMessage->exec();
        delete saveMessage;
        if (n == QMessageBox::Yes)
            on_save_triggered();
        if (n == QMessageBox::Cancel){
            event->ignore();
            return;
        }
        event->accept();
    }
}

void BBproject::drawBtnIcons()
{
    ui->f_e_1->setIcon(pixForBrush(QBrush(Qt::SolidPattern)));
    ui->f_e_3->setIcon(pixForBrush(QBrush(Qt::Dense5Pattern)));
    ui->f_e_4->setIcon(pixForBrush(QBrush(Qt::HorPattern)));
    ui->f_e_5->setIcon(pixForBrush(QBrush(Qt::VerPattern)));
    ui->f_e_6->setIcon(pixForBrush(QBrush(Qt::CrossPattern)));
    ui->f_e_7->setIcon(pixForBrush(QBrush(Qt::DiagCrossPattern)));
    QSize e_but_size = ui->f_e_1->geometry().size();
    ui->f_e_1->setIconSize(e_but_size);
    ui->f_e_3->setIconSize(e_but_size);
    ui->f_e_4->setIconSize(e_but_size);
    ui->f_e_5->setIconSize(e_but_size);
    ui->f_e_6->setIconSize(e_but_size);
    ui->f_e_7->setIconSize(e_but_size);

    ui->o_e_1->setIcon(pixForPen(QPen(Qt::SolidLine)));
    ui->o_e_2->setIcon(pixForPen(QPen(Qt::DashLine)));
    ui->o_e_3->setIcon(pixForPen(QPen(Qt::DashDotLine)));
    ui->o_e_4->setIcon(pixForPen(QPen(Qt::DashDotDotLine)));
    ui->o_e_5->setIcon(pixForPen(QPen(Qt::DotLine)));
    QSize o_but_size = ui->o_e_1->geometry().size();
    ui->o_e_1->setIconSize(o_but_size);
    ui->o_e_2->setIconSize(o_but_size);
    ui->o_e_3->setIconSize(o_but_size);
    ui->o_e_4->setIconSize(o_but_size);
    ui->o_e_5->setIconSize(o_but_size);
}

QPixmap BBproject::pixForBrush(QBrush brush)
{
    int x,y;
    x = ui->f_e_1->geometry().width();
    y=ui->f_e_1->geometry().height();
    QPixmap pixmap(x,y);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image;
    QRect target(0, 0, x, y);
    QRect source(0, 0, x, y);
    painter.setBrush(brush);
    painter.fillRect(QRect(5, 2, x-10, y-5), brush);
    painter.drawPixmap(target, image, source);

    return pixmap;
}

QPixmap BBproject::pixForPen(QPen pen)
{
    int x,y;
    x=185;
    y=28;
    QPixmap pixmap(x, y);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image;
    QRect target(0, 0, x, y);
    QRect source(0, 0, x, y);
    pen.setColor(Qt::black);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawLine(QPointF(5,y/2),QPointF(x-5,y/2));
    painter.drawPixmap(target, image, source);

    return pixmap;
}
