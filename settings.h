#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

class Settings
{
public:
    Settings();

    static void setCsgoFilename(QString);
    static QString getCsgoFilename();

    static void setWorkspace(QString);
    static QString getWorkspace();

    static bool exist(QString scope, QString key);
    static void setValue(QString key, QString value);
    static QString getValue(QString key, QString defaultValue);
    static void setValue(QString scope, QString key, QString value);
    static QString getValue(QString scope, QString key, QString defaultValue);

private:
    static QString findCsgoFilename();
    static QString findWorkspace();

};

#endif // SETTINGS_H
