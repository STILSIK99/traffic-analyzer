#include "database.h"

//bool DataBase::connect (const QString &filename)
//{
//    QSqlDatabase::addDatabase (DB::DRIVER);
//    setDatabaseName (filename);
//    if (open()) {
//        close();
//        return true;
//    } else {
//        qDebug() << lastError();
//    }
//    return false;
//}

DataBase::DataBase (const QString &path)
{
    filename = path;
}

DataBase::~DataBase()
{
    if (db.isOpen()) db.close();
}

//----------------------------------PRIVATE------------------------------------

void DataBase::initDataBase()
{
    QSqlQuery query (db);
    for (auto request : DB::TABLES) {
        if (!query.exec (request)) {
            qDebug() << "Table not created.";
        }
    }
}


void DataBase::insertFile (const QString &filename)
{
    QSqlQuery query (db);
    if (!query.exec (DB::INSERT_FILE.arg (filename))) {
        qDebug() << query.lastError().text();
    }
    //    qDebug() << DB::INSERT_FILE.arg (filename);
    if (!query.exec (DB::SELECT_FILE.arg (filename))) {
        qDebug() << query.lastError().text();
    }
    if (query.first()) {
        fileIds[filename] = query.value (0).toInt();
    } else {
        query.lastError().text();
    }
}

QString DataBase::getFileId (const QString &path)
{
    if (!fileIds.count (path)) {
        insertFile (path);
    }
    return QString::number (fileIds.at (path));
}

void DataBase::insertRecord (std::list<QString> *data)
{
    static int counter = 0;
    qDebug() << ++counter;
    QString file_id = getFileId (data->front());
    data->pop_front();
    data->push_front (file_id);
    if (data == nullptr) return;
    QString body = "";
    int i = 0;
    for (auto &el : *data) {
        if (DB::isStrField[i++]) {
            body += "'" + el + "',";
        } else {
            body += el + ",";
        }
    }
    for (; i < DB::isStrField.size(); ++i) {
        if (DB::isStrField[i]) {
            body += "'NULL',";
        } else {
            body += "0,";
        }
    }
    body[body.size() - 1] = ' ';
    QSqlQuery query (db);
    if (!query.exec (DB::INSERT_DATA.arg (body))) {
        qDebug() << "Record not written.";
        qDebug() << query.lastError().text();
        qDebug() << DB::INSERT_DATA.arg (body);
    }
    delete data;
}

bool DataBase::isOpen()
{
    db = QSqlDatabase::addDatabase (DB::DRIVER);
    qDebug() << db.drivers();
    db.setDatabaseName (filename);
    if (!db.open()) {
        qDebug() << db.lastError();
        qDebug() << db.drivers();
        return false;
    }
    initDataBase();
    return db.isOpen();
}

void DataBase::finishFile (const QString &path)
{
    if (fileIds.count (path))
        fileIds.erase (path);
}
