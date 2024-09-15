#pragma once

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

#include <utility>
#include <set>

typedef unsigned char u_char;

struct Http {
    //    QJsonObject body;
    //    QJsonObject add;
    const u_char *begin;
    int len;

    Http (const u_char *pkt_data, int size);

    Http();

    bool isDataFound();

    bool checkApplication (const u_char *, int);

    void foundKey (std::pair<bool, QString> &, const u_char *, int );

    void getValue (QString &, const u_char *, int );

    std::pair<QString, QString> getToken (QString);

    QJsonObject writeReport (std::set<QString> &attributes);
};

