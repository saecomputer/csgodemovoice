#include "frmabout.h"
#include "ui_frmabout.h"
#include "build.h"

FrmAbout::FrmAbout(QWidget *parent) :
    SaeDialog(parent),
    ui(new Ui::FrmAbout)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    QString date = __DATE__;
    QString time = __TIME__;

    QString major = MAJOR;
    QString minor = MINOR;
    QString patch = PATCH;
    QString build = BUILD;

    ui->lblVersion->setText(major + "." + minor + "." + patch + "." + build);
    ui->lblCreateDate->setText(date + " " + time);
}

FrmAbout::~FrmAbout()
{
    delete ui;
}
