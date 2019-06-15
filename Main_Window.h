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
    protected:
        void resizeEvent(QResizeEvent *e);
    private:
        QPushButton *button_;
        QGridLayout *main_layout;
        Image_Grid *grid;
        Grid_Slider *slider;
        std::vector<int> row_list;
        std::vector<int> col_list;
        std::vector<int> size_list;
};

#endif
