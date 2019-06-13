#include <algorithm>
#include <cmath>
#include <QtWidgets>
#include <QtNetwork>
#include "Main_Window.h"

const int MAX_IMAGES_PER_DIM = 4;

struct less_than_image {
    inline bool operator()(const std::pair<QPixmap *, int> &a, const std::pair<QPixmap *, int> &b) {
        return a.second < b.second;
    }
};

Main_Window::Main_Window(QWidget *parent)
    : QWidget(parent) {
    sorted = false;

    button_ = new QPushButton(tr("test"));
    nam = new QNetworkAccessManager(this);
    num_images_slider = new QSlider(Qt::Horizontal);
    num_images_label = new QLabel();

    image_grid = new QGridLayout();

    for (int i = 0; i < MAX_IMAGES_PER_DIM*MAX_IMAGES_PER_DIM; ++i) {
        QLabel *image = new QLabel();
        images.push_back(image);
        files.push_back(new QPixmap("placeholder.jpg"));
        dl_order.push_back(i);
    }

    image_grid->addWidget(images[0], 0, 0);
    images[0]->setScaledContents(false);
    images[0]->setMinimumSize(1,1);
    QPixmap p(*files[0]);
    images[0]->setPixmap(p.scaled(images[0]->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    num_images_slider->setTickPosition(QSlider::TicksBothSides);
    num_images_slider->setTickInterval(1);
    num_images_slider->setSingleStep(1);
    num_images_slider->setRange(1, MAX_IMAGES_PER_DIM);

    num_images_label->setText(QString::number(num_images_slider->value()));

    QGridLayout *left_layout = new QGridLayout();
    left_layout->addWidget(button_, 0, 0, 1, 2);
    left_layout->addWidget(num_images_label, 1, 0);
    left_layout->addWidget(num_images_slider, 1, 1);

    main_layout = new QHBoxLayout();
    main_layout->addLayout(left_layout, 0);
    main_layout->addLayout(image_grid, 1);
    setLayout(main_layout);
    setWindowTitle(tr("HONK"));

    connect(button_, SIGNAL(released()), this, SLOT(on_button_released()));
    connect(num_images_slider, SIGNAL(valueChanged(int)), this, SLOT(set_slider_text(int)));
    connect(num_images_slider, SIGNAL(valueChanged(int)), this, SLOT(set_num_images(int)));
}

Main_Window::~Main_Window() {
    //delete button_;
    //delete nam;
    //delete reply;
    //delete image;
}

void Main_Window::on_button_released() {
    sorted = false;

    QNetworkRequest request;
    request.setUrl(QUrl("https://wallhaven.cc/api/v1/search?sorting=toplist"));
    request.setRawHeader("User-Agent", "BackgroundBrowser");
    
    reply = nam->get(request);

    connect(reply, SIGNAL(finished()), this, SLOT(parse_json()));
}

void Main_Window::parse_json() {
    QByteArray reply_data = reply->readAll();
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "read error";
        exit(1);
    }
    if (reply_data.isEmpty()) {
        qDebug() << "reply empty";
        exit(2);
    }

    QJsonDocument reply_doc = QJsonDocument::fromJson(reply_data);
    if (!reply_doc.isObject()) {
        qDebug() << "not object";
        exit(3);
    }

    QJsonObject reply_obj = reply_doc.object();
    QJsonArray wh_data = reply_obj.value("data").toArray();

    for (int i = 0, size = files.size(); i < size; ++i) {
        files.pop_back();
    }

    for (int i = 0, size = dl_order.size(); i < size; ++i) {
        dl_order.pop_back();
    }

    int i = 0;
    for (const QJsonValue &v : wh_data) {
        if (i >= MAX_IMAGES_PER_DIM*MAX_IMAGES_PER_DIM) {
            break;
        }

        QNetworkAccessManager *nam_img = new QNetworkAccessManager();
        nam_img->get(QNetworkRequest(v.toObject().value("path").toString()));
        connect(nam_img, &QNetworkAccessManager::finished, this, [this,i](){dl_order.push_back(i);});
        connect(nam_img, SIGNAL(finished(QNetworkReply *)), this, SLOT(save_image(QNetworkReply *)));
        connect(nam_img, SIGNAL(finished(QNetworkReply *)), this, SLOT(sort_and_refresh()));

        ++i;
    }
}

void Main_Window::save_image(QNetworkReply *reply) {
    QImageReader img_reader(reply);
    QPixmap *img = new QPixmap();
    img->convertFromImage(img_reader.read());

    files.push_back(img);
}

void Main_Window::sort_and_refresh() {
    static int i = 0;
    ++i;
    if (i < MAX_IMAGES_PER_DIM*MAX_IMAGES_PER_DIM) {
        return;
    }

    i = 0;

    set_num_images(sqrt(image_grid->count()));
}

void Main_Window::resize_func(QLabel *label, int index) {
    QPixmap p(*files[index]);

    double ratio = double(label->width())/double(label->height());

    if (label->width() <= label->height()) {
        label->setPixmap(p.scaled(label->width(), int(label->width()/ratio), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        label->setPixmap(p.scaled(int(label->height()*ratio), label->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void Main_Window::resizeEvent(QResizeEvent *e) {
    #pragma omp parallel for
    for (int i = 0; i < image_grid->count(); ++i) {
        resize_func(images[i], i);
    }
}

void Main_Window::set_slider_text(int value) {
    num_images_label->setText(QString::number(value));
}

void Main_Window::set_num_images(int value) {
    if (!sorted) {
        std::vector<std::pair<QPixmap *, int> > pairs;
        for (int i = 0; i < files.size(); ++i) {
            std::pair<QPixmap *, int> p = {files[i], dl_order[i]};
            pairs.push_back(p);
        }

        std::sort(pairs.begin(), pairs.end(), less_than_image());

        for (int i = 0; i < pairs.size(); ++i) {
            files[i] = pairs[i].first;
        }

        sorted = true;
    }

    // count is width x height, so sqrt gets width/height
    const int &dim = sqrt(image_grid->count());

    // if num_images is decreasing, remove all widgets from grid
    if (value < dim) {
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                image_grid->itemAtPosition(i, j)->widget()->setVisible(false);
                image_grid->removeWidget(image_grid->itemAtPosition(i, j)->widget());
            }
        }
    }

    // sets all images to be same size
    for (int i = 0; i < MAX_IMAGES_PER_DIM; ++i) {
        image_grid->setRowStretch(i, 0);
        image_grid->setColumnStretch(i, 0);
    }

    for (int i = 0; i < value; ++i) {
        image_grid->setRowStretch(i, 1);
        image_grid->setColumnStretch(i, 1);
    }

    // add images to grid
    int count = 0;
    for (int i = 0; i < value; ++i) {
        for (int j = 0; j < value; ++j) {
            image_grid->addWidget(images[count], i, j);
            images[count]->setScaledContents(false);
            images[count]->setMinimumSize(1,1);
            images[count]->setVisible(true);
            QPixmap p(*files[count]);
            images[count]->setPixmap(p.scaled(images[count]->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

            ++count;
        }
    }

    // suboptimal method to force images to be correct size
    resize(size().width()+1, size().height()+1);
    resize(size().width()-1, size().height()-1);
}
