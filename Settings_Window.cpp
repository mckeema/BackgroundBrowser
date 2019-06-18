#include "Settings_Window.h"

#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSettings>

Settings_Window::Settings_Window(QSettings *settings_in, QPoint pos, QWidget *parent)
    : QWidget(parent) {
    settings = settings_in;

    layout = new QGridLayout(this);
    
    QLabel *save_loc_label = new QLabel(tr("Save Location:"), this);
    QLineEdit *save_loc_edit = new QLineEdit(this);
    save_loc_edit->setText(settings->value("Download/save_dir").toString());
    QPushButton *save_loc_button = new QPushButton(tr("..."), this);
    layout->addWidget(save_loc_label, 0, 0);
    layout->addWidget(save_loc_edit, 0, 1);
    layout->addWidget(save_loc_button, 0, 2);

    QLabel *apikey_label = new QLabel(tr("Wallhaven API Key:"), this);
    QLineEdit *apikey_edit = new QLineEdit(this);
    apikey_edit->setText(settings->value("API/apikey").toString());
    layout->addWidget(apikey_label, 1, 0);
    layout->addWidget(apikey_edit, 1, 1);

    QPushButton *apply_button = new QPushButton(tr("Apply"), this);
    QPushButton *cancel_button = new QPushButton(tr("Cancel"), this);
    QPushButton *ok_button = new QPushButton(tr("OK"), this);
    layout->addWidget(apply_button, 2, 0);
    layout->addWidget(cancel_button, 2, 1);
    layout->addWidget(ok_button, 2, 2);

    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    layout->setColumnStretch(2, 0);

    setLayout(layout);
    setWindowTitle(tr("Settings"));

    connect(save_loc_button, SIGNAL(released()), this, SLOT(set_save_location()));
    connect(this, &Settings_Window::save_loc_set, this, [save_loc_edit](QString loc){save_loc_edit->setText(loc);});
    connect(apply_button, &QPushButton::released, this, [this,save_loc_edit,apikey_edit](){
        settings->setValue("Download/save_dir", save_loc_edit->text());
        settings->setValue("API/apikey", apikey_edit->text());
    });
    connect(cancel_button, &QPushButton::released, this, &QWidget::close);
    connect(ok_button, &QPushButton::released, this, [this,save_loc_edit,apikey_edit](){
        settings->setValue("Download/save_dir", save_loc_edit->text());
        settings->setValue("API/apikey", apikey_edit->text());
        close();
    });

    move(pos - rect().center()/2);
}

Settings_Window::~Settings_Window() {}

void Settings_Window::set_save_location() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    dialog.setViewMode(QFileDialog::Detail);

    // if (dialog.exec()) settings->setValue("Download/save_dir", dialog.selectedFiles());
    if (dialog.exec()) emit save_loc_set(dialog.selectedFiles()[0]);
}
