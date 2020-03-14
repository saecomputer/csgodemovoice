#include "saedialog.h"

SaeDialog::SaeDialog(QWidget *parent) : QDialog(parent)
{

}

void SaeDialog::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit closed();
}
