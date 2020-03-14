#include "saetimehelper.h"

int SaeTimeHelper::HmsToMs(int h, int m, int s, int ms)
{
    return ((
            (h * 60 * 60) +
            (m * 60) +
            (s)
           ) * 1000) + ms;
}

int SaeTimeHelper::MsToH(int ms)
{
    int x = ms / 1000;
    int h = (x / 60 / 60);
    return h;
}

int SaeTimeHelper::MsToM(int ms)
{
    int x = ms / 1000;
    int m = (x / 60) % 60;
    return m;
}

int SaeTimeHelper::MsToS(int ms)
{
    int x = ms / 1000;
    int s =  x % 60;
    return s;
}
