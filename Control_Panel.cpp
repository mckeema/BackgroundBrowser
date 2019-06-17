#include "Control_Panel.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>

Control_Panel::Control_Panel(QWidget *parent)
    : QWidget(parent) {
    wh_page = 0;

    layout = new QGridLayout(this);

    query_box = new QGroupBox(tr("Query"), this);
    query_edit = new QLineEdit(query_box);
    QVBoxLayout *query_layout = new QVBoxLayout(query_box);
    query_layout->addWidget(query_edit, 0);
    query_box->setLayout(query_layout);
    layout->addWidget(query_box, 0, 0, 1, 2);

    category_box = new QGroupBox(tr("Categories"), this);
    QCheckBox *general_check = new QCheckBox(tr("General"), category_box);
    QCheckBox *anime_check = new QCheckBox(tr("Anime"), category_box);
    QCheckBox *people_check = new QCheckBox(tr("People"), category_box);
    general_check->setChecked(true);
    anime_check->setChecked(true);
    people_check->setChecked(true);
    category_group = new QButtonGroup(category_box);
    category_group->setExclusive(false);
    category_group->addButton(general_check, 0);
    category_group->addButton(anime_check, 1);
    category_group->addButton(people_check, 2);
    QVBoxLayout *category_layout = new QVBoxLayout(category_box);
    category_layout->addWidget(general_check, 0);
    category_layout->addWidget(anime_check, 1);
    category_layout->addWidget(people_check, 2);
    category_box->setLayout(category_layout);
    layout->addWidget(category_box, 1, 0);

    purity_box = new QGroupBox(tr("Purity"), this);
    QCheckBox *sfw_check = new QCheckBox(tr("SFW"), purity_box);
    QCheckBox *sketchy_check = new QCheckBox(tr("Sketchy"), purity_box);
    QCheckBox *nsfw_check = new QCheckBox(tr("NSFW"), purity_box);
    sfw_check->setChecked(true);
    purity_group = new QButtonGroup(purity_box);
    purity_group->setExclusive(false);
    purity_group->addButton(sfw_check, 0);
    purity_group->addButton(sketchy_check, 1);
    purity_group->addButton(nsfw_check, 2);
    QVBoxLayout *purity_layout = new QVBoxLayout(purity_box);
    purity_layout->addWidget(sfw_check, 0);
    purity_layout->addWidget(sketchy_check, 1);
    purity_layout->addWidget(nsfw_check, 2);
    purity_box->setLayout(purity_layout);
    layout->addWidget(purity_box, 1, 1);

    sorting_box = new QGroupBox(tr("Sorting"), this);
    QRadioButton *date_added_button = new QRadioButton(tr("Date Added"), sorting_box);
    date_added_button->setObjectName("date_added");
    QRadioButton *relevance_button = new QRadioButton(tr("Relevance"), sorting_box);
    relevance_button->setObjectName("relevance");
    QRadioButton *random_button = new QRadioButton(tr("Random"), sorting_box);
    random_button->setObjectName("random");
    QRadioButton *views_button = new QRadioButton(tr("Views"), sorting_box);
    views_button->setObjectName("views");
    QRadioButton *favorites_button = new QRadioButton(tr("Favorites"), sorting_box);
    favorites_button->setObjectName("favorites");
    QRadioButton *toplist_button = new QRadioButton(tr("Toplist"), sorting_box);
    toplist_button->setObjectName("toplist");
    date_added_button->setChecked(true);
    sorting_group = new QButtonGroup(sorting_box);
    sorting_group->addButton(date_added_button, 0);
    sorting_group->addButton(relevance_button, 1);
    sorting_group->addButton(random_button, 2);
    sorting_group->addButton(views_button, 3);
    sorting_group->addButton(favorites_button, 4);
    sorting_group->addButton(toplist_button, 5);
    QVBoxLayout *sorting_layout = new QVBoxLayout(sorting_box);
    sorting_layout->addWidget(date_added_button, 0);
    sorting_layout->addWidget(relevance_button, 1);
    sorting_layout->addWidget(random_button, 2);
    sorting_layout->addWidget(views_button, 3);
    sorting_layout->addWidget(favorites_button, 4);
    sorting_layout->addWidget(toplist_button, 5);
    sorting_box->setLayout(sorting_layout);
    layout->addWidget(sorting_box, 2, 0, 3, 1);

    order_box = new QGroupBox(tr("Order"), this);
    QRadioButton *desc_button = new QRadioButton(tr("Descending"), order_box);
    desc_button->setObjectName("desc");
    QRadioButton *asc_button = new QRadioButton(tr("Ascending"), order_box);
    asc_button->setObjectName("asc");
    desc_button->setChecked(true);
    order_group = new QButtonGroup(order_box);
    order_group->addButton(desc_button, 0);
    order_group->addButton(asc_button, 1);
    QVBoxLayout *order_layout = new QVBoxLayout(order_box);
    order_layout->addWidget(desc_button, 0);
    order_layout->addWidget(asc_button, 1);
    order_box->setLayout(order_layout);
    layout->addWidget(order_box, 2, 1);

    topRange_box = new QGroupBox(tr("Top Range"), this);
    QRadioButton *one_day_button = new QRadioButton(tr("1d"), topRange_box);
    one_day_button->setObjectName("1d");
    QRadioButton *three_day_button = new QRadioButton(tr("3d"), topRange_box);
    three_day_button->setObjectName("3d");
    QRadioButton *one_week_button = new QRadioButton(tr("1w"), topRange_box);
    one_week_button->setObjectName("1w");
    QRadioButton *one_month_button = new QRadioButton(tr("1M"), topRange_box);
    one_month_button->setObjectName("1M");
    QRadioButton *three_month_button = new QRadioButton(tr("3M"), topRange_box);
    three_month_button->setObjectName("3M");
    QRadioButton *six_month_button = new QRadioButton(tr("6M"), topRange_box);
    six_month_button->setObjectName("6M");
    QRadioButton *one_year_button = new QRadioButton(tr("1y"), topRange_box);
    one_year_button->setObjectName("1y");
    one_month_button->setChecked(true);
    topRange_group = new QButtonGroup(topRange_box);
    topRange_group->addButton(one_day_button, 0);
    topRange_group->addButton(three_day_button, 1);
    topRange_group->addButton(one_week_button, 2);
    topRange_group->addButton(one_month_button, 3);
    topRange_group->addButton(three_month_button, 4);
    topRange_group->addButton(six_month_button, 5);
    topRange_group->addButton(one_year_button, 6);
    QVBoxLayout *topRange_layout = new QVBoxLayout(topRange_box);
    topRange_layout->addWidget(one_day_button, 0);
    topRange_layout->addWidget(three_day_button, 1);
    topRange_layout->addWidget(one_week_button, 2);
    topRange_layout->addWidget(one_month_button, 3);
    topRange_layout->addWidget(three_month_button, 4);
    topRange_layout->addWidget(six_month_button, 5);
    topRange_layout->addWidget(one_year_button, 6);
    topRange_box->setLayout(topRange_layout);
    layout->addWidget(topRange_box, 6, 0, 3, 1);

    atleast_box = new QGroupBox(tr("At Least"), this);
    atleast_edit = new QLineEdit(atleast_box);
    QVBoxLayout *atleast_layout = new QVBoxLayout(atleast_box);
    atleast_layout->addWidget(atleast_edit, 0);
    atleast_box->setLayout(atleast_layout);
    layout->addWidget(atleast_box, 3, 1);

    resolution_box = new QGroupBox(tr("Resolution"), this);
    resolution_edit = new QLineEdit(resolution_box);
    QVBoxLayout *resolution_layout = new QVBoxLayout(resolution_box);
    resolution_layout->addWidget(resolution_edit, 0);
    resolution_box->setLayout(resolution_layout);
    layout->addWidget(resolution_box, 4, 1);

    ratio_box = new QGroupBox(tr("Ratio"), this);
    ratio_edit = new QLineEdit(ratio_box);
    QVBoxLayout *ratio_layout = new QVBoxLayout(ratio_box);
    ratio_layout->addWidget(ratio_edit, 0);
    ratio_box->setLayout(ratio_layout);
    layout->addWidget(ratio_box, 6, 1);

    color_box = new QGroupBox(tr("Color"), this);
    color_edit = new QLineEdit(color_box);
    QVBoxLayout *color_layout = new QVBoxLayout(color_box);
    color_layout->addWidget(color_edit, 0);
    color_box->setLayout(color_layout);
    layout->addWidget(color_box, 7, 1);

    page_box = new QGroupBox(tr("Page"), this);
    page_edit = new QLineEdit(page_box);
    page_edit->setText(QString::number(wh_page));
    QVBoxLayout *page_layout = new QVBoxLayout(page_box);
    page_layout->addWidget(page_edit, 0);
    page_box->setLayout(page_layout);
    connect(page_edit, SIGNAL(textEdited(QString)), this, SLOT(set_page(QString)));
    layout->addWidget(page_box, 8, 1);

    search_button = new QPushButton(tr("Search"), this);
    connect(search_button, SIGNAL(released()), this, SLOT(construct_url()));
    layout->addWidget(search_button, 9, 0, 1, 2);

    setLayout(layout);
}

Control_Panel::~Control_Panel() {};

int Control_Panel::get_page() const {
    return wh_page;
}

void Control_Panel::set_page(int value) {
    wh_page = value;
    page_edit->setText(QString::number(wh_page));
}

void Control_Panel::set_page(QString value) {
    wh_page = value.toInt();
    page_edit->setText(QString::number(wh_page));
}

void Control_Panel::construct_url() {
    QString url_str = "https://wallhaven.cc/api/v1/search";

    if (!query_edit->text().isEmpty()) {
        url_str += "?q=" + query_edit->text();
        url_str += "&categories=";
    } else {
        url_str += "?categories=";
    }

    for (int i = 0; i < category_group->buttons().size(); ++i) {
        if (category_group->button(i)->isChecked()) {
            url_str += "1";
        } else {
            url_str += "0";
        }
    }
    
    url_str += "&purity=";
    for (int i = 0; i < purity_group->buttons().size(); ++i) {
        if (purity_group->button(i)->isChecked()) {
            url_str += "1";
        } else {
            url_str += "0";
        }
    }

    url_str += "&sorting=";
    for (int i = 0; i < sorting_group->buttons().size(); ++i) {
        if (sorting_group->button(i)->isChecked()) {
            url_str += sorting_group->button(i)->objectName();
            break;
        }
    }

    url_str += "&order=";
    for (int i = 0; i < order_group->buttons().size(); ++i) {
        if (order_group->button(i)->isChecked()) {
            url_str += order_group->button(i)->objectName();
            break;
        }
    }

    if (url_str.contains("toplist")) {
        url_str += "&topRange=";
        for (int i = 0; i < topRange_group->buttons().size(); ++i) {
            if (topRange_group->button(i)->isChecked()) {
                url_str += topRange_group->button(i)->objectName();
                break;
            }
        }
    }

    if (!atleast_edit->text().isEmpty()) {
        url_str += "&atleast=" + atleast_edit->text();
    }

    if (!resolution_edit->text().isEmpty()) {
        url_str += "&resolutions=" + resolution_edit->text();
    }

    if (!ratio_edit->text().isEmpty()) {
        url_str += "&ratios=" + ratio_edit->text();
    }

    if (!color_edit->text().isEmpty()) {
        url_str += "&colors=" + color_edit->text();
    }

    url_str += "&page=" + page_edit->text();

    emit url_ready(QUrl(url_str));
}
