#include "Image_Label.h"

#include <QCheckBox>
#include <QDir>
#include <QLabel>

Image_Label::Image_Label(QWidget *parent)
    : QLabel(parent) {
    pos = 0;
    selected = false;
    id = "placeholder";

    check = new QCheckBox(this);

    setScaledContents(false);
    setMinimumSize(1, 1);

    //orig_pixmap = QPixmap(filename);

    //setPixmap(orig_pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

Image_Label::Image_Label(QImage *img, QWidget *parent)
    : QLabel(parent) {
    pos = 0;
    selected = false;
    id = "placeholder";

    check = new QCheckBox(this);

    setScaledContents(false);
    setMinimumSize(1, 1);

    orig_pixmap.convertFromImage(*img);

    setPixmap(orig_pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void Image_Label::set_img(QString filename, QString id_in) {
    orig_pixmap = QPixmap(filename);
    id = id_in;
}

void Image_Label::set_img(QImage img, QString id_in) {
    orig_pixmap.convertFromImage(img);
    id = id_in;
}

void Image_Label::resize() {
    double ratio = double(width())/double(height());

    if (width() <= height()) {
        setPixmap(orig_pixmap.scaled(width(), int(width()/ratio), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        setPixmap(orig_pixmap.scaled(int(height()*ratio), height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

int Image_Label::get_pos() const {
    return pos;
}

void Image_Label::set_pos(int value) {
    pos = value;
}

void Image_Label::save_image() {
    orig_pixmap.save(id + ".jpg", 0, 100);

    selected = false;
    check->setChecked(selected);
}

bool Image_Label::is_selected() {
    return selected;
}

void Image_Label::deselect() {
    selected = false;
    check->setChecked(selected);
}

void Image_Label::mousePressEvent(QMouseEvent *event) {
    selected = !selected;
    check->setChecked(selected);
}
