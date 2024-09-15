#include "csv_report.h"


CSVReport::CSVReport (const QString &_path)
{
    path = _path;
}


void CSVReport::insertRecord (Report *data)
{
    for (auto it = data->begin(); it != data->end(); ++it) {
        file.write (it->toUtf8());
        file.write (";");
    }
    file.write ("\n");
    ++counter;
    if (counter > 1e15) {
        counter = 0;
    }
    if (counter % 1000 == 0) {
        file.flush();
        file.close();
        file.open (QIODevice::Append);
    }
    delete data;
}

void CSVReport::init()
{
    file.setFileName (path);
    if (!file.open (QIODevice::WriteOnly)) {
        qDebug() << "Output file: unavailable.";
    } else {
        qDebug() << "CSV file: " << path;
    }
}

CSVReport::~CSVReport()
{
    file.close();
}
