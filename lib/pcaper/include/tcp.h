#pragma once

#include <QJsonObject>
#include <string>
#include <QDebug>
#include <map>


typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;

typedef std::list<QString > Report;

class Tcp
{
        //    u_int seq_num;
        //    u_int ack_num;
        //    u_short flags;
        u_short w_size_val;
        //    u_short check_sum;
        //    u_short urg_point;
        //    string opt;
        const u_char *dest_port;
        const u_char *src_port;


    public:

        const u_char *hdr_len;

        //    u_short dest_port;
        //    u_short src_port;

        Tcp (const u_char *begin);

        Report *writeReport (int);
        u_short getDestPort();
        u_short getSrcPort();
        u_char getLen();
        int getHeaderSize();
};

