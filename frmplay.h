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
    static const uintptr_t csgoTickOffset = 0x65E36C;

private slots:
    void showLoadingScreen();
    void hideLoadingScreen();

    void start();
    void stop();
    void sync();
    int getTick();

    void loadMatchFinished(Match match);

    void on_btnStop_clicked();
    void closeEvent (QCloseEvent *event);

};

#endif // FRMPLAY_H
