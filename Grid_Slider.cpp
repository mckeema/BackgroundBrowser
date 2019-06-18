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

#include "Grid_Slider.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>

Grid_Slider::Grid_Slider(std::vector<int> values_in, QWidget *parent)
    : QWidget(parent) {
    values = values_in;
    value = values.front();

    layout = new QHBoxLayout(this);
    label = new QLabel(this);
    slider = new QSlider(Qt::Horizontal, this);

    label->setText(QString::number(values.front()));

    slider->setTickPosition(QSlider::TicksBothSides);
    slider->setTickInterval(1);
    slider->setSingleStep(1);
    slider->setRange(1, values.size());

    layout->addWidget(label, 0);
    layout->addWidget(slider, 1);

    setLayout(layout);

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(set_value(int)));
}

Grid_Slider::~Grid_Slider() {}

void Grid_Slider::set_value(int value_in) {
    value = values[value_in-1];

    label->setText(QString::number(value));

    emit valueChanged(slider->value());
}
