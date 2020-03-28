#ifndef FRMPLAY_H
#define FRMPLAY_H

#include "saedialog.h"
#include "vdem.h"
#include "match.h"
#include "settings.h"
#include "memoryreader.h"

#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QProcess>
#include <QMediaPlayer>
#include <QCryptographicHash>

namespace Ui {
class FrmPlay;
}

class FrmPlay : public SaeDialog
{
    Q_OBJECT

public:
    explicit FrmPlay(QString filename, QWidget *parent = nullptr);
    ~FrmPlay();

private:
    Ui::FrmPlay *ui;
    Match match;
    QTimer timer;
    QProcess process;
    MemoryReader memoryReader;
    QMediaPlayer mediaPlayer;
    int lastTick;

    QString csgoChecksum = "kVun5R5ihLu/kpA8Gp4Myg==";
    QString engineChecksum = "enRg6mwnpRPSm7SZgFa8+g==";
    static const uintptr_t csgoTickOffset = 0x65E2EC;

private slots:
    void formLoaded();
    void showLoadingScreen();
    void hideLoadingScreen();

    QString fileChecksum(const QString &fileName, QCryptographicHash::Algorithm hashAlgorithm = QCryptographicHash::Md5);
    bool validCsgoVersion();

    void start();
    void stop();
    void sync();
    int getTick();

    void loadMatchFinished(Match match);

    void on_btnStop_clicked();
    void closeEvent (QCloseEvent *event);

};

#endif // FRMPLAY_H
