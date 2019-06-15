#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <vector>

class QNetworkReply;
class QPushButton;
class QHBoxLayout;
class QGridLayout;
class QResizeEvent;

class Image_Grid;
class Grid_Slider;
class Page_Controller;

class Main_Window : public QWidget {
    Q_OBJECT

    public:
        Main_Window(QWidget *parent = 0);
        ~Main_Window();
    private slots:
        void on_button_released();
        void parse_json(QNetworkReply *reply);
        void refresh();
        void set_imgs(int index, QNetworkReply *reply);
        void prev_button_released();
        void next_button_released();
    protected:
        void resizeEvent(QResizeEvent *e);
    private:
        QPushButton *button_;
        QGridLayout *main_layout;
        Image_Grid *grid;
        Grid_Slider *slider;
        Page_Controller *controller;
        std::vector<int> row_list;
        std::vector<int> col_list;
        std::vector<int> size_list;
        int wh_page;
};

#endif
