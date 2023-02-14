#ifndef TEXTCUSTOMWIDGET_H
#define TEXTCUSTOMWIDGET_H

#include <QWidget>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QVector>
#include <QStatusBar>

class TextField : public QWidget
{
    Q_OBJECT

public:
    TextField(int id, QWidget *parent = nullptr);

    ~TextField();

    void clearTxt();
    int getId();
private:
    QVBoxLayout *vlayout_txt_btns = nullptr;

    QHBoxLayout *hlayout_main = nullptr;
    QTextEdit * txted;
    QPushButton* btnTableX= nullptr;
    QPushButton* btnTableOK = nullptr;
    int id = 0;
private slots:
    void sendTextToStatus();
    void closeTextFld();
signals:
    void btnX_click(int);
    void btnOK_click(QString);


};

class TextCustomWidget : public QWidget
{
    Q_OBJECT

public:
    TextCustomWidget(QStatusBar *statusBar, QWidget *parent = nullptr);
    ~TextCustomWidget();


    void addTxtField();
    void clearTextPanels();

private:
    QStatusBar* statusBar = nullptr;

    QVBoxLayout *vlayout_wdgt = nullptr;
    QVector<TextField*> txt_fields;
    int txt_fields_id = 1;

private slots:
    void remTextPanel(int id);
};
#endif // TABLEWIDGET_H
