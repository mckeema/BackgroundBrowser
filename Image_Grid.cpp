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

#include "Image_Grid.h"

#include <QGridLayout>
#include <QImage>
#include <QSettings>
#include <QString>

#include <algorithm>
#include <cmath>

#include "Image_Label.h"

struct less_than_image {
    inline bool operator()(const Image_Label *a, const Image_Label *b) {
        return a->get_pos() < b->get_pos();
    }
};

Image_Grid::Image_Grid(std::vector<int> row_list_in, std::vector<int> col_list_in, std::vector<int> size_list_in, QSettings *settings, QWidget *parent)
    : QWidget(parent) {
    row_list = row_list_in;
    col_list = col_list_in;
    rows = row_list.front();
    cols = col_list.front();
    size_list = size_list_in;
    page = 1;
    last_page = size_list.back()/(row_list.front()*col_list.front());
    sorted = false;

    for (int i = 0; i < size_list.back(); ++i) {
        Image_Label *img = new Image_Label(settings, this);
        connect(img, &Image_Label::similar_pressed, this, [this](QString query){emit similar_pressed(query);});

        img->setVisible(false);

        imgs.push_back(img);
    }

    grid = new QGridLayout(this);

    update(1);

    setLayout(grid);
}

Image_Grid::~Image_Grid() {}

int Image_Grid::get_rows() const {
    return rows;
}

int Image_Grid::get_cols() const {
    return cols;
}

int Image_Grid::get_size() const {
    return rows*cols;
}

int Image_Grid::get_size_index(int size_in) {
    std::vector<int>::iterator it = std::find(size_list.begin(), size_list.end(), size_in);

    return std::distance(size_list.begin(), it)+1;
}

int Image_Grid::get_page() const {
    return page;
}

bool Image_Grid::on_last_page() const {
    return page == last_page;
}

void Image_Grid::set_img(int index, QString filename, QString id) {
    imgs[index]->set_img(filename, id);
}

void Image_Grid::set_img(int index, QImage img, QString id) {
    imgs[index]->set_img(img, id);
}

void Image_Grid::set_page(int page_in) {
    page = page_in;
}

void Image_Grid::set_to_last_page() {
    page = last_page;
}

void Image_Grid::set_pos(int index, int pos_in) {
    imgs[index]->set_pos(pos_in);
}

void Image_Grid::resize_imgs() {
    #pragma omp parallel for
    for (int i = 0; i < imgs.size(); ++i) {
        imgs[i]->resize();
    }
}

void Image_Grid::set_sorted(bool sorted_in) {
    sorted = sorted_in;
}

void Image_Grid::update(int value) {
    if (!sorted) sort();

    const int old_num = rows*cols;

    if (grid->count() != 0) for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QWidget *img = grid->itemAtPosition(i, j)->widget();
            img->setVisible(false);
            grid->removeWidget(img);
        }
    }

    rows = row_list[value-1];
    cols = col_list[value-1];

    for (int i = 0; i < row_list.back(); ++i) {
        grid->setRowStretch(i, 0);
    }
    for (int i = 0; i < col_list.back(); ++i) {
        grid->setColumnStretch(i, 0);
    }
    for (int i = 0; i < rows; ++i) {
        grid->setRowStretch(i, 1);
    }
    for (int i = 0; i < cols; ++i) {
        grid->setColumnStretch(i, 1);
    }

    const int old_page = last_page;
    last_page = size_list.back()/(rows*cols);

    if (old_page > last_page) {
        page = ceil(page / (double(old_page)/last_page));
    } else if (old_page < last_page) {
        page = page * (last_page/old_page) - (last_page/old_page-1);
    }

    int count = (page-1)*rows*cols;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid->addWidget(imgs[count], i, j);
            imgs[count]->setVisible(true);
            imgs[count]->resize();

            ++count;
        }
    }

    emit done_updating();
}

void Image_Grid::save_images() {
    for (int i = 0; i < imgs.size(); ++i) {
        if (imgs[i]->is_selected()) imgs[i]->save_image();
    }
}

void Image_Grid::deselect_images() {
    #pragma omp parallel for
    for (int i = 0; i < imgs.size(); ++i) {
        imgs[i]->deselect();
    }
}

void Image_Grid::sort() {
    std::sort(imgs.begin(), imgs.end(), less_than_image());

    sorted = true;
}

Image_Label * Image_Grid::get_img(int index) {
    return imgs[index];
}
