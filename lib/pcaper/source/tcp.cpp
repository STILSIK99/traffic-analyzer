#include "tcp.h"

Tcp::Tcp (const u_char *begin)
{
    src_port = begin;
    dest_port = begin + 2;
    hdr_len = begin + 12;
    //    hdr_len = >> 4;
    //    w_size_val = 0;
    //    for (int i = 0; i < 2; ++i) {
    //        src_port = (src_port << 8) + begin[i];
    //    }
    //    for (int i = 2; i < 4; ++i) {
    //        dest_port = (dest_port << 8) + begin[i];
    //    }
    //    hdr_len =  >> 2;
    /*, seq_num = 0,
            ack_num = 0, hdr_len = 0, flags = 0,
            w_size_val = 0, check_sum = 0, urg_point = 0;*/
    //    for (int i = 4; i < 8; ++i) {
    //        seq_num = seq_num << 8 + begin[i];
    //    }
    //    for (int i = 8; i < 12; ++i) {
    //        ack_num = ack_num << 8 + begin[i];
    //    }
    //    flags = ((begin[12] % 16) << 8) + begin[13];
    //    for (int i = 14; i < 16; ++i) {
    //        w_size_val = w_size_val * 256 + begin[i];
    //    }
    //    for (int i = 16; i < 18; ++i) {
    //        check_sum = check_sum * 256 + begin[i];
    //    }
    //    for (int i = 18; i < 20; ++i) {
    //        urg_point = urg_point * 256 + begin[i];
    //    }
    //    opt = string(hdr_len - 20, ' ');
    //    for (int i = 20; i < hdr_len; ++i){
    //        opt[i - 20] = begin[i];
    //    }
}

Report *Tcp::writeReport (int size)
{
    Report *data = new Report;
    data->push_back (QString::number (getSrcPort())); //Source port
    data->push_back (QString::number (getDestPort())); //Destination port
    data->push_back (QString::number (size - getHeaderSize())); //TCP protocol
    return data;
}

u_short Tcp::getDestPort()
{
    return *dest_port * 256 + * (dest_port + 1);
}

u_short Tcp::getSrcPort()
{
    return *src_port * 256 + * (src_port + 1);
}

u_char Tcp::getLen()
{
    return *hdr_len >> 2;
}

int Tcp::getHeaderSize()
{
    u_char buffer = *hdr_len >> 4;
    return buffer * 4;
}
