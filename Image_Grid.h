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

#ifndef IMAGE_GRID_H
#define IMAGE_GRID_H

#include <QImage>
#include <QString>
#include <QWidget>

#include <vector>

#include "Image_Label.h"

class QGridLayout;
class QSettings;

class Image_Grid : public QWidget {
    Q_OBJECT

    public:
        Image_Grid(std::vector<int> row_list_in, std::vector<int> col_list_in, std::vector<int> size_list_in, QSettings *settings, QWidget *parent);
        ~Image_Grid();

        int get_rows() const;
        int get_cols() const;
        int get_size() const;
        int get_size_index(int size_in);
        int get_page() const;
        bool on_last_page() const;
        void set_img(int index, QString filename, QString id);
        void set_img(int index, QImage img, QString id);
        void set_page(int page_in);
        void set_to_last_page();
        void set_pos(int index, int pos_in);
        void resize_imgs();
        void set_sorted(bool sorted_in);
    public slots:
        void update(int value);
        void save_images();
        void deselect_images();
    signals:
        void done_updating();
        void similar_pressed(QString query);
    private:
        int rows;
        int cols;
        std::vector<int> row_list;
        std::vector<int> col_list;
        std::vector<int> size_list;
        int page;
        int last_page;
        bool sorted;
        std::vector<Image_Label *> imgs;
        QGridLayout *grid;

        void set_rows(int rows_in);
        void set_cols(int cols_in);
        void sort();
};

#endif
