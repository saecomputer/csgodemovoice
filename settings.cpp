#include "settings.h"

#include <QDir>
#include <QFile>
#include <QSettings>
#include <QStandardPaths>
#include <QProcessEnvironment>

Settings::Settings()
{

}

void Settings::setCsgoFilename(QString w)
{
    setValue("csgo", w);
}

QString Settings::getCsgoFilename()
{
    if(exist("", "csgo"))
        return getValue("csgo", "");

    QString w = findCsgoFilename();
    setValue("csgo", w);
    return w;
}

void Settings::setWorkspace(QString w)
{
    setValue("workspace", w);
}

QString Settings::getWorkspace()
{
    if(exist("", "workspace"))
        return getValue("workspace", "");

    QString w = findWorkspace();
    setValue("workspace", w);
    return w;
}

bool Settings::exist(QString scope, QString key)
{
    bool r;
    QSettings s;

    if(!scope.isEmpty())
        s.beginGroup(scope);

    r = s.allKeys().contains(key);

    if(!scope.isEmpty())
        s.endGroup();

    return r;
}

void Settings::setValue(QString key, QString value)
{
    setValue("", key, value);
}

QString Settings::getValue(QString key, QString defaultValue)
{
    return getValue("", key, defaultValue);
}

void Settings::setValue(QString scope, QString key, QString value)
{
    QSettings s;

    if(!scope.isEmpty())
        s.beginGroup(scope);

    s.setValue(key, value);

    if(!scope.isEmpty())
        s.endGroup();
}

QString Settings::getValue(QString scope, QString key, QString defaultValue)
{
    QString r;
    QSettings s;

    if(!scope.isEmpty())
        s.beginGroup(scope);

    r = s.value(key, defaultValue).toString();

    if(!scope.isEmpty())
        s.endGroup();

    return r;
}

QString Settings::findCsgoFilename()
{
    QFile file;
    QSettings s;
    QString path;
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

    path = env.value("programfiles(x86)") + "/Steam/steamapps/common/Counter-Strike Global Offensive/csgo.exe";
    file.setFileName(path);
    if(file.exists())
    {
        return path;
    }

    path = env.value("programfiles") + "/Steam/steamapps/common/Counter-Strike Global Offensive/csgo.exe";
    file.setFileName(path);
    if(file.exists())
    {
        return path;
    }

    return "";

}

QString Settings::findWorkspace()
{
    QString docPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QDir docDir(docPath);
    if(docDir.exists())
    {
        QDir wsDir(docDir.path() + "/Demovoice");
        if(!wsDir.exists())
            wsDir.mkdir(wsDir.path());
        return wsDir.path();
    }
    return "";
}
