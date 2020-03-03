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
#include <QImageReader>
#include <QLabel>
#include <QSettings>
#include <QtNetwork>

#include "Image_Window.h"

Image_Label::Image_Label(QSettings *settings_in, QWidget *parent)
    : QLabel(parent) {
    pos = 0;
    selected = false;
    id = "placeholder";
    url = "placeholder";
    settings = settings_in;

    check = new QCheckBox(this);

    setScaledContents(false);
    setMinimumSize(1, 1);

    connect(this, &Image_Label::finished_save, this, &Image_Label::image_save_helper);
    connect(this, &Image_Label::finished_window, this, &Image_Label::create_window);
}

Image_Label::Image_Label(Image_Label *label, QSettings *settings, QWidget *parent, bool full)
    : Image_Label(settings, parent) {
    if (!full) {
        orig_pixmap = label->orig_pixmap;
    } else {
        orig_pixmap = label->fullsize;
    }
    fullsize = label->fullsize;
    id = label->id;
    url = label->url;
    check->setEnabled(false);
    check->setVisible(false);
}

void Image_Label::set_img(QString filename, QString id_in) {
    orig_pixmap = QPixmap(filename);
    url = id_in;
    id = id_in.section("/", -1, -1);
    fullsize.load("");
}

void Image_Label::set_img(QImage img, QString id_in) {
    orig_pixmap.convertFromImage(img);
    url = id_in;
    id = id_in.section("/", -1, -1);
    fullsize.load("");
}

void Image_Label::set_fullsize(QNetworkReply *reply, Fullsize_Origin origin) {
    if (reply->error() == QNetworkReply::NetworkError::NoError) {
        QImageReader img_reader(reply);
        QImage img = img_reader.read();
        fullsize.convertFromImage(img);

        if (origin == Fullsize_Origin::Save) {
            emit finished_save();
        } else {
            emit finished_window();
        }
    } else {
        get_fullsize(origin);
    }
}

void Image_Label::get_fullsize(Fullsize_Origin origin) {
    QNetworkAccessManager *nam_img = new QNetworkAccessManager(this);

    QNetworkReply *reply = nam_img->get(QNetworkRequest(url));

    connect(nam_img, &QNetworkAccessManager::finished, this, [this,reply,origin](){set_fullsize(reply, origin);});
    connect(nam_img, &QNetworkAccessManager::finished, this, [nam_img](){nam_img->deleteLater();});
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
    if (fullsize.isNull()) {
        get_fullsize(Fullsize_Origin::Save);
    } else {
        image_save_helper();
    }
}

void Image_Label::image_save_helper() {
    fullsize.save(settings->value("Download/save_dir").toString() + "/" + id, 0, 100);

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

QString Image_Label::get_id() {
    return id;
}

void Image_Label::mousePressEvent(QMouseEvent *event) {
    selected = !selected;
    check->setChecked(selected);
}

void Image_Label::mouseDoubleClickEvent(QMouseEvent *event) {
    deselect();

    if (fullsize.isNull()) {
        get_fullsize(Fullsize_Origin::Window);
    } else {
        create_window();
    }
}

void Image_Label::create_window() {
    Image_Window *window = new Image_Window(new Image_Label(this, settings, window, true), parentWidget()->parentWidget());
    connect(window, &Image_Window::similar_pressed, this, [this](QString query){emit similar_pressed(query);});
    window->setWindowTitle(id.section(".", 0, 0).section("-", -1, -1));

    window->show();
    window->resize_img();
}
