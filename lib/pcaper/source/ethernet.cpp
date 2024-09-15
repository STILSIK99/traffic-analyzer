#include "ethernet.h"

Ethernet::Ethernet (const u_char *begin)
{
    dest = begin;
    src = begin + 6;
    type = begin + 12;
    //    for (int i = 0; i < 6; ++i) dest[i] = begin[i];
    //    for (int i = 0; i < 6; ++i) src[i] = begin[i + 6];
    //    for (int i = 0; i < 2; ++i) type[i] = begin[i + 12];
}

QString Ethernet::getHex (const u_char *str, bool isMac)
{
    QString s (4, 0);
    if (isMac) {
        s = QString (17, ':');
        for (int i = 0; i < 12; ++i) {
            s[i + i / 2] = getHexSymb ( (i % 2 == 0) ? (str[i / 2] / 16) : (str[i / 2] % 16));
        }
        return s;
    }
    s = QString (4, 0);
    for (int i = 0; i < 4; ++i) {
        s[i] = getHexSymb ((i % 2 == 0) ? (str[i / 2] / 16) : (str[i / 2] % 16));
    }
    return s;
}

Report Ethernet::writeReport ()
{
    Report data;
    data.push_front (getHex (src, true)); //Source MAC
    data.push_front (getHex (dest, true)); //Destination MAC
    data.push_front (getHex (type, false)); //EtherType
    return data;
}

u_short Ethernet::getType()
{
    return type[0] * 256 + type[1];
}

char Ethernet::getHexSymb (char a)
{
    if (a >= 0 && a <= 9) {
        return 48 + a;
    }
    return 'a' + a - 10;
};

