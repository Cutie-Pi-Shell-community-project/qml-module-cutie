#include "cutienetworkconnection.h"

CutieNetworkConnection::CutieNetworkConnection(QObject *parent) : QObject(parent) {}

CutieNetworkConnection::~CutieNetworkConnection() {}

void CutieNetworkConnection::setPath(QString path) {
    m_path = path;
    QDBusConnection::systemBus().connect(
        "org.freedesktop.NetworkManager",
        path, 
        "org.freedesktop.NetworkManager.Settings.Connection", 
        "Updated",
        this, SLOT(onUpdated()));
    emit pathChanged(path);
    QDBusMessage reply = QDBusInterface(
        "org.freedesktop.NetworkManager",
        path, 
        "org.freedesktop.NetworkManager.Settings.Connection",
        QDBusConnection::systemBus()
    ).call("GetSettings");
    m_data = QMap<QString,QMap<QString,QVariant>>();
    const QDBusArgument &dbusArg = reply.arguments().at( 0 ).value<QDBusArgument>();
    dbusArg >> m_data;
    emit dataChanged(data());
}

QString CutieNetworkConnection::path() {
    return m_path;
}

QMap<QString,QVariant> CutieNetworkConnection::data() {
    QMap<QString,QVariant> map;
    foreach (QString k, m_data.keys()) {
        map.insert(k, QVariant(m_data.value(k)));
    }
    return map;
}

void CutieNetworkConnection::onUpdated() {
    QDBusReply<QMap<QString,QMap<QString,QVariant>>> connReply = QDBusInterface(
        "org.freedesktop.NetworkManager",
        m_path, 
        "org.freedesktop.NetworkManager.Settings.Connection",
        QDBusConnection::systemBus()
    ).call("GetSettings");
    m_data = QMap<QString,QMap<QString,QVariant>>();
    if (connReply.isValid()) {
        m_data = connReply.value();
    }
    emit dataChanged(data());
}