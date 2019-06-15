#ifndef PAGE_CONTROLLER_H
#define PAGE_CONTROLLER_H

#include <QWidget>

class QHBoxLayout;
class QPushButton;

class Page_Controller : public QWidget {
    Q_OBJECT

    public:
        Page_Controller(QWidget *parent);
        ~Page_Controller();
    signals:
        void prev_button_released();
        void next_button_released();
    private:
        QHBoxLayout *layout;
        QPushButton *prev_button;
        QPushButton *next_button;
};

#endif
