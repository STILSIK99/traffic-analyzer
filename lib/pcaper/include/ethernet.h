#pragma once

#include <QString>
#include <QJsonObject>
#include <QDebug>

#include <set>

using namespace std;

typedef unsigned char u_char;
typedef unsigned short u_short;
typedef std::list<QString> Report;

class Ethernet
{
        const u_char *dest;  //[6];
        const u_char *src;   //[6];
        const u_char *type;  //[2];

        char getHexSymb (char);

        QString getHex (const u_char *str, bool isMac);

    public:

        Ethernet (const u_char *begin);

        Report writeReport ();

        u_short getType();

};
