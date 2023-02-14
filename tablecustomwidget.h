#ifndef TABLECUSTOMWIDGET_H
#define TABLECUSTOMWIDGET_H

#include <QWidget>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>

class TableCustomWidget : public QWidget
{
    Q_OBJECT

public:
    TableCustomWidget(QWidget *parent = nullptr);
    ~TableCustomWidget();

private:
    QVBoxLayout *vlayout_tbl = nullptr;
    QHBoxLayout *hlayout_tbl_btns = nullptr;


    QTableWidget * tblwidget = nullptr;

    QPushButton* btnTableAddLine = nullptr;
    QPushButton* btnTableDeleteLine = nullptr;

private slots:
    void addLine();
    void deleteLine();
    \
};
#endif // TABLEWIDGET_H
