#ifndef GRID_SLIDER_H
#define GRID_SLIDER_H

#include <QWidget>

#include <vector>

class QHBoxLayout;
class QLabel;
class QSlider;

class Grid_Slider : public QWidget {
    Q_OBJECT

    public:
        Grid_Slider(std::vector<int> values_in, QWidget *parent);
        ~Grid_Slider();
    private slots:
        void set_value(int value_in);
    signals:
        void valueChanged(int value_out);
    private:
        QHBoxLayout *layout;
        QLabel *label;
        QSlider *slider;
        int value;
        std::vector<int> values;
};

#endif
