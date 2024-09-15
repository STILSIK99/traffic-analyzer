#pragma once

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QFileInfo>
#include <QDir>
#include <QDirIterator>
#include <QChar>
#include <QCoreApplication>

#include <map>

#include "processor.h"
#include "tools.h"
#include "exceptions.h"
#include "database.h"
#include "csv_report.h"

class TrafficParser: public QCoreApplication
{
        Q_OBJECT


    private:
        int threadCount;
        QString dump;
        QString result;
        QDateTime startTime;

        std::list<QString> files;
        int progress;
        int fullCount;

        std::map<QThread *, Processor *> workers;
        DataBase *database;
        QThread *dataThread;
        CSVReport *out;


        void getDirectory (char *);
        void printParameters();
        void initDefaultParams();
        void readDumpSource (char *);
        void readParams (int, char *[]);
        void prepareFileList();


    public:

        TrafficParser (int, char **);
        void init (int argc, char **);
        void start();
        static void printHelp();
        ~TrafficParser();
    public slots:
        void finishedFile (const QString &);
    signals:
        void parseFile (const QString &, int);

};
