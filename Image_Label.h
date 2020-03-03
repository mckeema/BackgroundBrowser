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

#ifndef IMAGE_LABEL_H
#define IMAGE_LABEL_H

#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QString>

class QCheckBox;
class QLabel;
class QMouseEvent;
class QSettings;
class QWidget;
class QNetworkReply;

enum Fullsize_Origin : char {
    Save, Window
};

class Image_Label : public QLabel {
    Q_OBJECT

    public:
        Image_Label(QSettings *settings_in, QWidget *parent);
        Image_Label(Image_Label *label, QSettings *settings_in, QWidget *parent, bool full = false);

        void set_img(QString filename, QString id_in);
        void set_img(QImage img, QString id_in);
        void set_fullsize(QNetworkReply *reply, Fullsize_Origin origin);
        void get_fullsize(Fullsize_Origin origin);
        void resize();
        int get_pos() const;
        void set_pos(int value);
        void save_image();
        bool is_selected();
        void deselect();
        QString get_id();
        
    signals:
        void similar_pressed(QString query);
        void finished_save();
        void finished_window();
    public slots:
        void create_window();
        void image_save_helper();
    protected:
        void mousePressEvent(QMouseEvent *event);
        void mouseDoubleClickEvent(QMouseEvent *event);
    private:
        QPixmap orig_pixmap;
        QPixmap fullsize;
        QCheckBox *check;
        int pos;
        bool selected;
        QString id;
        QString url;
        QSettings *settings;
};

#endif
