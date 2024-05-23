include(libs/Qt-Color-Widgets-master/color_widgets.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    bbproject.cpp \
    paintwidget.cpp

HEADERS += \
    bbproject.h \
    paintwidget.h

FORMS += \
    bbproject.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    img/cursor.svg \
    img/cursor.svg \
    img/cursor.svg \
    img/cursor_icon.svg \
    img/customization.svg \
    img/customization.svg \
    img/customization.svg \
    img/effects_icon.svg \
    img/eraser.svg \
    img/eraser.svg \
    img/eraser_icon.svg \
    img/fill.svg \
    img/fill.svg \
    img/fill.svg \
    img/fill_icon.svg \
    img/mars-double.png \
    img/mars-double.png \
    img/mars-double.png \
    img/message-text.svg \
    img/message-text.svg \
    img/message-text.svg \
    img/mouse-field.svg \
    img/mouse-field.svg \
    img/mouse-field.svg \
    img/mouse_icon.svg \
    img/paint-brush.svg \
    img/paint-brush.svg \
    img/paint-brush.svg \
    img/paint_brush_icon.svg \
    img/rectangle-horizontal.svg \
    img/rectangle-horizontal.svg \
    img/rectangle-horizontal.svg \
    img/reflect-horizontal.svg \
    img/reflect-horizontal.svg \
    img/reflect-horizontal.svg \
    img/reflect-horizontal_icon.svg \
    img/reflect-vertical.svg \
    img/reflect-vertical.svg \
    img/reflect-vertical.svg \
    img/resources.svg \
    img/resources.svg \
    img/resources.svg \
    img/rotate-left.svg \
    img/rotate-left.svg \
    img/rotate-left.svg \
    img/rotate-left_icon.svg \
    img/rotate-right.svg \
    img/rotate-right.svg \
    img/rotate-right.svg \
    img/rotate-right_icon.svg \
    img/square.svg \
    img/square.svg \
    img/square.svg \
    img/star-of-david.png \
    img/star-of-david.png \
    img/star-of-david.png \
    img/star.svg \
    img/star.svg \
    img/star.svg \
    img/text_icon.svg \
    img/triangle.svg \
    img/triangle.svg \
    img/triangle.svg \
    img/сircle.svg \
    img/сircle.svg \
    img/сircle.svg \
    libs/Qt-Color-Widgets-master/resources/QtColorWidgets/img/cursor.svg \
    libs/Qt-Color-Widgets-master/resources/QtColorWidgets/img/customization.svg \
    libs/Qt-Color-Widgets-master/resources/QtColorWidgets/img/eraser.svg \
    libs/Qt-Color-Widgets-master/resources/QtColorWidgets/img/fill.svg \
    libs/Qt-Color-Widgets-master/resources/QtColorWidgets/img/mars-double.png \
    libs/Qt-Color-Widgets-master/resources/QtColorWidgets/img/message-text.svg \
    libs/Qt-Color-Widgets-master/resources/QtColorWidgets/img/mouse-field.svg \
    libs/Qt-Color-Widgets-master/resources/QtColorWidgets/img/paint-brush.svg \
    libs/Qt-Color-Widgets-master/resources/QtColorWidgets/img/rectangle-horizontal.svg \
    libs/Qt-Color-Widgets-master/resources/QtColorWidgets/img/reflect-horizontal.svg \
    libs/Qt-Color-Widgets-master/resources/QtColorWidgets/img/reflect-vertical.svg \
    libs/Qt-Color-Widgets-master/resources/QtColorWidgets/img/resources.svg \
    libs/Qt-Color-Widgets-master/resources/QtColorWidgets/img/rotate-left.svg \
    libs/Qt-Color-Widgets-master/resources/QtColorWidgets/img/rotate-right.svg \
    libs/Qt-Color-Widgets-master/resources/QtColorWidgets/img/square.svg \
    libs/Qt-Color-Widgets-master/resources/QtColorWidgets/img/star-of-david.png \
    libs/Qt-Color-Widgets-master/resources/QtColorWidgets/img/star.svg \
    libs/Qt-Color-Widgets-master/resources/QtColorWidgets/img/triangle.svg \
    libs/Qt-Color-Widgets-master/resources/QtColorWidgets/img/сircle.svg \
    libs/Qt-Color-Widgets-master/resources/img/cursor.svg \
    libs/Qt-Color-Widgets-master/resources/img/customization.svg \
    libs/Qt-Color-Widgets-master/resources/img/eraser.svg \
    libs/Qt-Color-Widgets-master/resources/img/fill.svg \
    libs/Qt-Color-Widgets-master/resources/img/mars-double.png \
    libs/Qt-Color-Widgets-master/resources/img/message-text.svg \
    libs/Qt-Color-Widgets-master/resources/img/mouse-field.svg \
    libs/Qt-Color-Widgets-master/resources/img/paint-brush.svg \
    libs/Qt-Color-Widgets-master/resources/img/rectangle-horizontal.svg \
    libs/Qt-Color-Widgets-master/resources/img/reflect-horizontal.svg \
    libs/Qt-Color-Widgets-master/resources/img/reflect-vertical.svg \
    libs/Qt-Color-Widgets-master/resources/img/resources.svg \
    libs/Qt-Color-Widgets-master/resources/img/rotate-left.svg \
    libs/Qt-Color-Widgets-master/resources/img/rotate-right.svg \
    libs/Qt-Color-Widgets-master/resources/img/square.svg \
    libs/Qt-Color-Widgets-master/resources/img/star-of-david.png \
    libs/Qt-Color-Widgets-master/resources/img/star.svg \
    libs/Qt-Color-Widgets-master/resources/img/triangle.svg \
    libs/Qt-Color-Widgets-master/resources/img/сircle.svg

RESOURCES += \
    img/icons.qrc
