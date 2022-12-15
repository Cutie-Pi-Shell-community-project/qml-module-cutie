#include "plugin.h"

Q_DECLARE_METATYPE(QList<QDBusObjectPath>)

WifiSettings::WifiSettings(QObject *parent) : QObject(parent) {
    qDBusRegisterMetaType<QList<QDBusObjectPath> >();
    QDBusInterface netIface(
	    "org.cutie_shell.SettingsDaemon",
        "/networking", 
	    "org.freedesktop.DBus.Properties",
        QDBusConnection::systemBus()
    );
	QDBusReply<QDBusVariant> reply = netIface.call(
        QLatin1String("Get"), 
        QString("org.cutie_shell.SettingsDaemon.Networking"),
        QString("Backends")
    );
    if (!reply.isValid()) return;
    QList<QDBusObjectPath> netbackends = qdbus_cast<QList<QDBusObjectPath>>(reply.value().variant());
    if (netbackends.size() < 1) return;
    QDBusInterface backendIface(
	    "org.cutie_shell.SettingsDaemon",
        netbackends.at(0).path(), 
	    "org.freedesktop.DBus.Properties",
        QDBusConnection::systemBus()
    );
	reply = backendIface.call(
        QLatin1String("Get"), 
        QString("org.cutie_shell.SettingsDaemon.NetworkBackend"),
        QString("Devices")
    );
    if (!reply.isValid()) return;
    QList<QDBusObjectPath> netdevices = qdbus_cast<QList<QDBusObjectPath>>(reply.value().variant());
    if (netdevices.size() < 1) return;
    wifiDevice = new QDBusInterface(
	    "org.cutie_shell.SettingsDaemon",
        netdevices.at(0).path(), 
	    "org.freedesktop.DBus.Properties",
        QDBusConnection::systemBus()
    );

    QObject::connect(
        wifiDevice, SIGNAL(PropertiesChanged(QString,QMap<QString,QVariant>,QStringList)),
        this, SLOT(onDevicePropertiesChanged(QString,QMap<QString,QVariant>,QStringList)));

	QDBusReply<QMap<QString, QVariant>> propReply = wifiDevice->call(
        QLatin1String("GetAll"), 
        QString("org.cutie_shell.SettingsDaemon.NetworkDevice")
    );
    if (!propReply.isValid()) return;
    if (propReply.value().contains("Services")) {
        QList<QDBusObjectPath> netservices = qdbus_cast<QList<QDBusObjectPath>>(propReply.value().value("Services"));
        updateConnections(netservices);
    }

    if (propReply.value().contains("ActiveService")) {
        m_activePath = qdbus_cast<QDBusObjectPath>(propReply.value().value("ActiveService"));
        emit activeConnectionChanged(activeConnection());
    }
}

WifiSettings::~WifiSettings() {}

void WifiSettings::updateConnections(QList<QDBusObjectPath> netservices) {
    QMap<QString, QMap<QString,QVariant>> newConnections;
    m_connectionIfaces.clear();
    for (int i = 0; i < netservices.count(); i++) {
        QDBusInterface *dbusIface = new QDBusInterface(
            "org.cutie_shell.SettingsDaemon",
            netservices.at(i).path(), 
            "org.freedesktop.DBus.Properties",
            QDBusConnection::systemBus()
        );
        QDBusReply<QMap<QString, QVariant>> reply = dbusIface->call(
            QLatin1String("GetAll"), 
            QString("org.cutie_shell.SettingsDaemon.NetworkService")
        );
        if (!reply.isValid()) continue;
        newConnections.insert(netservices.at(i).path(), reply.value());
        m_connectionIfaces.append(dbusIface);
        QObject::connect(
            dbusIface, SIGNAL(PropertiesChanged(QString,QMap<QString,QVariant>,QStringList)),
            this, SLOT(onConnectionPropertiesChanged(QString,QMap<QString,QVariant>,QStringList)));
    }
    m_connections = newConnections;
    emit connectionsChanged(m_connections.values());
}

QMap<QString,QVariant> WifiSettings::activeConnection() {
    return m_connections.value(m_activePath.path());
}

QList<QMap<QString,QVariant>> WifiSettings::connections() {
    return m_connections.values();
}

void WifiSettings::onConnectionPropertiesChanged(QString iface, QMap<QString,QVariant> updated, QStringList invalidated) {
    Q_UNUSED(invalidated);
    if (iface == "org.cutie_shell.SettingsDaemon.NetworkService") {
        QMap<QString,QVariant> props = m_connections.value(((QDBusInterface *)QObject::sender())->path());
        foreach (QString k, updated.keys())
            props.insert(k, updated.value(k));
        m_connections.insert(((QDBusInterface *)QObject::sender())->path(), props);
        emit connectionsChanged(m_connections.values());
        if (((QDBusInterface *)QObject::sender())->path().compare(m_activePath.path()) == 0)
            emit activeConnectionChanged(props);
    }
}

void WifiSettings::onDevicePropertiesChanged(QString iface, QMap<QString,QVariant> updated, QStringList invalidated) {
    Q_UNUSED(invalidated);
    if (iface == "org.cutie_shell.SettingsDaemon.NetworkDevice") {
        if (updated.contains("Services")) {
            updateConnections(qdbus_cast<QList<QDBusObjectPath>>(updated.value("Services")));
        }
        if (updated.contains("ActiveService")) {
            m_activePath = qdbus_cast<QDBusObjectPath>(updated.value("ActiveService"));
            emit activeConnectionChanged(activeConnection());
        }
    }
}

QObject *WifiSettings::provider(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(scriptEngine);
    return new WifiSettings(engine);
}

