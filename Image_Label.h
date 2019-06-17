#ifndef IMAGE_LABEL_H
#define IMAGE_LABEL_H

#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QString>

class QCheckBox;
class QLabel;
class QMouseEvent;
class QWidget;

class Image_Label : public QLabel {
    Q_OBJECT

    public:
        Image_Label(QString filename, QWidget *parent);
        Image_Label(QImage *img, QWidget *parent);

        void set_img(QString filename, QString id_in);
        void set_img(QImage img, QString id_in);
        void resize();
        int get_pos() const;
        void set_pos(int value);
        void save_image();
        bool is_selected();
    protected:
        void mousePressEvent(QMouseEvent *event);
    private:
        QPixmap orig_pixmap;
        QCheckBox *check;
        int pos;
        bool selected;
        QString id;
};

#endif
