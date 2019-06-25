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

#include "Image_Window.h"

#include <QDesktopServices>
#include <QGridLayout>
#include <QPushButton>
#include <QUrl>

#include "Image_Label.h"

Image_Window::Image_Window(Image_Label *label, QWidget *parent)
    : QDialog(parent) {
    layout = new QGridLayout(this);

    resize(parent->size());

    img = label;
    layout->addWidget(img, 0, 0, 1, 4);

    QPushButton *similar_button = new QPushButton(tr("Search for Similar"), this);
    QPushButton *open_browser_button = new QPushButton(tr("Open in Browser"), this);
    QPushButton *save_button = new QPushButton(tr("Save"), this);
    QPushButton *save_close_button = new QPushButton(tr("Save and Close"), this);
    connect(similar_button, &QPushButton::released, this, [this](){emit similar_pressed("like:" + img->get_id().section(".", 0, 0).section("-", 1, 1)); close();});
    connect(open_browser_button, &QPushButton::released, this, [this](){QDesktopServices::openUrl(QUrl("https://wallhaven.cc/w/" + img->get_id().section(".", 0, 0).section("-", -1, -1)));});
    connect(save_button, &QPushButton::released, this, [this](){img->save_image();});
    connect(save_close_button, &QPushButton::released, this, [this](){img->save_image(); close();});
    layout->addWidget(similar_button, 1, 0);
    layout->addWidget(open_browser_button, 1, 1);
    layout->addWidget(save_button, 1, 2);
    layout->addWidget(save_close_button, 1, 3);

    setModal(true);

    setLayout(layout);
}

Image_Window::~Image_Window() {}

void Image_Window::resize_img() {
    img->resize();
    layout->setSizeConstraint(QLayout::SetFixedSize);
}
