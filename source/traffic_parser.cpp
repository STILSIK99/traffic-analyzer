#include "traffic_parser.h"

TrafficParser::TrafficParser (int argc, char **argv): QCoreApplication (argc, argv)
{
    initDefaultParams();
}

TrafficParser::~TrafficParser()
{
    for (auto p : workers) {
        delete p.first;
        delete p.second;
    }
    dataThread->terminate();
    delete dataThread;
    delete out;
}

void TrafficParser::init (int argc, char *argv[])
{
    readParams (argc, argv);
    bool flag = true;
    if (dump == "") {
        throw EXCEPTIONS::Parameter (
            "Select directory with dumps.");
    }
    result = result.replace ('\\', '/');
    if (result == "") {
        result = dump;
    } else if (QFileInfo (result).isDir()) {
        if (result[result.size() - 1] != '/') {
            result += "/";
        }
        //        result += "result.db";
        result += "result.csv";
    }

    if (threadCount <= 0) {
        throw EXCEPTIONS::Parameter (
            "Input another thread count.");
    }

    out = new CSVReport (result);
    dataThread = new QThread;
    out->moveToThread (dataThread);
    dataThread->start();
    out->init();

    //    dataThread->start();
    //    database = new DataBase ("result.db");
    //    database->moveToThread (dataThread);
    //    if (!database->isOpen()) {
    //        throw EXCEPTIONS::Access (
    //            "Database unavailable.");
    //    }

    prepareFileList();
}


void TrafficParser::printHelp()
{
    qDebug() << "  Analyze dump of network traffic.                ";
    qDebug() << "  PARSER [--dir | -d[:]source] [--config | -c[:]configuration file]";
    qDebug() << "      [--threads | -t[:]count of threads] [--out | -o[:]report]    ";
    qDebug() << "";
    qDebug() << "  Parameters:\n";
    qDebug() << "    --dir\t Directory with dump for analyze.       ";
    qDebug() << "    --config\t Json-formatted file with some parameters.        ";
    qDebug() << "    --threads\t Count of threads that will be used for analyze.    ";
    qDebug() << "    --out\t Reports will be save in that directory.";
    qDebug() << "";
    qDebug() << "  By default:\n";
    qDebug() << "    Configuration file selected in tool directory.";
    qDebug() << "    Source directory selected for save reports.";
    qDebug() << "    The count of threads selected as 5.";
    qDebug() << "";
    qDebug() << "  Example of command stores in tool directory.";
    qDebug() << "";
}


void TrafficParser::printParameters()
{
    qDebug() << "Parsing directory - \t" << dump;
    qDebug() << "Path with result - \t" << result;
    qDebug() << "Count of threads - \t" << threadCount;
}

void TrafficParser::initDefaultParams()
{
    //    result = "data.db";
    result = "data.csv";
    threadCount = QThread::idealThreadCount() - 2;
    //    database = nullptr;
}

void TrafficParser::readDumpSource (char *str)
{
    dump = QString::fromStdString (str);
    if (dump.left (1) == "\"" && dump.right (1) == "\"") {
        dump = dump.mid (1, dump.length() - 2);
    }
}

void TrafficParser::readParams (int count, char **params)
{
    for (int i = 1; i < count; ++i) {
        if ((i + 1 < count) && TOOLS::isEqual (params[i], "--dir", "-d")) {
            readDumpSource (params[i + 1]);
            ++i;
        } else if ((i + 1 < count) && TOOLS::isEqual (params[i], "--out", "-o")) {
            dump = TOOLS::forgingOut (params[i + 1]);
            ++i;
        } else if ((i + 1 < count) && TOOLS::isEqual (params[i], "--threads", "-t")) {
            threadCount = std::min (
                              QString::fromStdString (params[i + 1]).toInt(),
                              QThread::idealThreadCount() - 2
                          );
            ++i;
        } else
            printHelp();

    }
}

void TrafficParser::prepareFileList()
{
    progress = 0;
    if (QFileInfo (dump).isDir()) {
        QDirIterator it (dump, QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext()) {
            QFileInfo info (it.next());
            files.push_back (info.filePath());
        }
    } else if (QFileInfo (dump).isFile()) {
        files.push_back (dump);
    }
    fullCount = files.size();
}

void TrafficParser::start()
{
    //    if (database == nullptr) return;
    startTime = QDateTime::currentDateTime();
    qDebug() << "Analysis start in " << startTime.toString ("yyyy-MM-dd HH:mm:ss");
    threadCount = std::min (threadCount, int (files.size()));
    std::vector<std::list<QString>> arr (threadCount, std::list<QString>());
    auto it = files.begin();
    for (int i = 0; i < files.size(); ++i, ++it) {
        arr[i % threadCount].emplace_back (*it);
    }

    for (int i = 0; i < threadCount; ++i) {
        auto thr = new QThread();
        auto  proc = new Processor (arr[i]);
        proc->moveToThread (thr);
        QObject::connect (thr, &QThread::started, proc, &Processor::start);
        //        QObject::connect (this, &TrafficParser::parseFile, proc, &Processor::inputFile);
        //        QObject::connect (proc, &Processor::saveReport, database, &DataBase::insertRecord);
        QObject::connect (proc, &Processor::saveReport, out, &CSVReport::insertRecord);
        QObject::connect (proc, &Processor::finishedFile, this, &TrafficParser::finishedFile);

        thr->start();
    }
    //    int i = 0;
    //    for (auto file : files) {
    //        emit (parseFile (file, (i++) % threadCount));
    //    }
}

void TrafficParser::finishedFile (const QString &path)
{
    qDebug() << "Progress: " << ++progress << " of " << fullCount
             << QFileInfo (path).fileName();
    if (progress >= fullCount) {
        QDateTime finishTime = QDateTime::currentDateTime();
        qDebug() << QString (50, '#');
        qDebug() << "Analysis finished in " << finishTime.toString ("yyyy-MM-dd HH:mm:ss");
        qDebug() << "Completed for " << TOOLS::timeInterval (startTime, finishTime);
    }
}















