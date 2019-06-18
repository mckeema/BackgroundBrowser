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

#include <QtWidgets>

#include "Main_Window.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    if (qgetenv("APPIMAGE") != "") {
        a.setWindowIcon(QIcon(QCoreApplication::applicationDirPath() + QString("/../share/pixmaps/backgroundbrowser.png")));
    } else {
        a.setWindowIcon(QIcon(QCoreApplication::applicationDirPath() + QString("/backgroundbrowser.png")));
    }

    Main_Window w;
    w.show();

    w.resize(w.size().width()+1, w.size().height()+1);
    w.resize(w.size().width()-1, w.size().height()-1);

    return a.exec();
}
