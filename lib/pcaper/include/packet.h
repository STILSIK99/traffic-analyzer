#pragma once

typedef unsigned int u_int;
typedef unsigned short u_short;
typedef unsigned char u_char;

#include <QString>
#include <QFile>
#include <QDebug>

class Packet
{
        char *pkt_hdr;

    public:
        bool isValid;

        Packet (char *);
        ~Packet();
        u_int getLength();
        u_int getSec();
        u_int getUsec();

};
