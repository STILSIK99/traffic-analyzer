#pragma once

#include <QJsonObject>
#include <QString>
#include <QDebug>

using namespace std;

typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef std::list<QString> Report;

class Ip
{
        //    u_char version;
        //DSCP and ECN
        //    u_char tos;
        //    u_short total_len;
        //    u_short id;
        //    u_char flag;
        //    u_short fragment;
        //    u_char ttl;
        //    u_short check_sum;
        const u_char *src;
        const u_char *dest;
        const u_char *protocol;

        QString getIp (const u_char *begin);

    public:
        const u_char *hdr_len;

        u_char getProtocol();

        Ip (const u_char *begin);

        Report writeReport ();

};

