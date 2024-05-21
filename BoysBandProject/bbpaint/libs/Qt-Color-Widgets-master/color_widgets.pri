# Copyright (C) 2013-2017 Mattia Basaglia
#
#
# This software is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with Color Widgets.  If not, see <http://www.gnu.org/licenses/>.

CONFIG += c++11

INCLUDEPATH += $$PWD/src $$PWD/include

SOURCES += \
    $$PWD/src/QtColorWidgets/color_preview.cpp \
    $$PWD/src/QtColorWidgets/color_wheel.cpp \
    $$PWD/src/QtColorWidgets/gradient_slider.cpp \
    $$PWD/src/QtColorWidgets/hue_slider.cpp \
    $$PWD/src/QtColorWidgets/color_dialog.cpp \
    $$PWD/src/QtColorWidgets/color_selector.cpp \
    $$PWD/src/QtColorWidgets/color_delegate.cpp \
    $$PWD/src/QtColorWidgets/color_list_widget.cpp \
    $$PWD/src/QtColorWidgets/bound_color_selector.cpp \
    $$PWD/src/QtColorWidgets/abstract_widget_list.cpp \
    $$PWD/src/QtColorWidgets/color_palette.cpp \
    $$PWD/src/QtColorWidgets/color_palette_model.cpp \
    $$PWD/src/QtColorWidgets/color_palette_widget.cpp \
    $$PWD/src/QtColorWidgets/swatch.cpp \
    $$PWD/src/QtColorWidgets/color_utils.cpp \
    $$PWD/src/QtColorWidgets/color_2d_slider.cpp \
    $$PWD/src/QtColorWidgets/color_line_edit.cpp \
    $$PWD/src/QtColorWidgets/color_names.cpp

HEADERS += \
    $$PWD/include/QtColorWidgets/color_wheel.hpp \
    $$PWD/include/QtColorWidgets/color_preview.hpp \
    $$PWD/include/QtColorWidgets/gradient_slider.hpp \
    $$PWD/include/QtColorWidgets/hue_slider.hpp \
    $$PWD/include/QtColorWidgets/color_dialog.hpp \
    $$PWD/include/QtColorWidgets/color_selector.hpp \
    $$PWD/include/QtColorWidgets/color_delegate.hpp \
    $$PWD/include/QtColorWidgets/color_list_widget.hpp \
    $$PWD/include/QtColorWidgets/bound_color_selector.hpp \
    $$PWD/include/QtColorWidgets/abstract_widget_list.hpp \
    $$PWD/include/QtColorWidgets/colorwidgets_global.hpp \
    $$PWD/include/QtColorWidgets/color_palette.hpp \
    $$PWD/include/QtColorWidgets/color_palette_model.hpp \
    $$PWD/include/QtColorWidgets/color_palette_widget.hpp \
    $$PWD/include/QtColorWidgets/swatch.hpp \
    $$PWD/src/QtColorWidgets/color_utils.hpp \
    $$PWD/include/QtColorWidgets/color_2d_slider.hpp \
    $$PWD/include/QtColorWidgets/color_line_edit.hpp \
    $$PWD/include/QtColorWidgets/color_names.hpp

FORMS += \
    $$PWD/src/QtColorWidgets/color_dialog.ui \
    $$PWD/src/QtColorWidgets/color_palette_widget.ui

RESOURCES += \
    $$PWD/resources/QtColorWidgets/color_widgets.qrc

DISTFILES += \
    $$PWD/resources/QtColorWidgets/img/cursor.svg \
    $$PWD/resources/QtColorWidgets/img/customization.svg \
    $$PWD/resources/QtColorWidgets/img/eraser.svg \
    $$PWD/resources/QtColorWidgets/img/fill.svg \
    $$PWD/resources/QtColorWidgets/img/mars-double.png \
    $$PWD/resources/QtColorWidgets/img/message-text.svg \
    $$PWD/resources/QtColorWidgets/img/mouse-field.svg \
    $$PWD/resources/QtColorWidgets/img/paint-brush.svg \
    $$PWD/resources/QtColorWidgets/img/rectangle-horizontal.svg \
    $$PWD/resources/QtColorWidgets/img/reflect-horizontal.svg \
    $$PWD/resources/QtColorWidgets/img/reflect-vertical.svg \
    $$PWD/resources/QtColorWidgets/img/resources.svg \
    $$PWD/resources/QtColorWidgets/img/rotate-left.svg \
    $$PWD/resources/QtColorWidgets/img/rotate-right.svg \
    $$PWD/resources/QtColorWidgets/img/square.svg \
    $$PWD/resources/QtColorWidgets/img/star-of-david.png \
    $$PWD/resources/QtColorWidgets/img/star.svg \
    $$PWD/resources/QtColorWidgets/img/triangle.svg \
    $$PWD/resources/QtColorWidgets/img/сircle.svg

