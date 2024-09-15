#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QObject>
#include <QString>
#include <QDebug>
#include <QDate>
#include <vector>

#include <utility>

#include "vars.h"

typedef std::list<QString> Report;

class DataBase : public QObject
{
        Q_OBJECT
    private:
        QSqlDatabase db;
        QString filename;
        void initDataBase();
        std::map<QString, int> fileIds;

    public:
        //        bool connect ();
        DataBase (const QString &);
        ~DataBase();

        //внесение изменений
        bool query (const QString &);
        QString getFileId (const QString &);

        bool isOpen();

    public slots:

        void insertFile (const QString &filename);
        void insertRecord (Report *data);
        void finishFile (const QString &);

    signals:
        void errorConnection();
};
