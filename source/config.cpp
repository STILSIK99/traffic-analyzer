#include "config.h"

Config::Config (const QString &filename)
{
    path = filename;
}

void Config::init()
{
    QFile f (path);
    f.open (QIODevice::ReadOnly);
    if (!f.isOpen()) throw EXCEPTIONS::Access (path.toStdString());
    QJsonObject *obj = new QJsonObject (QJsonDocument::fromJson (f.readAll()).object());
    parseCfg (obj);
    delete obj;
}

void Config::parseCfg (const QJsonObject *cfg)
{
    //read Attributes from configuration file
    if (cfg->contains ("Attibutes")) {
        if ((*cfg)["Attibutes"].isObject()) {
            const auto attr = (*cfg)["Attibutes"].toObject();
            for (auto key : attr.keys()) {
                if (attr[key].isArray()) {
                    for (auto el : attr[key].toArray()) {
                        if (!el.isString()) continue;
                        if (attributes.count (key) == 0) {
                            attributes[key] = std::set<QString>();
                        }
                        attributes[key].insert (el.toString());
                    }
                }
            }
        }
    }
    //read Types from configuration file
    if ((*cfg).contains ("Type")) {
        if ((*cfg)["Type"].isObject()) {
            const auto type = (*cfg)["Type"].toObject();
            //перебор протоколов
            for (auto key : type.keys()) {
                if (type[key].isObject()) {
                    //protocol - объект в котором поля соответствуют определенным портам
                    auto protocol = type[key].toObject();
                    if (types.count (key) == 0) {
                        types[key] = std::map<u_short, QString>();
                    }
                    //kkey - тип
                    for (auto kkey : protocol.keys()) {
                        if (protocol[kkey].isDouble()) {
                            types[key][protocol[kkey].toInt()] = kkey;
                        }
                        if (protocol[kkey].isArray()) {
                            auto arr = protocol[kkey].toArray();
                            for (auto el : arr) {
                                types[key][el.toInt()] = kkey;
                            }
                        }
                    }
                }
            }
        }
    }
    auto req = {"ethernet", "ip", "tcp", "http"};
    for (auto k : req) {
        if (attributes.count (k) == 0) {
            attributes[k] = {};
        }
    }
}
