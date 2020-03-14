#ifndef FRMMAIN_H
#define FRMMAIN_H

#include "settings.h"

#include <QMainWindow>

namespace Ui {
class FrmMain;
}

class FrmMain : public QMainWindow
{
    Q_OBJECT
    int tblMatchColName = 0;
    int tblMatchColPath = 1;
    int tblMatchColPlay = 2;
    int tblMatchColEdit = 3;
    int tblMatchColDelete = 4;

public:
    explicit FrmMain(QWidget *parent = nullptr);
    ~FrmMain();

private:
    Ui::FrmMain *ui;

private slots:
    void tblMatchAdd(QString name, QString path);
    void loadMatch();

    void tblMatchBtnPlay();
    void tblMatchBtnEdit();
    void tblMatchBtnDelete();

    void on_actionNew_Match_triggered();
    void on_actionAbout_triggered();
    void on_actionSettings_triggered();
    void on_actionDonate_triggered();
};

#endif // FRMMAIN_H
