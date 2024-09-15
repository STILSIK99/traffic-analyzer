#include "udp.h"
#include "tcp.h"

Udp::Udp (const u_char *begin)
{
    src_port = begin;
    dest_port = begin + 2;
    data_len = begin + 4;
}

Report *Udp::writeReport (int size)
{
    Report *data = new Report;
    data->push_back (QString::number (getSrcPort())); //Source port
    data->push_back (QString::number (getDestPort())); //Destination port
    data->push_back (QString::number (getDataSize())); //UDP Size
    return data;
}

u_short Udp::getDestPort()
{
    return *dest_port * 256 + * (dest_port + 1);
}

u_short Udp::getSrcPort()
{
    return *src_port * 256 + * (src_port + 1);
}

int Udp::getDataSize()
{
    return (int (*data_len) << 8) + (* (data_len + 1));
}
