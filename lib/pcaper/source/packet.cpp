#include "packet.h"


u_int Packet::getLength()
{
    return * (reinterpret_cast<u_int *> (pkt_hdr + 8));
}

u_int Packet::getSec()
{
    return * (reinterpret_cast<u_int *> (pkt_hdr));
}

u_int Packet::getUsec()
{
    return * (reinterpret_cast<u_int *> (pkt_hdr + 4));
}

Packet::~Packet ()
{
    delete []pkt_hdr;
}

Packet::Packet (char *data)
{
    pkt_hdr = data;
}
