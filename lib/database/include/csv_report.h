#pragma once

#include <QObject>
#include <QFile>
#include <QString>
#include <QDebug>

#include <list>

#include "exceptions.h"

typedef std::list<QString> Report;

class CSVReport : public QObject
{
        Q_OBJECT

    private:
        QString path;
        QFile file;
        long long counter = 0;
    public:
        CSVReport (const QString &);
        ~CSVReport();

        void init();

    public slots:
        void insertRecord (Report *data);
};
