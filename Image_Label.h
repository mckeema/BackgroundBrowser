#ifndef IMAGE_LABEL_H
#define IMAGE_LABEL_H

#include <QImage>
#include <QPixmap>
#include <QString>
#include <QLabel>

class QLabel;
class QWidget;

class Image_Label : public QLabel {
    Q_OBJECT

    public:
        Image_Label(QString filename, QWidget *parent);
        Image_Label(QImage *img, QWidget *parent);

        void set_img(QString filename);
        void set_img(QImage img);
        void resize();
        int get_pos() const;
        void set_pos(int value);
    private:
        QPixmap orig_pixmap;
        int pos;
};

#endif
