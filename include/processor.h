#pragma once

#include <QObject>
#include <list>
#include <QJsonObject>
#include <QFileInfo>

#include "pcap.h"
#include "packet.h"
#include "tools.h"
#include "ethernet.h"
#include "ip.h"
#include "tcp.h"
#include "udp.h"

#include "vars.h"

typedef std::list<QString> Report;

class Processor : public QObject
{
        Q_OBJECT

    private:
        std::list<QString> files;
        void process (const QString &);
        Report *processEth (const u_char *, int);
        Report *processIp (const u_char *, int);
        Report *processTcp (const u_char *, int);
        Report *processUdp (const u_char *, int);

    public:
        Processor (std::list<QString>);

    public slots:
        void start();
    signals:
        void saveReport (Report *);
        void finishedFile (QString);
};
