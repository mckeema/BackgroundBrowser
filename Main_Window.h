#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <vector>

class QPushButton;
class QNetworkAccessManager;
class QNetworkReply;
class QLabel;
class QSlider;
class QGridLayout;
class QHBoxLayout;
class QString;
class QPixmap;

class Main_Window : public QWidget {
    Q_OBJECT

    public:
        Main_Window(QWidget *parent = 0);
        ~Main_Window();
    private slots:
        void on_button_released();
        void parse_json();
        void resize_func(QLabel *label, int index);
        void save_image(QNetworkReply *reply);
        void set_slider_text(int value);
        void set_num_images(int value);
        void sort_and_refresh();
    protected:
        void resizeEvent(QResizeEvent *e);
    private:
        QPushButton *button_;
        QNetworkAccessManager *nam;
        QNetworkReply *reply;
        std::vector<QLabel *> images;
        std::vector<QPixmap *> files;
        std::vector<int> dl_order;
        QSlider *num_images_slider;
        QLabel *num_images_label;
        QHBoxLayout *main_layout;
        QGridLayout *image_grid;
        bool sorted;
};

#endif
