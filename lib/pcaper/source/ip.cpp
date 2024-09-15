#include "ip.h"

Ip::Ip (const u_char *begin)
{
    hdr_len = begin;
    protocol = begin + 9;
    src = begin + 12;
    dest = begin + 16;
    //       for (int i = 0; i < 32; ++i)
    //           printf("%.2x ", begin[i]);
    //    version = begin[0] / 16;
    //hdr_len = count word (32 bit) in hdr
    //    if (hdr_len != 20) return;
    //    tos = begin[1];
    //    total_len = begin[2] * 256 + begin[3];
    //    id = begin[4] * 256 + begin[5];
    //    flag = begin[6] >> 1;
    //    fragment = (begin[6] % 2) * 256 + begin[7];
    //    ttl = begin[8];
    //    check_sum = begin[10] * 256 + begin[11];
    //    src = ((int)begin[12] << 24) + ((int)begin[13] << 16) +
    //            ((int)begin[14] << 8) + begin[15];
    //    dest = ((int)begin[16] << 24) + ((int)begin[17] << 16) +
    //            ((int)begin[18] << 8) + begin[19];
}

u_char Ip::getProtocol()
{
    return *protocol;
}

Report Ip::writeReport ()
{
    Report data;
    data.push_front (getIp (src)); //Source IP
    data.push_front (getIp (dest)); //Destination IP
    data.push_front (QString::number (getProtocol())); //Protocol
    return data;
}

QString Ip::getIp (const u_char *addr)
{
    return QString ("%1.%2.%3.%4").arg (
               QString::number (*addr),
               QString::number (* (addr + 1)),
               QString::number (* (addr + 2)),
               QString::number (* (addr + 3))
           );
}
