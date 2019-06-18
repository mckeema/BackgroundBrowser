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

#include "Page_Controller.h"

#include <QPushButton>
#include <QHBoxLayout>

Page_Controller::Page_Controller(QWidget *parent)
    : QWidget(parent) {
    layout = new QHBoxLayout(this);
    prev_button = new QPushButton("<", this);
    next_button = new QPushButton(">", this);

    layout->addWidget(prev_button, 0);
    layout->addWidget(next_button, 1);
    layout->setStretch(0, 0);
    layout->setStretch(1, 0);

    setLayout(layout);

    connect(prev_button, &QPushButton::released, this, [this](){emit prev_button_released();});
    connect(next_button, &QPushButton::released, this, [this](){emit next_button_released();});
}

Page_Controller::~Page_Controller() {};
