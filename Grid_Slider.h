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

#ifndef GRID_SLIDER_H
#define GRID_SLIDER_H

#include <QWidget>

#include <vector>

class QHBoxLayout;
class QLabel;
class QSlider;

class Grid_Slider : public QWidget {
    Q_OBJECT

    public:
        Grid_Slider(std::vector<int> values_in, QWidget *parent);
        ~Grid_Slider();
    private slots:
        void set_value(int value_in);
    signals:
        void valueChanged(int value_out);
    private:
        QHBoxLayout *layout;
        QLabel *label;
        QSlider *slider;
        int value;
        std::vector<int> values;
};

#endif
