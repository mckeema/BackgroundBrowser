/*
Copyright 2019 Matt M.

This file is part of BackgroundBrowser.

BackgroundBrowser is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

BackgroundBrowser is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with BackgroundBrowser.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "Image_Label.h"

#include <QCheckBox>
#include <QDir>
#include <QLabel>

Image_Label::Image_Label(QWidget *parent)
    : QLabel(parent) {
    pos = 0;
    selected = false;
    id = "placeholder";

    check = new QCheckBox(this);

    setScaledContents(false);
    setMinimumSize(1, 1);
}

void Image_Label::set_img(QString filename, QString id_in) {
    orig_pixmap = QPixmap(filename);
    id = id_in.section("/", -1, -1);
}

void Image_Label::set_img(QImage img, QString id_in) {
    orig_pixmap.convertFromImage(img);
    id = id_in.section("/", -1, -1);
}

void Image_Label::resize() {
    double ratio = double(width())/double(height());

    if (width() <= height()) {
        setPixmap(orig_pixmap.scaled(width(), int(width()/ratio), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        setPixmap(orig_pixmap.scaled(int(height()*ratio), height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

int Image_Label::get_pos() const {
    return pos;
}

void Image_Label::set_pos(int value) {
    pos = value;
}

void Image_Label::save_image() {
    orig_pixmap.save(id, 0, 100);

    selected = false;
    check->setChecked(selected);
}

bool Image_Label::is_selected() {
    return selected;
}

void Image_Label::deselect() {
    selected = false;
    check->setChecked(selected);
}

void Image_Label::mousePressEvent(QMouseEvent *event) {
    selected = !selected;
    check->setChecked(selected);
}
