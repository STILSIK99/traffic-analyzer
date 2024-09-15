#pragma once


#include <QJsonObject>
#include <string>
#include <QDebug>
#include <map>


typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;

typedef std::list<QString > Report;

class Udp
{
        const u_char *dest_port;
        const u_char *src_port;
        const u_char *data_len;


    public:


        Udp (const u_char *begin);

        Report *writeReport (int);
        u_short getDestPort();
        u_short getSrcPort();
        int getDataSize();
};
