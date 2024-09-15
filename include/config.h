#pragma once

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "exceptions.h"

#include <map>
#include <set>

typedef unsigned short u_short;

class Config
{
    private:
        QString path;
        std::map<QString, std::set<QString>> attributes;
        std::map<QString, std::map<u_short, QString>> types;
    public:
        Config (const QString &);
        void init();
        void parseCfg (const QJsonObject *);
};
