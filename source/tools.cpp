#include "tools.h"


bool TOOLS::isEqual (const QString &a, const QString &b, const QString &c)
{
    return true;
}

QString TOOLS::forgingOut (char *str)
{
    QString result = QString::fromStdString (str);
    if (result.left (1) == "\"" && result.right (1) == "\"") {
        result = result.mid (1, result.length() - 2);
    }
    return result;
}


QString TOOLS::fromSecToDate (long secs, long usecs)
{
    return QDateTime::fromSecsSinceEpoch (secs).toString ("yyyy-MM-dd HH:mm:ss.")
           + QString::number (usecs);
}

QString TOOLS::timeInterval (const QDateTime &from, const QDateTime &to)
{
    if (from.isValid() && to.isValid()) {
        long long interval = from.secsTo (to);
        if (interval == 0) {
            int msecs = from.msecsTo (to);
            return QString ("00 mons 00 days 00 hours 00 mins 00 secs %1 msecs").arg (msecs, 3, 10, QLatin1Char ('0'));
        }
        if (interval < 0) interval *= -1;
        QString result = QString ("%1 secs").arg (interval % 60, 2, 10, QLatin1Char ('0'));
        interval /= 60;
        result = QString ("%1 mins").arg (interval / 60, 2, 10, QLatin1Char ('0')) + " " + result;
        interval /= 60;
        result = QString ("%1 hours").arg (interval / 60, 2, 10, QLatin1Char ('0')) + " " + result;
        interval /= 24;
        result = QString ("%1 days").arg (interval / 24, 2, 10, QLatin1Char ('0')) + " " + result;
        interval /= 30;
        result = QString ("%1 mons").arg (interval / 30, 2, 10, QLatin1Char ('0')) + " " + result;
        return result;
    }
    return QString::null;
}
