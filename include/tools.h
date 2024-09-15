#pragma once

#include <QString>
#include <QDateTime>

namespace TOOLS
{
    bool isEqual (const QString &a, const QString &b, const QString &c);

    QString forgingOut (char *);

    QString fromSecToDate (long secs, long usecs);

    QString timeInterval (const QDateTime &from, const QDateTime &to);
}


