#include <QtWidgets>
#include <QtNetwork>
#include "Main_Window.h"
#include "Image_Grid.h"
#include "Image_Label.h"
#include "Grid_Slider.h"

Main_Window::Main_Window(QWidget *parent)
    : QWidget(parent) {
    row_list = {3, 4, 6};
    col_list = {2, 3, 4};
    size_list = {6, 12, 24};

    button_ = new QPushButton(tr("Next"), this);
    grid = new Image_Grid(row_list, col_list, size_list, QString("placeholder.jpg"), this);
    slider = new Grid_Slider(size_list, this);

    QVBoxLayout *left_layout = new QVBoxLayout();
    left_layout->addWidget(button_, 0);
    left_layout->addWidget(slider, 1);

    main_layout = new QGridLayout(this);
    main_layout->addLayout(left_layout, 0, 0);
    main_layout->addWidget(grid, 0, 1);
    main_layout->setColumnStretch(0, 0);
    main_layout->setColumnStretch(1, 1);
    setLayout(main_layout);
    setWindowTitle(tr("BackgroundBrowser"));

    connect(button_, SIGNAL(released()), this, SLOT(on_button_released()));
    connect(slider, SIGNAL(valueChanged(int)), grid, SLOT(update(int)));
    connect(grid, &Image_Grid::done_updating, this, [this](){resize(size().width()+1, size().height()+1);
                                                             resize(size().width()-1, size().height()-1);});
}

Main_Window::~Main_Window() {
    //delete button_;
    //delete nam;
    //delete reply;
    //delete image;
}

void Main_Window::on_button_released() {
    QNetworkAccessManager *nam = new QNetworkAccessManager(this);

    QNetworkRequest request;
    request.setUrl(QUrl("https://wallhaven.cc/api/v1/search?sorting=toplist"));
    request.setRawHeader("User-Agent", "BackgroundBrowser");
    
    nam->get(request);

    connect(nam, SIGNAL(finished(QNetworkReply *)), this, SLOT(parse_json(QNetworkReply *)));
    connect(nam, &QNetworkAccessManager::finished, this, [nam](){nam->deleteLater();});
}

void Main_Window::parse_json(QNetworkReply *reply) {
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

    int i = 0;
    for (const QJsonValue &v : wh_data) {
        QNetworkAccessManager *nam_img = new QNetworkAccessManager(this);

        QNetworkReply *reply = nam_img->get(QNetworkRequest(v.toObject().value("path").toString()));

        connect(reply, &QNetworkReply::finished, this, [this,i,reply](){grid->set_pos(i, i); set_imgs(i, reply);});
        connect(nam_img, &QNetworkAccessManager::finished, this, [nam_img](){nam_img->deleteLater();});

        ++i;
    }
}

void Main_Window::refresh() {
    static int i = 0;
    ++i;
    if (i < size_list.back()) return;
    i = 0;

    grid->update(grid->get_size());
}

void Main_Window::set_imgs(int index, QNetworkReply *reply) {
    QImageReader img_reader(reply);
    QImage img = img_reader.read();
    grid->set_img(index, img);
}

void Main_Window::resizeEvent(QResizeEvent *e) {
    grid->resize_imgs();
}
