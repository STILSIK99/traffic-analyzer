#pragma once

#include <QString>
#include <set>
#include <vector>

typedef unsigned short u_short;
typedef unsigned char u_char;

namespace DB
{

    const QString DRIVER = "QSQLITE";
    //    const QString DRIVER_2 = "SQLITE";
    const QString FILEPATH = "result.db";
    const std::vector<QString> TABLES = {
        "CREATE TABLE IF NOT EXISTS Files ("
        "id integer primary key,"
        "path text);",
        "CREATE TABLE IF NOT EXISTS Data ("
        "file_id integer,"
        "packet_id integer,"
        "time datetime,"
        "src_mac text,"
        "dest_mac text,"
        "eth_protocol text,"
        "src_ip text,"
        "dest_ip text,"
        "ip_protocol text,"
        "src_port text,"
        "dest_port text,"
        "data_size int);"
    };

    const QString INSERT_FILE = "INSERT INTO Files VALUES (null, '%1');";
    const QString SELECT_FILE = "SELECT id FROM Files WHERE path = '%1';";
    const QString INSERT_DATA = "INSERT INTO Data VALUES (%1);";

    const std::vector<bool> isStrField = {
        0, 0, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 0
    };

}


namespace PCAP
{
    namespace ETHERTYPES
    {
        const u_short IPv4 = 0x0800;
    }

    namespace IPTYPES
    {
        const u_char TCP = 0x06;
        const u_char UDP = 0x11;
    }

}
