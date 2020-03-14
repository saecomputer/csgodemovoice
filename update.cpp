#include "update.h"

#include <QString>
#include <QProcess>
#include <QCoreApplication>

Update::Update()
{

}

bool Update::check()
{
    QString program =  QCoreApplication::applicationDirPath() + "/maintenancetool.exe";
    QString workingDirectory = QCoreApplication::applicationDirPath();
    QStringList arguments;
    arguments << "--checkupdates";

    QProcess *myProcess = new QProcess();
    myProcess->setWorkingDirectory(workingDirectory);
    myProcess->start(program, arguments);
    myProcess->waitForFinished();
    QByteArray data = myProcess->readAll();

    if(data.isEmpty())
        return false;
    else
        return true;
}

void Update::startUpdater()
{
    QString program =  QCoreApplication::applicationDirPath() + "/maintenancetool.exe";
    QString workingDirectory = QCoreApplication::applicationDirPath();
    QStringList arguments;
    arguments << "--updater";

    QProcess *myProcess = new QProcess();
    myProcess->setWorkingDirectory(workingDirectory);
    myProcess->startDetached(program, arguments);
}
