#ifndef VDEMTHREAD_H
#define VDEMTHREAD_H

#include "match.h"

#include <QThread>
#include <QObject>

class FileHelper
{
public:
    static bool readFile(QString filename, QByteArray &data);
    static bool writeFile(QString filename, QByteArray &data);
};

class VdemSaver : public QObject
{
    Q_OBJECT
public:
    VdemSaver();
    void setMatch(const Match &value);

public slots:
    void save();

signals:
    void saved(Match match);

private:
    Match match;
    int lastError;
};

class VdemLoader : public QObject
{
    Q_OBJECT
public:
    VdemLoader();
    void setMatch(const Match &value);

public slots:
    void load();

signals:
    void loaded(Match match);

private:
    Match match;
    int lastError;

};

#endif // VDEMTHREAD_H
