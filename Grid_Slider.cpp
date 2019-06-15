#include "Grid_Slider.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>

Grid_Slider::Grid_Slider(std::vector<int> values_in, QWidget *parent)
    : QWidget(parent) {
    values = values_in;
    value = values.front();

    layout = new QHBoxLayout(this);
    label = new QLabel(this);
    slider = new QSlider(Qt::Horizontal, this);

    label->setText(QString::number(values.front()));

    slider->setTickPosition(QSlider::TicksBothSides);
    slider->setTickInterval(1);
    slider->setSingleStep(1);
    slider->setRange(1, values.size());

    layout->addWidget(label, 0);
    layout->addWidget(slider, 1);

    setLayout(layout);

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(set_value(int)));
}

Grid_Slider::~Grid_Slider() {};

void Grid_Slider::set_value(int value_in) {
    value = values[value_in-1];

    label->setText(QString::number(value));

    emit valueChanged(slider->value());
}
