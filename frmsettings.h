#ifndef FRMSETTINGS_H
#define FRMSETTINGS_H

#include "saedialog.h"
#include "settings.h"

namespace Ui {
class FrmSettings;
}

class FrmSettings : public SaeDialog
{
    Q_OBJECT

public:
    explicit FrmSettings(QWidget *parent = nullptr);
    ~FrmSettings();

private slots:
    void on_btnCsgoOpen_clicked();
    void on_btnWorkspaceOpen_clicked();
    void on_btnSave_clicked();

private:
    Ui::FrmSettings *ui;
};

#endif // FRMSETTINGS_H
