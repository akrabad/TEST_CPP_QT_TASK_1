#include "mainwindow.h"

#include "tablecustomwidget.h"
#include "textcustomwidget.h"

#include <QJsonDocument>
#include <QJsonObject>

#define CONF_FILE_PATH "config/conf.json"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    centralwidget = new QFrame(this);



    this->setCentralWidget(centralwidget);

    QMenuBar * menubar = new QMenuBar(this);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 1150, 22));

    this->setMenuBar(menubar);
    this->setWindowTitle("Hello world!");

    QMenu* firstMenu = menuBar()->addMenu(tr("&First Menu"));
    QMenu* secondMenu = menuBar()->addMenu(tr("&Second Menu"));

    QAction * actionExit = new QAction( tr("&Exit"),this);

    QAction * action1 = new QAction( tr("&Action1"),this);
    QAction * action2 = new QAction( tr("&Action2"),this);
    QAction * action3 = new QAction( tr("&Action3"),this);

    actionExit->setText("Exit\t Ctrl-Q");
    actionExit->setShortcut(QKeySequence(Qt::CTRL|Qt::Key_Q));


    connect(actionExit, SIGNAL(triggered()), this, SLOT(closeApp()));

    connect(action1, SIGNAL(triggered()), this, SLOT(setStatusText1()));
    connect(action2, SIGNAL(triggered()), this, SLOT(setStatusText2()));
    connect(action3, SIGNAL(triggered()), this, SLOT(setStatusText3()));

    firstMenu->addAction(actionExit);


    secondMenu->addAction(action1);
    QMenu* subMenu = secondMenu->addMenu(tr("&Sub menu"));
    subMenu-> addAction(action2);
    subMenu-> addAction(action3);

    statusBar = new QStatusBar(this);
    statusBar->setObjectName(QString::fromUtf8("statusbar"));
    this->setStatusBar(statusBar);

    tblWdgt = new TableCustomWidget(this);
    txtWdgt = new TextCustomWidget(statusBar,this);


    QSizePolicy sp_retain = tblWdgt->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    tblWdgt->setSizePolicy(sp_retain);

    menubar->addAction(firstMenu->menuAction());
    menubar->addAction(secondMenu->menuAction());





    btnHideShowStylePanel =  new QPushButton("Hide style panel",this);
    connect(btnHideShowStylePanel, SIGNAL(clicked()), this, SLOT(hideShowStylesPanel()));

    btnHideShowTable =  new QPushButton("Hide table",this);
    connect(btnHideShowTable, SIGNAL(clicked()), this, SLOT(hideShowTablePanel()));

    btnHideShowTextPanel =  new QPushButton("Hide text panel",this);
    connect(btnHideShowTextPanel, SIGNAL(clicked()), this, SLOT(hideShowTextPanel()));

    btnClearTextFields =  new QPushButton("Clear text fields",this);
    connect(btnClearTextFields, SIGNAL(clicked()), this, SLOT(clearTextPanels()));

    btnAddTextFields =  new QPushButton("Add text field",this);
    connect(btnAddTextFields, SIGNAL(clicked()), this, SLOT(addTextPanel()));

    createStylesDock();

    QVBoxLayout * vlayout = new QVBoxLayout(centralwidget);


    QHBoxLayout * hlayout_btns_main = new QHBoxLayout();
    QHBoxLayout * hlayout_main = new QHBoxLayout();

    hlayout_btns_main->addWidget(btnHideShowStylePanel);
    hlayout_btns_main->addWidget(btnHideShowTable);
    hlayout_btns_main->addWidget(btnHideShowTextPanel);
    hlayout_btns_main->addWidget(btnClearTextFields);
    hlayout_btns_main->addWidget(btnAddTextFields);




    hlayout_main->addWidget(tblWdgt);
    hlayout_main->addWidget(txtWdgt);





    vlayout->addLayout(hlayout_btns_main);
    vlayout->addLayout(hlayout_main);



    //  statusBar->showMessage("1");

}

void MainWindow::setStatusText1(){statusBar->showMessage("Action1");}
void MainWindow::setStatusText2(){statusBar->showMessage("Action2");}
void MainWindow::setStatusText3(){statusBar->showMessage("Action3");}



void MainWindow::createStylesDock()
{
    stylesDock = new QDockWidget(tr("Style"),this);

    stylesList = new QListWidget(stylesDock);
    stylesList->addItems(QStringList()
                         << "Grey"
                         << "Red"
                         << "Green"
                         << "Blue");
    stylesDock->setWidget(stylesList);



    QString currentstyle = readConfFile(CONF_FILE_PATH);

    connect(stylesList, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(onchangeStyle(QListWidgetItem*)));

    connect(stylesDock, SIGNAL(visibilityChanged(bool)),this, SLOT(dockWindowClosed(bool)) );

    for(int i = 0; i < stylesList->count(); ++i)
    {
        QListWidgetItem* item = stylesList->item(i);

        if(QString::compare(item->text(), currentstyle, Qt::CaseInsensitive) == 0 )
        {
            stylesList->setCurrentItem(item);

        }
    }

    setStyle(currentstyle);


    stylesDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    this->addDockWidget(Qt::LeftDockWidgetArea,stylesDock);



}

void MainWindow::dockWindowClosed(bool visability)
{
    if(!visability)
    {
        btnHideShowStylePanel-> setText("Show style panel");
    }
    else
    {
        btnHideShowStylePanel->setText("Hide style panel");
    }
}

void MainWindow::hideShowStylesPanel()
{
    if(stylesDock->isHidden())
    {
        btnHideShowStylePanel-> setText("Hide style panel");
        stylesDock->show();
    }
    else
    {
        btnHideShowStylePanel->setText("Show style panel");
        stylesDock->hide();
    }
}

void MainWindow::hideShowTablePanel()
{
    if(tblWdgt->isHidden())
    {
        btnHideShowTable-> setText("Hide table");
        tblWdgt->show();
    }
    else
    {
        btnHideShowTable->setText("Show table");
        tblWdgt->hide();
    }
}

void MainWindow::hideShowTextPanel()
{
    if(txtWdgt->isHidden())
    {
        btnHideShowTextPanel-> setText("Hide text panel");
        txtWdgt->show();
    }
    else
    {
        btnHideShowTextPanel->setText("Show text panel");
        txtWdgt->hide();
    }
}

void MainWindow::addTextPanel()
{
    txtWdgt->addTxtField();
}

void MainWindow::clearTextPanels()
{
    txtWdgt->clearTextPanels();
}



void MainWindow::onchangeStyle(QListWidgetItem* item)
{
    setStyle(item->text());
}

void MainWindow::setStyle(QString styleName)
{
    QString styleNameL = styleName.toLower();

    QFile file("config/"+styleNameL+".stylesheet");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    this->setStyleSheet(file.readAll());
    file.close();

    writeStyleToConfFile("config/conf.json",styleName);
}

QString MainWindow::readConfFile(QString filename)
{
    QString val;
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("style"));
    return value.toString();
}

void MainWindow::writeStyleToConfFile(QString filename, QString styleName)
{
    QString val;
    QFile file(filename);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("style"));

    sett2[QString("style")] = styleName;

    d.setObject(sett2);

    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    file.write(d.toJson());
    file.close();

    //    qDebug()<<sett2.value(QString("style"));

}

void MainWindow::closeApp()
{
    this->close();

}

MainWindow::~MainWindow()
{
    //    delete ui;
}

