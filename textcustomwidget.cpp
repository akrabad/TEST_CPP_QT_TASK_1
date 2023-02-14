#include "textcustomwidget.h"




TextField::TextField(int id,QWidget *parent)
    : QWidget(parent)
{

    btnTableX =  new QPushButton("X",this);
    btnTableOK =  new QPushButton("OK",this);
    vlayout_txt_btns = new QVBoxLayout();


    vlayout_txt_btns->addWidget(btnTableX);
    vlayout_txt_btns->addWidget(btnTableOK);

    hlayout_main = new QHBoxLayout(this);

    txted = new QTextEdit(this);
    txted->setText("Text_"+ QString::number(id));
    txted->setStyleSheet("background-color: white;");

    this->id = id;

    hlayout_main->addWidget(txted);
    hlayout_main->addLayout(vlayout_txt_btns);

    hlayout_main->setContentsMargins(1,1,1,1);

    connect(btnTableX,SIGNAL(clicked()),this,SLOT(closeTextFld()));
    connect(btnTableOK,SIGNAL(clicked()),this,SLOT(sendTextToStatus()));

}

int TextField::getId()
{
    return id;
}

void TextField::sendTextToStatus()
{
    emit btnOK_click(txted->toPlainText());
}
void TextField::closeTextFld()
{
    emit btnX_click(id);
}


void TextField::clearTxt()
{
    txted->setText("");
}

TextField::~TextField()
{

}

TextCustomWidget::TextCustomWidget(QStatusBar* statusBar,QWidget *parent)
    : QWidget(parent)
{
    this->statusBar = statusBar;
    vlayout_wdgt = new QVBoxLayout(this);
    vlayout_wdgt->setContentsMargins(1,1,1,1);
    addTxtField();
}

void TextCustomWidget::addTxtField()
{
    TextField* fld = new TextField(txt_fields_id,this);
    txt_fields.push_back(fld);

    vlayout_wdgt->addWidget(fld);
    txt_fields_id++;

    if(statusBar!= nullptr)
    {
        connect(fld,SIGNAL(btnOK_click(QString)),statusBar,SLOT(showMessage(QString)));
    }
    connect(fld,SIGNAL(btnX_click(int)),this,SLOT(remTextPanel(int)));

}

void TextCustomWidget::remTextPanel(int id)
{
    for(auto item=txt_fields.begin();item < txt_fields.end(); item++)
    {
        if ((*item)->getId() == id)
        {
            vlayout_wdgt->removeWidget((*item));
            delete (*item);
            txt_fields.erase(item);
            break;
        }
    }
}

void TextCustomWidget::clearTextPanels()
{
    for(auto item=txt_fields.begin();item < txt_fields.end(); item++)
    {
        (*item)->clearTxt();
    }

}


TextCustomWidget::~TextCustomWidget()
{

}
