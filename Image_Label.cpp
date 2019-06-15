#include "Image_Label.h"

#include <QLabel>

Image_Label::Image_Label(QString filename, QWidget *parent)
    : QLabel(parent) {
    pos = 0;

    setScaledContents(false);
    setMinimumSize(1, 1);

    orig_pixmap = QPixmap(filename);

    setPixmap(orig_pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

Image_Label::Image_Label(QImage *img, QWidget *parent)
    : QLabel(parent) {
    pos = 0;

    setScaledContents(false);
    setMinimumSize(1, 1);

    orig_pixmap.convertFromImage(*img);

    setPixmap(orig_pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void Image_Label::set_img(QString filename) {
    orig_pixmap = QPixmap(filename);

    //setPixmap(orig_pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void Image_Label::set_img(QImage img) {
    orig_pixmap.convertFromImage(img);

    //setPixmap(orig_pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
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
