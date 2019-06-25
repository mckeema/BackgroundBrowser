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

#ifndef IMAGE_WINDOW_H
#define IMAGE_WINDOW_H

#include <QDialog>

class QGridLayout;
class QWidget;

class Image_Label;

class Image_Window : public QDialog {
    Q_OBJECT

    public:
        Image_Window(Image_Label *label, QWidget *parent);
        ~Image_Window();

        void resize_img();
    signals:
        void similar_pressed(QString query);
    private:
        QGridLayout *layout;
        Image_Label *img;
};

#endif
