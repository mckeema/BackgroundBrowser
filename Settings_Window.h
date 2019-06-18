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

#ifndef SETTINGS_WINDOW_H
#define SETTINGS_WINDOW_H

#include <QPoint>
#include <QWidget>

class QGridLayout;
class QPoint;
class QSettings;

class Settings_Window : public QWidget {
    Q_OBJECT

    public:
        Settings_Window(QSettings *settings_in, QPoint pos, QWidget *parent = 0);
        ~Settings_Window();
    private slots:
        void set_save_location();
    signals:
        void save_loc_set(QString loc);
    private:
        QSettings *settings;
        QGridLayout *layout;
};

#endif
