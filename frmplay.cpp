#include "frmplay.h"
#include "ui_frmplay.h"

#include <QSvgWidget>
#include <QMessageBox>

FrmPlay::FrmPlay(QString vdemFilename, QWidget *parent) :
    SaeDialog(parent),
    ui(new Ui::FrmPlay)
{
    ui->setupUi(this);
    showLoadingScreen();

    connect(&timer, &QTimer::timeout, this, &FrmPlay::sync);
    match.vdemFilename = vdemFilename;
    ui->txtName->setText(match.vdemFilename.section("/",-1,-1));

    QSvgWidget *svgBar = new QSvgWidget(QString(":/res/arrowbar.svg"), this);
    svgBar->setFixedSize(256, 32);
    ui->layoutBar->addWidget(svgBar);
    ui->layoutBar->setAlignment(svgBar, Qt::AlignHCenter);

    QSvgWidget *svgLoading = new QSvgWidget(QString(":/res/loading.svg"), this);
    svgLoading->setFixedSize(64, 64);
    ui->layoutLoading->addWidget(svgLoading);

    QTimer::singleShot(100, this, &FrmPlay::formLoaded);
}

FrmPlay::~FrmPlay()
{
    delete ui;
}

void FrmPlay::formLoaded()
{
    if(!validCsgoVersion())
    {
        stop();
        return;
    }

    QThread *thread = new QThread();
    VdemLoader *vdemLoader = new VdemLoader();
    vdemLoader->setMatch(match);
    vdemLoader->moveToThread(thread);
    connect(thread, &QThread::started, vdemLoader, &VdemLoader::load);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(thread, &QThread::finished, vdemLoader, &QObject::deleteLater);
    connect(vdemLoader, &VdemLoader::loaded, this, &FrmPlay::loadMatchFinished);
    thread->start();
}

void FrmPlay::showLoadingScreen()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void FrmPlay::hideLoadingScreen()
{
    ui->stackedWidget->setCurrentIndex(0);
}

QString FrmPlay::fileChecksum(const QString &fileName, QCryptographicHash::Algorithm hashAlgorithm)
{
    QFile f(fileName);
    if (f.open(QFile::ReadOnly)) {
        QCryptographicHash hash(hashAlgorithm);
        if (hash.addData(&f)) {
            return hash.result().toBase64();
        }
    }
    return "";
}

bool FrmPlay::validCsgoVersion()
{
    bool valid = true;
    QString csgoFilename = Settings::getCsgoFilename();
    QString engineFilename = Settings::getCsgoFilename().section("/",0,-2) + "/bin/engine.dll";

    QString currentCsgoChecksum=fileChecksum(csgoFilename);
    QString currentEngineChecksum=fileChecksum(engineFilename);

    if(currentCsgoChecksum!=this->csgoChecksum)
        valid = false;
    if(currentEngineChecksum!=this->engineChecksum)
        valid = false;

    qDebug() << "currentCsgoChecksum" << currentCsgoChecksum;
    qDebug() << "currentEngineChecksum" << currentEngineChecksum;

    if(!valid)
    {
        int ret = QMessageBox::warning(this,
                                       "Warning",
                                       "Version difference between CS:GO and Demovoice!\n"
                                       "This can lead to errors.\n"
                                       "Do you want to continue?",
                                       QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(ret==QMessageBox::Yes)
            return true;
    }
    return valid;
}

void FrmPlay::start()
{
    hideLoadingScreen();
    QString csgoFilename = Settings::getCsgoFilename();
    QStringList arguments;
    arguments << "-insecure";
    arguments << "-novid";
    arguments << "+playdemo";
    arguments << match.demoFilename;

    process.setWorkingDirectory(csgoFilename.section("/",0,-2));
    process.start(csgoFilename, arguments);
    timer.start(50);
    mediaPlayer.setMedia(QUrl::fromLocalFile(match.audioFilename));
}

void FrmPlay::stop()
{
    timer.stop();
    mediaPlayer.stop();
    mediaPlayer.setMedia(QUrl());

    process.kill();
    process.waitForFinished(1000);

    this->close();
    QWidget *parent = qobject_cast<QWidget *>(this->parent());
    if(parent)
        parent->show();
}

void FrmPlay::loadMatchFinished(Match match)
{
    this->match = match;
    start();
}

void FrmPlay::sync()
{
    enum Status
    {
        ProcessStopped,
        DemoWaiting,
        DemoStopped,
        DemoRunning,
    };

    int status = Status::DemoRunning;
    int demoOffset = match.demoBegin;
    int audioOffset = match.audioBegin;

    int gameTick = getTick();
    int gameTime = gameTick * 1000 / match.tickrate;

    int targetAudioTime = (gameTime-demoOffset+audioOffset);
    int diff = int(targetAudioTime) - int(mediaPlayer.position());

    if(process.state() != QProcess::Running)
    {
        status = Status::ProcessStopped;
        mediaPlayer.stop();
        mediaPlayer.setPosition(0);
    }
    else if(gameTick==lastTick)
    {
        status = Status::DemoStopped;
        mediaPlayer.stop();
        mediaPlayer.setPosition(0);
    }
    else if(targetAudioTime<0)
    {
        status = Status::DemoWaiting;
        mediaPlayer.stop();
        mediaPlayer.setPosition(0);
    }
    else if(diff>100 || diff<-100)
    {
        qDebug() << "Adjust audio track.";
        mediaPlayer.play();
        mediaPlayer.setPosition(targetAudioTime);
    }
    lastTick = gameTick;

    switch(status)
    {
        case Status::ProcessStopped:
            ui->txtStatus->setText("CS:GO process stopped");
            ui->txtSync->setText("0000 ms");
            break;
        case Status::DemoStopped:
            ui->txtStatus->setText("Demo is stopped");
            ui->txtSync->setText("0000 ms");
            break;
        case Status::DemoWaiting:
            ui->txtStatus->setText("Waiting for match start");
            ui->txtSync->setText("0000 ms");
            break;
        case Status::DemoRunning:
            ui->txtStatus->setText("Running");
            ui->txtSync->setText(QString::number(abs(diff)).rightJustified(4, '0')+" ms");
            break;
    }

}

int FrmPlay::getTick()
{
    int tick = 0;
    if(process.state()==QProcess::Running)
    {
        memoryReader.openProcess(process.pid()->dwProcessId);
        uintptr_t engineBaseAddress = memoryReader.getModuleBaseAddress(process.pid()->dwProcessId, L"engine.dll");
        uintptr_t tickAddress = engineBaseAddress + csgoTickOffset;
        tick = memoryReader.readInt(tickAddress);
        memoryReader.closeProcess();
    }
    return tick;
}

void FrmPlay::on_btnStop_clicked()
{
    stop();
}

void FrmPlay::closeEvent(QCloseEvent *event)
{
    event->accept();
    stop();
}
