#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QDockWidget>
#include <QtGui/QAction>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QListWidget>
#include <QFrame>
#include <QFile>

class TableCustomWidget;
class TextCustomWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:


    QString readConfFile(QString filename);
    void writeStyleToConfFile(QString filename, QString styleName);

    void setStyle(QString styleName);
    void createStylesDock();


    QDockWidget *stylesDock = nullptr;

    QFrame * centralwidget = nullptr;
    QStatusBar* statusBar = nullptr;


    QPushButton* btnHideShowStylePanel = nullptr;
    QPushButton* btnHideShowTable = nullptr;
    QPushButton* btnHideShowTextPanel = nullptr;
    QPushButton* btnClearTextFields = nullptr;
    QPushButton* btnAddTextFields = nullptr;

    TableCustomWidget* tblWdgt = nullptr;
    TextCustomWidget* txtWdgt = nullptr;

    QListWidget * stylesList;

private slots:
    void closeApp();
    void onchangeStyle(QListWidgetItem* item);
    void setStatusText1();
    void setStatusText2();
    void setStatusText3();


    void hideShowStylesPanel();

    void hideShowTextPanel();

    void hideShowTablePanel();

    void addTextPanel();

    void clearTextPanels();

    void dockWindowClosed(bool visability);
};
#endif // MAINWINDOW_H
