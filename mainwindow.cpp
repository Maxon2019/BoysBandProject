#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    paintwid = new PaintWidget;
    ui->verticalLayout->addWidget(paintwid);

    penWidthValue = new QSpinBox;

    colorBtn1 = new QPushButton;
    colorBtn2 = new QPushButton;

    pen=QPen(Qt::black,1,Qt::SolidLine);
    brush=QBrush(Qt::white, Qt::SolidPattern);

    createActions();
    createMenus();
    drawBtnIcons();
    addToolBar(Qt::TopToolBarArea, myToolBar());

    connect(
                this,
                SIGNAL(getActiveTool(int)),
                paintwid,
                SLOT(setActiveTool(int))
            );

    connect(
                this,
                SIGNAL(changeBrush(QBrush)),
                paintwid,
                SLOT(setBrush(QBrush))
            );

    connect(
                this,
                SIGNAL(changePen(QPen)),
                paintwid,
                SLOT(setPen(QPen))
            );

    connect(
                colorBtn2,
                SIGNAL(clicked()),
                SLOT(changeBrushColor())
            );

    connect(
                colorBtn1,
                SIGNAL(clicked()),
                SLOT(changePenColor())
            );

    connect(
                penWidthValue,
                SIGNAL(valueChanged(int)),
                SLOT(changePenWidth(int))
            );


    connect(
                penWidthValue,
                SIGNAL(valueChanged(int)),
                paintwid,
                SLOT(setPenWidth(int))
            );

}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::createActions()
{
    openAct = new QAction(QIcon(":/images/open.png"),tr("&Открыть..."),this);
    openAct->setShortcut(QKeySequence::Open);
    connect(
                openAct,
                SIGNAL(triggered()),
                this,
                SLOT(openFile())
            );

    saveAct = new QAction(QIcon(":/images/save.png"),tr("&Сохранить..."),this);
    saveAct->setShortcut(QKeySequence::Save);
    connect(
                saveAct,
                SIGNAL(triggered()),
                this,
                SLOT(saveFile())
           );

    closeAct = new QAction(tr("&Выход"),this);
    closeAct->setShortcut(QKeySequence::Close);
    connect(
                closeAct,
                SIGNAL(triggered()),
                this,
                SLOT(close())
           );

    clearAct = new QAction(/*QIcon(":/images/info.png"),*/tr("&Очистить"),this);
    connect(
                clearAct,
                SIGNAL(triggered()),
                paintwid,
                SLOT(clearAll())
                );



}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Файл"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAct);

    correctMenu = menuBar()->addMenu(tr("&Правка"));
    correctMenu->addAction(clearAct);

    // infoMenu = menuBar()->addMenu(tr("&Информация"));
    // infoMenu->addAction(aboutAct);

}

void MainWindow::drawBtnIcons()
{
    ui->pushButton_9->setIcon(pixForBrush(QBrush(Qt::SolidLine)));
    ui->pushButton_10->setIcon(pixForBrush(QBrush(Qt::NoBrush)));
    ui->pushButton_11->setIcon(pixForBrush(QBrush(Qt::Dense7Pattern)));
    ui->pushButton_12->setIcon(pixForBrush(QBrush(Qt::HorPattern)));
    ui->pushButton_13->setIcon(pixForBrush(QBrush(Qt::VerPattern)));
    ui->pushButton_14->setIcon(pixForBrush(QBrush(Qt::CrossPattern)));
    ui->pushButton_15->setIcon(pixForBrush(QBrush(Qt::DiagCrossPattern)));
    //ui->pushButton_16->setIcon();

    ui->pushButton_17->setIcon(pixForPen(QPen(Qt::SolidLine)));
    ui->pushButton_18->setIcon(pixForPen(QPen(Qt::DashLine)));
    ui->pushButton_19->setIcon(pixForPen(QPen(Qt::DashDotLine)));
    ui->pushButton_20->setIcon(pixForPen(QPen(Qt::DashDotDotLine)));
    ui->pushButton_21->setIcon(pixForPen(QPen(Qt::DotLine)));
}

QPixmap MainWindow::pixForBrush(QBrush brush)
{
    int x,y;
    x=92;
    y=40;
    QPixmap pixmap(x,y );
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

QPixmap MainWindow::pixForPen(QPen pen)
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

QToolBar* MainWindow::myToolBar()
{
    QToolBar* toolBar = new QToolBar("Options");

    toolBar->addAction(openAct);
    toolBar->addSeparator();
    toolBar->addAction(saveAct);
    toolBar->addSeparator();

    QLabel *lbl;
    lbl = new QLabel;
    QString Lbl("Толщина пера ");
    lbl->setText(Lbl);
    toolBar->addWidget(lbl);
    penWidthValue->setMinimumWidth(50);
    penWidthValue->setMinimum(1);
    toolBar->addWidget(penWidthValue);
    toolBar->addSeparator();

    QLabel *lbl3;
    lbl3 = new QLabel;
    QString Lbl3("Цвет пера ");
    lbl3->setText(Lbl3);
    toolBar->addWidget(lbl3);
    colorBtn1->setIcon(pixForColor(Qt::black));
    toolBar->addWidget(colorBtn1);
    toolBar->addSeparator();

    QLabel *lbl4;
    lbl4 = new QLabel;
    QString Lbl4("Цвет кисти ");
    lbl4->setText(Lbl4);
    toolBar->addWidget(lbl4);
    colorBtn2->setIcon(pixForColor(Qt::white));
    toolBar->addWidget(colorBtn2);

    return toolBar;

}

void MainWindow::openFile()
{

    QString openImageName = QFileDialog::getOpenFileName(this,
                                                        tr("Открыть графический файл"),
                                                         QDir::currentPath());
    QImage img(openImageName);

    paintwid->setImage(img);


}

void MainWindow::saveFile()
{
    QImage saveImage;
    saveImage=paintwid->getImage();

    QString filter;
    QFileDialog *saveDlg = new QFileDialog;
    QString saveImageName = saveDlg->getSaveFileName(this,
                                                    tr("Сохранить графический файл"),
                                                    "MyPictureName",
                                                    "*.png ;; *.jpeg",
                                                    &filter );
    if (!saveImageName.isEmpty())
    {
        if (filter.contains("jpeg"))
            saveImage.save(saveImageName, "JPEG");
        else if (filter.contains("png"))
            saveImage.save(saveImageName, "PNG");
    }

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox* closeMessage = new QMessageBox(QMessageBox::Question,
                                                tr("Внимание"),
                                                tr("Вы действительно хотите выйти?"),
                                                QMessageBox::Yes | QMessageBox::No |QMessageBox::Cancel);
    int n = closeMessage->exec();
    delete closeMessage;
    if (n == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}

void MainWindow::aboutEvent()
{
    QMessageBox::about(
                this,
                tr("О программе"),
                tr("Графический редактор\n"
                   "Лабораторная работа №2"));

}

void MainWindow::changeBrushColor()
{
    QColor newCol=QColorDialog::getColor();
    brush.setColor(newCol);
    colorBtn2->setIcon(pixForColor(newCol));
    emit changeBrush(brush);
}

void MainWindow::changePenColor()
{
    QColor newCol=QColorDialog::getColor();
    pen.setColor(newCol);
    colorBtn1->setIcon(pixForColor(newCol));
    emit changePen(pen);
}


void MainWindow::changePenWidth(int value)
{
    pen.setWidth(value);
    emit changePen(pen);

}

QPixmap MainWindow::pixForColor(QColor color)
{
    QPixmap pixmap(70, 70);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image;
    QRect target(0, 0, 70, 70);
    QRect source(0, 0, 70, 70);
    painter.fillRect(QRect(0, 0, 70, 70), color);
    painter.drawPixmap(target, image, source);

    return pixmap;
}


void MainWindow::on_pushButton_clicked()
{
    emit getActiveTool(1);
    statusBar()->showMessage(QString("Активный инструмент: линия"));
}

void MainWindow::on_pushButton_3_clicked()
{
    emit getActiveTool(2);
    statusBar()->showMessage(QString("Активный инструмент: эллипс"));
}

void MainWindow::on_pushButton_5_clicked()
{
    emit getActiveTool(3);
    statusBar()->showMessage(QString("Активный инструмент: закругленный прямоугольник"));
}

void MainWindow::on_pushButton_17_clicked()
{
    pen.setStyle(Qt::SolidLine);
    emit changePen(pen);
}

void MainWindow::on_pushButton_18_clicked()
{
    pen.setStyle(Qt::DashLine);
    emit changePen(pen);
}

void MainWindow::on_pushButton_19_clicked()
{
    pen.setStyle(Qt::DashDotLine);
    emit changePen(pen);
}

void MainWindow::on_pushButton_20_clicked()
{
    pen.setStyle(Qt::DashDotDotLine);
    emit changePen(pen);
}

void MainWindow::on_pushButton_21_clicked()
{
    pen.setStyle(Qt::DotLine);
    emit changePen(pen);
}


void MainWindow::on_pushButton_9_clicked()
{
    brush.setStyle(Qt::SolidPattern);
    emit changeBrush(brush);
}

void MainWindow::on_pushButton_10_clicked()
{
    brush.setStyle(Qt::NoBrush);
    emit changeBrush(brush);
}

void MainWindow::on_pushButton_11_clicked()
{
    brush.setStyle(Qt::Dense7Pattern);
    emit changeBrush(brush);
}

void MainWindow::on_pushButton_12_clicked()
{
    brush.setStyle(Qt::HorPattern);
    emit changeBrush(brush);
}

void MainWindow::on_pushButton_13_clicked()
{
    brush.setStyle(Qt::VerPattern);
    emit changeBrush(brush);
}

void MainWindow::on_pushButton_14_clicked()
{
    brush.setStyle(Qt::CrossPattern);
    emit changeBrush(brush);
}

void MainWindow::on_pushButton_15_clicked()
{
    brush.setStyle(Qt::DiagCrossPattern);
    emit changeBrush(brush);
}

void MainWindow::on_pushButton_7_clicked()
{
    emit getActiveTool(4);
    statusBar()->showMessage(QString("Активный инструмент: кисть"));
}

void MainWindow::on_pushButton_2_clicked()
{
    emit getActiveTool(5);
    statusBar()->showMessage(QString("Активный инструмент: ластик"));
}

void MainWindow::on_pushButton_4_clicked()
{
    emit getActiveTool(6);
    statusBar()->showMessage(QString("Активный инструмент: прямоугольник"));
}

void MainWindow::on_pushButton_8_clicked()
{
    emit getActiveTool(8);
    statusBar()->showMessage(QString("Активный инструмент: спрей"));
}

void MainWindow::on_pushButton_6_clicked()
{
    emit getActiveTool(7);
    statusBar()->showMessage(QString("Активный инструмент: заливка"));
}
