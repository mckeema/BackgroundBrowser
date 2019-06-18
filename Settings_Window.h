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
