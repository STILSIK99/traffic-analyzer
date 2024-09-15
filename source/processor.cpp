#include "processor.h"

Processor::Processor (std::list<QString> arr): files (arr) {}

void Processor::start()
{
    for (auto &file : files) {
        process (file);
    }
}

void Processor::process (const QString &filename)
{
    Pcap *pcap = new Pcap (filename);
    if (!pcap->isValid) {
        emit finishedFile (filename);
        return;
    }
    int packet_id = 0;
    while (pcap->hasNext()) {
        Packet *pkt_hdr = pcap->getNextPacket();
        u_char *pkt_data = pcap->getPacketData (pkt_hdr->getLength());
        Report *data = processEth (pkt_data, pkt_hdr->getLength());
        if (data != nullptr) {
            data->push_front (TOOLS::fromSecToDate (pkt_hdr->getSec(), pkt_hdr->getUsec())); //time
            data->push_front (QString::number (packet_id)); //packet
            data->push_front (QFileInfo (filename).fileName()); //filename
            emit saveReport (data);
        }
        ++packet_id;
        delete []pkt_data;
        delete pkt_hdr;
    }
    delete pcap;
    emit finishedFile (filename);
    //    qDebug() << "Finished: " << filename;
}

Report *Processor::processEth (const u_char *pkt_data, int size)
{
    //get Ethernet header
    Ethernet eth_pkt (pkt_data);
    if (size - 14 < 20) return nullptr;
    auto x = eth_pkt.getType();
    if (eth_pkt.getType() == PCAP::ETHERTYPES::IPv4 && size > 14) {
        const u_char *next_hdr = (pkt_data + 14);
        Report *data = processIp (next_hdr, size - 14);
        if (data != nullptr) {
            for (auto &el : eth_pkt.writeReport()) {
                data->push_front (el);
            }
        }
        return data;
    }
    return nullptr;
}

Report *Processor::processIp (const u_char *pkt_data, int size)
{
    //get IP_v4 header
    Ip ip_pkt (pkt_data);
    int tcp_size = * (ip_pkt.hdr_len) % 16 * 4;
    Report *data = nullptr;
    if (ip_pkt.getProtocol() == PCAP::IPTYPES::TCP) {
        const u_char *next_hdr = (pkt_data + (*ip_pkt.hdr_len % 16 * 4));
        data = processTcp (next_hdr, size - (*ip_pkt.hdr_len % 16 * 4));
    } else if (ip_pkt.getProtocol() == PCAP::IPTYPES::UDP) {
        const u_char *next_hdr = (pkt_data + (*ip_pkt.hdr_len % 16 * 4));
        data = processUdp (next_hdr, size - (*ip_pkt.hdr_len % 16 * 4));
    }
    if (data != nullptr) {
        for (auto &el : ip_pkt.writeReport()) {
            data->push_front (el);
        }
        return data;
    } else {
        return new Report (ip_pkt.writeReport());
    }
    return nullptr;
}

Report *Processor::processUdp (const u_char *pkt_data, int size)
{
    if (size < 8) return nullptr;
    Udp udp_pkt (pkt_data);
    return udp_pkt.writeReport (size);
}

Report *Processor::processTcp (const u_char *pkt_data, int size)
{
    if (size < 20) return nullptr;
    Tcp tcp_pkt (pkt_data);
    return tcp_pkt.writeReport (size);
}
