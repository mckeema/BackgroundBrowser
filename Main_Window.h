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
        std::vector<int> row_list;
        std::vector<int> col_list;
        std::vector<int> size_list;
};

#endif
