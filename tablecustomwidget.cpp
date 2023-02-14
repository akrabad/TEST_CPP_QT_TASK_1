#include "tablecustomwidget.h"

#include <QHeaderView>

TableCustomWidget::TableCustomWidget(QWidget *parent)
    : QWidget(parent)
{
    btnTableAddLine =  new QPushButton("Add line",this);
    btnTableDeleteLine =  new QPushButton("Delete line",this);


    tblwidget = new QTableWidget(0,3,this);
    QStringList headers;
    headers << "Id" << "Parameter" << "Value";
    tblwidget->setColumnCount(3);
    tblwidget->setHorizontalHeaderLabels(headers);
    tblwidget->verticalHeader()->setVisible(false);
    tblwidget->setColumnWidth(0, 100);
    tblwidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    tblwidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    tblwidget->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);

    tblwidget->setStyleSheet("background-color: white;");

    vlayout_tbl = new QVBoxLayout(this);
    this->setLayout(vlayout_tbl);
    hlayout_tbl_btns = new QHBoxLayout();

    hlayout_tbl_btns->addWidget(btnTableAddLine);
    hlayout_tbl_btns->addWidget(btnTableDeleteLine);


    vlayout_tbl->addWidget(tblwidget);
    vlayout_tbl->addLayout(hlayout_tbl_btns);
    vlayout_tbl->setContentsMargins(1,1,1,1);

    connect(btnTableAddLine,SIGNAL(clicked()),this,SLOT(addLine()));
    connect(btnTableDeleteLine,SIGNAL(clicked()),this,SLOT(deleteLine()));
}

void TableCustomWidget::addLine()
{

    int rcnt = tblwidget->rowCount();
    tblwidget->setRowCount(rcnt+1);
    tblwidget->setItem(rcnt, 0, new QTableWidgetItem("Id_"+QString::number(rcnt+1)));
    tblwidget->setItem(rcnt, 1, new QTableWidgetItem("Parameter_"+QString::number(rcnt+1)));
    tblwidget->setItem(rcnt, 2, new QTableWidgetItem(QString::number(rcnt+1)+QString::number(rcnt+1)+QString::number(rcnt+1)));
}


void TableCustomWidget::deleteLine()
{

    int rcnt = tblwidget->rowCount();
    if(rcnt>0)
        tblwidget->removeRow(rcnt-1);

}


TableCustomWidget::~TableCustomWidget()
{

}
