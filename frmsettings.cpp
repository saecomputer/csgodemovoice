#include "frmsettings.h"
#include "ui_frmsettings.h"

#include <QFileDialog>

FrmSettings::FrmSettings(QWidget *parent) :
    SaeDialog(parent),
    ui(new Ui::FrmSettings)
{
    ui->setupUi(this);
    ui->txtCsgo->setText(Settings::getCsgoFilename());
    ui->txtWorkspace->setText(Settings::getWorkspace());
}

FrmSettings::~FrmSettings()
{
    delete ui;
}

void FrmSettings::on_btnCsgoOpen_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                tr("Open CSGO"), "", tr("CSGO (csgo.exe)"));
    if(!path.isEmpty())
    {
        Settings::setCsgoFilename(path);
        ui->txtCsgo->setText(path);
    }
}

void FrmSettings::on_btnWorkspaceOpen_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this);
    if(!path.isEmpty())
    {
        Settings::setWorkspace(path);
        ui->txtWorkspace->setText(path);
    }
}

void FrmSettings::on_btnSave_clicked()
{
    this->close();
}
