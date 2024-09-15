#include <QCoreApplication>

#include "traffic_parser.h"
#include "exceptions.h"
#include <iostream>

#include <QObject>
#include "processor.h"
#include "database.h"

int main (int argc, char *argv[])
{
    //    std::ios_base::sync_with_stdio (0);
    //    std::cin.tie (NULL);
    //    std::cout.tie (NULL);
    TrafficParser *app = new TrafficParser (argc, argv);
    try {

        app->init (argc, argv);
        app->start();
    }  catch (EXCEPTIONS::Parameter e) {
        qDebug() << e.what();
        TrafficParser::printHelp();
        delete app;
        return 0;
    }

    //    DataBase *db = new DataBase ("F:/Current projs/PRG/dev_cpp/traffic-parser-master/remastered/src/data.db");
    //    Processor *pr = new Processor (1);
    //    QObject::connect (pr, &Processor::saveReport, db, &DataBase::insertRecord);
    //    pr->inputFile ("F:/Current projs/PRG/dev_cpp/traffic-parser-master/remastered/src/test.pcap", 1);

    return app->exec();
}
