#include "frmmain.h"
#include "ui_frmmain.h"

#include "frmabout.h"
#include "frmplay.h"
#include "frmmatch.h"
#include "frmsettings.h"

#include <QDebug>
#include <QDir>
#include <QPushButton>
#include <QDesktopServices>

FrmMain::FrmMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FrmMain)
{
    ui->setupUi(this);
    ui->tblMatch->horizontalHeader()->setSectionResizeMode(tblMatchColName, QHeaderView::Stretch);
    ui->tblMatch->setColumnHidden(tblMatchColPath, true);
    ui->tblMatch->setColumnWidth(tblMatchColPlay, 80);
    ui->tblMatch->setColumnWidth(tblMatchColEdit, 80);
    ui->tblMatch->setColumnWidth(tblMatchColDelete, 80);
    loadMatch();
}

FrmMain::~FrmMain()
{
    delete ui;
}

void FrmMain::tblMatchAdd(QString name, QString path)
{
    int row = ui->tblMatch->rowCount();
        ui->tblMatch->insertRow(row);

    ui->tblMatch->setItem(row, tblMatchColName, new QTableWidgetItem(name));
    ui->tblMatch->setItem(row, tblMatchColPath, new QTableWidgetItem(path));

    QPushButton *btnPlay = new QPushButton;
    connect(btnPlay, &QPushButton::clicked, this, &FrmMain::tblMatchBtnPlay);
    btnPlay->setText("Play");
    btnPlay->setFlat(true);
    ui->tblMatch->setCellWidget(row, tblMatchColPlay, btnPlay);

    QPushButton *btnEdit= new QPushButton;
    connect(btnEdit, &QPushButton::clicked, this, &FrmMain::tblMatchBtnEdit);
    btnEdit->setText("Edit");
    btnEdit->setFlat(true);
    ui->tblMatch->setCellWidget(row, tblMatchColEdit, btnEdit);

    QPushButton *btnDelete = new QPushButton;
    connect(btnDelete, &QPushButton::clicked, this, &FrmMain::tblMatchBtnDelete);
    btnDelete->setText("Remove");
    btnDelete->setFlat(true);
    ui->tblMatch->setCellWidget(row, tblMatchColDelete, btnDelete);
}

void FrmMain::loadMatch()
{
    ui->tblMatch->setRowCount(0);
    QDir dir(Settings::getWorkspace());
    QFileInfoList fiList = dir.entryInfoList();
    for(QFileInfo fi: fiList)
    {
        if(fi.fileName().right(5) == ".vdem")
        {
            tblMatchAdd(fi.fileName(), fi.filePath());
        }
    }
}

void FrmMain::tblMatchBtnPlay()
{
    int row = ui->tblMatch->currentRow();
    if(row>=0)
    {
        QString filename = ui->tblMatch->item(row, tblMatchColPath)->text();
        FrmPlay *frm = new FrmPlay(filename, this);
        connect(frm, &FrmPlay::closed, this, &FrmMain::loadMatch);
        frm->show();
        this->hide();
    }
}

void FrmMain::tblMatchBtnEdit()
{
    int row = ui->tblMatch->currentRow();
    if(row>=0)
    {
        QString filename = ui->tblMatch->item(row, tblMatchColPath)->text();
        FrmMatch *frm = new FrmMatch(filename);
        connect(frm, &FrmMatch::closed, this, &FrmMain::loadMatch);
        frm->show();
    }
}

void FrmMain::tblMatchBtnDelete()
{
    int row = ui->tblMatch->currentRow();
    if(row>=0)
    {
        QString filename = ui->tblMatch->item(row, tblMatchColPath)->text();
        QFile f(filename);
        f.remove();
        loadMatch();
    }
}

void FrmMain::on_actionNew_Match_triggered()
{
    FrmMatch *frm = new FrmMatch;
    connect(frm, &FrmMatch::closed, this, &FrmMain::loadMatch);
    frm->show();
}

void FrmMain::on_actionAbout_triggered()
{
    FrmAbout *frm = new FrmAbout();
    connect(frm, &FrmAbout::closed, this, &FrmMain::loadMatch);
    frm->show();
}

void FrmMain::on_actionSettings_triggered()
{
    FrmSettings *frm = new FrmSettings();
    connect(frm, &FrmSettings::closed, this, &FrmMain::loadMatch);
    frm->show();
}

void FrmMain::on_actionDonate_triggered()
{
    QDesktopServices::openUrl(QUrl("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=QN2UC85PAVCMC&source=url"));
}
