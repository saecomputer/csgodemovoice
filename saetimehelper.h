#ifndef QTIMEHELPER_H
#define QTIMEHELPER_H

#include <QTime>

class SaeTimeHelper
{
public:
    static int HmsToMs(int h=0, int m=0, int s=0, int ms=0);
    static int MsToH(int ms);
    static int MsToM(int ms);
    static int MsToS(int ms);
    static QTime fromMs(int ms);
    static QTime fromHMS(int h=0, int m=0, int s=0, int ms=0);
    static QTime fromTick(int tickrate, int tick);
    static int toMs(QTime time);
};

#endif // QTIMEHELPER_H
