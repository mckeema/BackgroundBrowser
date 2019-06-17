#include "Main_Window.h"

#include <QtNetwork>
#include <QtWidgets>

#include "Control_Panel.h"
#include "Grid_Slider.h"
#include "Image_Grid.h"
#include "Image_Label.h"
#include "Page_Controller.h"

Main_Window::Main_Window(QWidget *parent)
    : QWidget(parent) {
    row_list = {3, 4, 6};
    col_list = {2, 3, 4};
    size_list = {6, 12, 24};

    grid = new Image_Grid(row_list, col_list, size_list, QString("placeholder.jpg"), this);
    slider = new Grid_Slider(size_list, this);
    controller = new Page_Controller(this);
    controls = new Control_Panel(this);
    save_button = new QPushButton(tr("Save Selected"), this);
    menubar = new QMenuBar(this);

    QMenu *file_menu = menubar->addMenu(tr("File"));
    QAction *exit_button = file_menu->addAction(tr("Exit"));
    connect(exit_button, &QAction::triggered, this, &QWidget::close);

    QMenu *edit_menu = menubar->addMenu(tr("Edit"));
    QAction *settings_button = edit_menu->addAction(tr("Settings"));

    main_layout = new QGridLayout(this);
    main_layout->setMenuBar(menubar);
    main_layout->addWidget(controls, 0, 0, 2, 1);
    main_layout->addWidget(grid, 0, 1, 1, 3);
    main_layout->addWidget(controller, 1, 2);
    main_layout->addWidget(slider, 1, 1);
    main_layout->addWidget(save_button, 1, 3);
    main_layout->setColumnStretch(0, 0);
    main_layout->setColumnStretch(1, 1);
    main_layout->setColumnStretch(2, 2);
    main_layout->setColumnStretch(3, 1);
    main_layout->setRowStretch(0, 1);
    main_layout->setRowStretch(1, 0);
    setLayout(main_layout);
    setWindowTitle(tr("BackgroundBrowser"));

    connect(controls, SIGNAL(url_ready(QUrl)), this, SLOT(on_button_released(QUrl)));
    connect(slider, SIGNAL(valueChanged(int)), grid, SLOT(update(int)));
    connect(grid, &Image_Grid::done_updating, this, [this](){resize(size().width()+1, size().height()+1);
                                                             resize(size().width()-1, size().height()-1);});
    connect(controller, SIGNAL(prev_button_released()), this, SLOT(prev_button_released()));
    connect(controller, SIGNAL(next_button_released()), this, SLOT(next_button_released()));
    connect(save_button, SIGNAL(released()), grid, SLOT(save_images()));
}

Main_Window::~Main_Window() {}

void Main_Window::on_button_released(QUrl url) {
    QNetworkAccessManager *nam = new QNetworkAccessManager(this);

    QNetworkRequest request;
    request.setUrl(url);
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
        QString *id = new QString(v.toObject().value("id").toString());

        connect(reply, &QNetworkReply::finished, this, [this,i,reply,id](){grid->set_pos(i, i); set_imgs(i, reply, *id);});
        connect(nam_img, &QNetworkAccessManager::finished, this, [nam_img](){nam_img->deleteLater();});
        connect(reply, SIGNAL(finished()), this, SLOT(refresh()));

        ++i;
    }
}

void Main_Window::refresh() {
    static int i = 0;
    ++i;
    if (i < size_list.back()) return;
    i = 0;

    grid->update(grid->get_size_index(grid->get_size()));
}

void Main_Window::set_imgs(int index, QNetworkReply *reply, QString id) {
    QImageReader img_reader(reply);
    QImage img = img_reader.read();
    grid->set_img(index, img, id);
}

void Main_Window::prev_button_released() {
    if (controls->get_page() > 1 && grid->get_page() == 1) {
        grid->set_to_last_page();
        controls->set_page(controls->get_page()-1);

        controls->construct_url();
    } else if (grid->get_page() != 1) {
        grid->set_page(grid->get_page()-1);

        grid->update(grid->get_size_index(grid->get_size()));
    }
}

void Main_Window::next_button_released() {
    if (grid->on_last_page()) {
        grid->set_page(1);
        controls->set_page(controls->get_page()+1);

        controls->construct_url();
    } else {
        grid->set_page(grid->get_page()+1);

        grid->update(grid->get_size_index(grid->get_size()));
    }   
}

void Main_Window::resizeEvent(QResizeEvent *e) {
    grid->resize_imgs();
}
