#ifndef FRMABOUT_H
#define FRMABOUT_H

#include "saedialog.h"

namespace Ui {
class FrmAbout;
}

class FrmAbout : public SaeDialog
{
    Q_OBJECT

public:
    explicit FrmAbout(QWidget *parent = nullptr);
    ~FrmAbout();

private:
    Ui::FrmAbout *ui;
};

#endif // FRMABOUT_H
