#ifndef CONTROL_PANEL_H
#define CONTROL_PANEL_H

#include <QUrl>
#include <QWidget>

class QButtonGroup;
class QGridLayout;
class QGroupBox;
class QLineEdit;
class QPushButton;

class Control_Panel : public QWidget{
    Q_OBJECT

    public:
        Control_Panel(QWidget *parent);
        ~Control_Panel();

        int get_page() const;
        void set_page(int value);
    public slots:
        void construct_url();
        void set_page(QString value);
    signals:
        void url_ready(QUrl url);
    private:
        QGridLayout *layout;
        QGroupBox *query_box;
        QLineEdit *query_edit;
        QGroupBox *category_box;
        QButtonGroup *category_group;
        QGroupBox *purity_box;
        QButtonGroup *purity_group;
        QGroupBox *sorting_box;
        QButtonGroup *sorting_group;
        QGroupBox *order_box;
        QButtonGroup *order_group;
        QGroupBox *topRange_box;
        QButtonGroup *topRange_group;
        QGroupBox *atleast_box;
        QLineEdit *atleast_edit;
        QGroupBox *resolution_box;
        QLineEdit *resolution_edit;
        QGroupBox *ratio_box;
        QLineEdit *ratio_edit;
        QGroupBox *color_box;
        QLineEdit *color_edit;
        QGroupBox *page_box;
        QLineEdit *page_edit;
        QPushButton *search_button;
        QUrl url;
        int wh_page;
};

#endif
