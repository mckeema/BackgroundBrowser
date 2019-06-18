#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QUrl>
#include <QWidget>
#include <vector>

class QCloseEvent;
class QGridLayout;
class QMenuBar;
class QNetworkReply;
class QPushButton;
class QResizeEvent;
class QSettings;

class Control_Panel;
class Image_Grid;
class Grid_Slider;
class Page_Controller;
class Settings_Window;

class Main_Window : public QWidget {
    Q_OBJECT

    public:
        Main_Window(QWidget *parent = 0);
        ~Main_Window();
    private slots:
        void on_button_released(QUrl url);
        void parse_json(QNetworkReply *reply);
        void refresh();
        void set_imgs(int index, QNetworkReply *reply, QString id);
        void prev_button_released();
        void next_button_released();
        void open_settings_window();
    protected:
        void resizeEvent(QResizeEvent *e);
        void closeEvent(QCloseEvent *e);
    private:
        QSettings *settings;
        QString settings_filename;
        QMenuBar *menubar;
        QPushButton *save_button;
        QGridLayout *main_layout;
        Control_Panel *controls;
        Image_Grid *grid;
        Grid_Slider *slider;
        Page_Controller *controller;
        //Settings_Window *settings_window;
        std::vector<int> row_list;
        std::vector<int> col_list;
        std::vector<int> size_list;
};

#endif
