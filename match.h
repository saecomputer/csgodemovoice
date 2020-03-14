#ifndef MATCH_H
#define MATCH_H

#include <QMetaType>
#include <QString>
#include <QByteArray>

class Match
{
public:
    QString name;
    int tickrate;
    int demoBegin;
    int audioBegin;
    QString vdemFilename;
    QString demoFilename;
    QString audioFilename;
};

Q_DECLARE_METATYPE(Match);

#endif // MATCH_H
