#include "frmmatch.h"
#include "ui_frmmatch.h"

#include <QTime>
#include <QFile>
#include <QMovie>
#include <QFileDialog>
#include <QSvgWidget>

FrmMatch::FrmMatch(QString vdemFilename, QWidget *parent) :
    SaeDialog(parent),
    ui(new Ui::FrmMatch)
{
    ui->setupUi(this);
    ui->txtName->setValidator(new QRegExpValidator( QRegExp("[0-9a-zA-Z ]+"), this ));

    QSvgWidget *svgWidget = new QSvgWidget(QString(":/res/loading.svg"), this);
    svgWidget->setFixedSize(64, 64);
    ui->layoutLoading->addWidget(svgWidget);

    match.vdemFilename = vdemFilename;
    loadMatch();
}

FrmMatch::~FrmMatch()
{
    delete ui;
}

void FrmMatch::showLoadingScreen()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void FrmMatch::hideLoadingScreen()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void FrmMatch::on_btnSave_clicked()
{
    saveMatch();
}

void FrmMatch::saveMatch()
{
    showLoadingScreen();

    match.name = ui->txtName->text();
    match.tickrate = ui->cboTickrate->currentText().toInt();
    match.demoBegin = SaeTimeHelper::HmsToMs(ui->txtDemoBeginH->value(), ui->txtDemoBeginM->value(), ui->txtDemoBeginS->value());
    match.audioBegin = SaeTimeHelper::HmsToMs(ui->txtAudioBeginH->value(), ui->txtAudioBeginM->value(), ui->txtAudioBeginS->value());
    match.vdemFilename = createNewFilename();
    match.demoFilename = ui->txtDemo->text();
    match.audioFilename = ui->txtAudio->text();

    QThread *thread = new QThread();
    VdemSaver *vdemSaver = new VdemSaver();
    vdemSaver->setMatch(match);
    vdemSaver->moveToThread(thread);
    connect(thread, &QThread::started, vdemSaver, &VdemSaver::save);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(thread, &QThread::finished, vdemSaver, &QObject::deleteLater);
    connect(vdemSaver, &VdemSaver::saved, this, &FrmMatch::saveMatchFinished);
    thread->start();
}

void FrmMatch::loadMatch()
{
    showLoadingScreen();

    QThread *thread = new QThread();
    VdemLoader *vdemLoader = new VdemLoader();
    vdemLoader->setMatch(match);
    vdemLoader->moveToThread(thread);
    connect(thread, &QThread::started, vdemLoader, &VdemLoader::load);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(thread, &QThread::finished, vdemLoader, &QObject::deleteLater);
    connect(vdemLoader, &VdemLoader::loaded, this, &FrmMatch::loadMatchFinished);
    thread->start();
}

void FrmMatch::saveMatchFinished(Match match)
{
    this->match = match;
    this->close();
}

void FrmMatch::loadMatchFinished(Match match)
{
    ui->txtName->setText(match.name);
    ui->cboTickrate->setCurrentText(QString::number(match.tickrate));
    ui->txtDemo->setText(match.demoFilename);
    ui->txtAudio->setText(match.audioFilename);
    ui->txtDemoBeginH->setValue(SaeTimeHelper::MsToH(match.demoBegin));
    ui->txtDemoBeginM->setValue(SaeTimeHelper::MsToM(match.demoBegin));
    ui->txtDemoBeginS->setValue(SaeTimeHelper::MsToS(match.demoBegin));
    ui->txtAudioBeginH->setValue(SaeTimeHelper::MsToH(match.audioBegin));
    ui->txtAudioBeginM->setValue(SaeTimeHelper::MsToM(match.audioBegin));
    ui->txtAudioBeginS->setValue(SaeTimeHelper::MsToS(match.audioBegin));
    hideLoadingScreen();
}

QString FrmMatch::createNewFilename()
{
    QFile f(match.vdemFilename);
    if(f.exists())
        f.remove();
    return Settings::getWorkspace() + "/" + match.name + ".vdem";
}

void FrmMatch::on_btnDemoOpen_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                    tr("Open Demo"), "", tr("Demo (*.dem)"));
    if(!path.isEmpty())
    {
        ui->txtDemo->setText(path);
    }
}

void FrmMatch::on_btnAudioOpen_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
                    tr("Open Audio"), "", tr("Audio (*.wav)"));
    if(!path.isEmpty())
    {
        ui->txtAudio->setText(path);
    }
}
