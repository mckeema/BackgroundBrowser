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

#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H

#include <QUrl>
#include <QWidget>

class QButtonGroup;
class QGridLayout;
class QGroupBox;
class QLineEdit;
class QPushButton;

class Control_Panel : public QWidget{
    Q_OBJECT

    public:
        Control_Panel(QWidget *parent);
        ~Control_Panel();

        int get_page() const;
        void set_page(int value);
    public slots:
        void construct_url();
        void set_page(QString value);
    signals:
        void url_ready(QUrl url);
    private:
        QGridLayout *layout;
        QGroupBox *query_box;
        QLineEdit *query_edit;
        QGroupBox *category_box;
        QButtonGroup *category_group;
        QGroupBox *purity_box;
        QButtonGroup *purity_group;
        QGroupBox *sorting_box;
        QButtonGroup *sorting_group;
        QGroupBox *order_box;
        QButtonGroup *order_group;
        QGroupBox *topRange_box;
        QButtonGroup *topRange_group;
        QGroupBox *atleast_box;
        QLineEdit *atleast_edit;
        QGroupBox *resolution_box;
        QLineEdit *resolution_edit;
        QGroupBox *ratio_box;
        QLineEdit *ratio_edit;
        QGroupBox *color_box;
        QLineEdit *color_edit;
        QGroupBox *page_box;
        QLineEdit *page_edit;
        QPushButton *search_button;
        QUrl url;
        int wh_page;
};

#endif
