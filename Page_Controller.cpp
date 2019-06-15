#include "Page_Controller.h"

#include <QPushButton>
#include <QHBoxLayout>

Page_Controller::Page_Controller(QWidget *parent)
    : QWidget(parent) {
    layout = new QHBoxLayout(this);
    prev_button = new QPushButton("<", this);
    next_button = new QPushButton(">", this);

    layout->addWidget(prev_button, 0);
    layout->addWidget(next_button, 1);
    layout->setStretch(0, 0);
    layout->setStretch(1, 0);

    setLayout(layout);

    connect(prev_button, &QPushButton::released, this, [this](){emit prev_button_released();});
    connect(next_button, &QPushButton::released, this, [this](){emit next_button_released();});
}

Page_Controller::~Page_Controller() {};
