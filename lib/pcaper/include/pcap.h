#pragma once

#include <QString>
#include <QFile>
#include <QDebug>

#include "packet.h"

typedef unsigned int u_int;
typedef unsigned short u_short;
typedef unsigned char u_char;

class Pcap
{
        QFile *file;
        char *pcap_hdr;

    public:
        bool isValid;

        Pcap (const QString &);
        ~Pcap();
        Packet *getNextPacket();
        u_char *getPacketData (u_int);
        bool hasNext();

};
