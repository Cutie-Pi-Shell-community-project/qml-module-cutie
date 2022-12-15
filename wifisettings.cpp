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
	    "org.cutie_shell.SettingsDaemon.NetworkDevice",
        QDBusConnection::systemBus()
    );
    
    connect(wifiDevice, SIGNAL(ServicesChanged(QList<QDBusObjectPath>)), 
        this, SLOT(onServicesChanged(QList<QDBusObjectPath>))
    );

    QDBusInterface wifiDeviceProps(
	    "org.cutie_shell.SettingsDaemon",
        netdevices.at(0).path(), 
	    "org.freedesktop.DBus.Properties",
        QDBusConnection::systemBus()
    );

	QDBusReply<QMap<QString, QVariant>> propReply = wifiDeviceProps.call(
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
            "org.cutie_shell.SettingsDaemon.NetworkService",
            QDBusConnection::systemBus()
        );
        QDBusInterface dbusPropIface(
            "org.cutie_shell.SettingsDaemon",
            netservices.at(i).path(), 
            "org.freedesktop.DBus.Properties",
            QDBusConnection::systemBus()
        );
        QDBusReply<QMap<QString, QVariant>> reply = dbusPropIface.call(
            QLatin1String("GetAll"), 
            QString("org.cutie_shell.SettingsDaemon.NetworkService")
        );
        if (!reply.isValid()) continue;
        newConnections.insert(netservices.at(i).path(), reply.value());
        m_connectionIfaces.append(dbusIface);
        connect(dbusIface, SIGNAL(StrengthChanged(uchar)), 
            this, SLOT(onConnectionStrengthChanged(uchar))
        );
    }
    m_connections = newConnections;
    QList<QMap<QString,QVariant>> maps = m_connections.values();
    std::sort(maps.begin(), maps.end(), 
      [](const QMap<QString,QVariant>& a, const QMap<QString,QVariant>& b) -> bool { 
        return a.value("Strength").value<uchar>() > b.value("Strength").value<uchar>(); });
    emit connectionsChanged(maps);
}

QMap<QString,QVariant> WifiSettings::activeConnection() {
    return m_connections.value(m_activePath.path());
}

QList<QMap<QString,QVariant>> WifiSettings::connections() {
    QList<QMap<QString,QVariant>> maps = m_connections.values();
    std::sort(maps.begin(), maps.end(), 
      [](const QMap<QString,QVariant>& a, const QMap<QString,QVariant>& b) -> bool { 
        return a.value("Strength").value<uchar>() > b.value("Strength").value<uchar>(); });
    return maps;
}

void WifiSettings::onConnectionStrengthChanged(uchar strength) {
    QMap<QString,QVariant> props = m_connections.value(((QDBusInterface *)QObject::sender())->path());
    props.insert("Strength", strength);
    m_connections.insert(((QDBusInterface *)QObject::sender())->path(), props);
    QList<QMap<QString,QVariant>> maps = m_connections.values();
    std::sort(maps.begin(), maps.end(), 
    [](const QMap<QString,QVariant>& a, const QMap<QString,QVariant>& b) -> bool { 
        return a.value("Strength").value<uchar>() > b.value("Strength").value<uchar>(); });
    emit connectionsChanged(maps);
    if (((QDBusInterface *)QObject::sender())->path().compare(m_activePath.path()) == 0)
        emit activeConnectionChanged(props);
}

void WifiSettings::onServicesChanged(QList<QDBusObjectPath> services) {
    updateConnections(services);
}

void WifiSettings::onActiveServiceChanged(QDBusObjectPath activeService) {
    m_activePath = activeService;
    emit activeConnectionChanged(activeConnection());
}

QObject *WifiSettings::provider(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(scriptEngine);
    return new WifiSettings(engine);
}

