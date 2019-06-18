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

#ifndef PAGE_CONTROLLER_H
#define PAGE_CONTROLLER_H

#include <QWidget>

class QHBoxLayout;
class QPushButton;

class Page_Controller : public QWidget {
    Q_OBJECT

    public:
        Page_Controller(QWidget *parent);
        ~Page_Controller();
    signals:
        void prev_button_released();
        void next_button_released();
    private:
        QHBoxLayout *layout;
        QPushButton *prev_button;
        QPushButton *next_button;
};

#endif
