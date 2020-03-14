#ifndef FRMMATCH_H
#define FRMMATCH_H

#include "saedialog.h"
#include "match.h"
#include "vdem.h"
#include "saetimehelper.h"
#include "settings.h"
#include <QThread>

namespace Ui {
class FrmMatch;
}

class FrmMatch : public SaeDialog
{
    Q_OBJECT

public:
    explicit FrmMatch(QString vdemFilename="", QWidget *parent = nullptr);
    ~FrmMatch();

private slots:
    void showLoadingScreen();
    void hideLoadingScreen();
    void saveMatch();
    void loadMatch();
    void saveMatchFinished(Match match);
    void loadMatchFinished(Match match);
    QString createNewFilename();

    void on_btnSave_clicked();
    void on_btnDemoOpen_clicked();
    void on_btnAudioOpen_clicked();

private:
    Ui::FrmMatch *ui;
    Match match;
};

#endif // FRMMATCH_H
