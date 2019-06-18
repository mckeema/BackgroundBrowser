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
