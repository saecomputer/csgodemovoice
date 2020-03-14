#include "vdem.h"
#include "settings.h"

#include <QFile>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>

bool FileHelper::readFile(QString filename, QByteArray &data)
{
    QFile f(filename);
    if(f.open(QIODevice::ReadWrite))
    {
        data = f.readAll();
        if(data.size()>0)
            return true;
    }
    return false;
}

bool FileHelper::writeFile(QString filename, QByteArray &data)
{
    QFile f(filename);
    if(f.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        qint64 size = f.write(data);
        if(size>0)
            return true;
    }
    return false;
}

VdemSaver::VdemSaver()
{
}

void VdemSaver::setMatch(const Match &value)
{
    match = value;
}

void VdemSaver::save()
{
    int version = 1;
    QByteArray data;
    QByteArray vdem;
    QDataStream vdemStream(&vdem, QIODevice::ReadWrite);

    vdemStream << version;
    vdemStream << match.name;
    vdemStream << match.tickrate;
    vdemStream << match.demoBegin;
    vdemStream << match.audioBegin;

    if(!FileHelper::readFile(match.demoFilename, data))
        lastError = 1;
    vdemStream << data;

    if(!FileHelper::readFile(match.audioFilename, data))
        lastError = 1;
    vdemStream << data;

    vdem = qCompress(vdem, 1);
    if(!FileHelper::writeFile(match.vdemFilename, vdem))
        lastError = 1;

    emit saved(match);
}

VdemLoader::VdemLoader()
{
}

void VdemLoader::setMatch(const Match &value)
{
    match = value;
}

void VdemLoader::load()
{
    int version;
    QByteArray data;
    QByteArray vdem;
    QDataStream vdemStream(&vdem, QIODevice::ReadWrite);

    if(!FileHelper::readFile(match.vdemFilename, vdem))
        lastError = 1;
    vdem = qUncompress(vdem);

    vdemStream >> version;
    vdemStream >> match.name;
    vdemStream >> match.tickrate;
    vdemStream >> match.demoBegin;
    vdemStream >> match.audioBegin;

    vdemStream >> data;
    match.demoFilename = Settings::getWorkspace() + "/current.dem";
    if(!FileHelper::writeFile(match.demoFilename, data))
    {
        match.demoFilename.clear();
        lastError = 1;
    }

    vdemStream >> data;
    match.audioFilename = Settings::getWorkspace() + "/current.wav";
    if(!FileHelper::writeFile(match.audioFilename, data))
    {
        match.audioFilename.clear();
        lastError = 1;
    }

    emit loaded(match);
}


