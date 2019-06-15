#ifndef IMAGE_GRID_H
#define IMAGE_GRID_H

#include <QImage>
#include <QString>
#include <QWidget>

#include <vector>

#include "Image_Label.h"

class QGridLayout;

class Image_Grid : public QWidget {
    Q_OBJECT

    public:
        Image_Grid(std::vector<int> row_list_in, std::vector<int> col_list_in, std::vector<int> size_list_in, QString filename, QWidget *parent);
        ~Image_Grid();

        int get_rows() const;
        int get_cols() const;
        int get_size() const;
        int get_size_index(int size_in);
        int get_page() const;
        bool on_last_page() const;
        void set_img(int index, QString filename);
        void set_img(int index, QImage img);
        void set_page(int page_in);
        void set_to_last_page();
        void set_pos(int index, int pos_in);
        void resize_imgs();
    public slots:
        void update(int value);
    signals:
        void done_updating();
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
