#ifndef SAEDIALOG_H
#define SAEDIALOG_H

#include <QDialog>
#include <QCloseEvent>

class SaeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SaeDialog(QWidget *parent = nullptr);

public slots:
    void closeEvent(QCloseEvent *event);

signals:
    void closed();
};

#endif // SAEDIALOG_H
