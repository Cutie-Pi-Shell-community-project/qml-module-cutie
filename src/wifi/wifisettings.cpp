#include "plugin.h"
#include <QDBusMetaType>

WifiSettings::WifiSettings(QObject *parent) : QObject(parent) {
    qDBusRegisterMetaType<QMap<QString,QMap<QString,QVariant>>>();
    QDBusInterface networkManager(
	    "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager", 
	    "org.freedesktop.NetworkManager",
        QDBusConnection::systemBus()
    );

    QDBusInterface(
	    "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager/AgentManager", 
	    "org.freedesktop.NetworkManager.AgentManager",
        QDBusConnection::systemBus()
    ).call(
        "Register", "org.cutie_shell"
    );

    QDBusReply<QDBusVariant> enabledReply = QDBusInterface(
	    "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager", 
	    "org.freedesktop.DBus.Properties",
        QDBusConnection::systemBus()
    ).call(
        "Get", "org.freedesktop.NetworkManager", "WirelessEnabled"
    );
    m_wirelessEnabled = enabledReply.isValid() 
        ? qdbus_cast<bool>(enabledReply.value().variant())
        : false;

    QDBusReply<QList<QDBusObjectPath>> devicesReply = networkManager.call("GetDevices");
    if (!devicesReply.isValid()) return;
    QList<QDBusObjectPath> devices = devicesReply.value();

    m_wlanPath = QDBusObjectPath("/");
    foreach (QDBusObjectPath path, devices) {
        QDBusInterface deviceInterface(
            "org.freedesktop.NetworkManager",
            path.path(), 
            "org.freedesktop.DBus.Properties",
            QDBusConnection::systemBus()
        );
        QDBusReply<QDBusVariant> typeReply = deviceInterface.call(
            "Get", "org.freedesktop.NetworkManager.Device", "DeviceType"
        );
        if (typeReply.isValid()) {
            uint type = qdbus_cast<uint>(typeReply.value().variant());
            if (type == 2) { // Wireless LAN
                m_wlanPath = path;
                break;
            }
        }
    }

    if (m_wlanPath.path() == "") return;
    
    QDBusInterface deviceInterface(
        "org.freedesktop.NetworkManager",
        m_wlanPath.path(), 
        "org.freedesktop.DBus.Properties",
        QDBusConnection::systemBus()
    );
    QDBusReply<QDBusVariant> apReply = deviceInterface.call(
        "Get", "org.freedesktop.NetworkManager.Device.Wireless", "AccessPoints"
    );

    if (!apReply.isValid()) return;
    foreach (QDBusObjectPath path, qdbus_cast<QList<QDBusObjectPath>>(apReply.value().variant())) {
        if (path.path() == "/") continue;
        WifiAccessPoint* wifiAP = new WifiAccessPoint(this);
        wifiAP->setPath(path.path());
        m_accessPoints.insert(path, wifiAP);
        emit accessPointsChanged(accessPoints());
    }

    apReply = deviceInterface.call(
        "Get", "org.freedesktop.NetworkManager.Device.Wireless", "ActiveAccessPoint"
    );
    if (apReply.isValid()) {
        m_activeAccessPoint = qdbus_cast<QDBusObjectPath>(apReply.value().variant());
        emit activeAccessPointChanged(m_accessPoints.value(m_activeAccessPoint));
    }

    QDBusReply<QList<QDBusObjectPath>> connsReply = QDBusInterface(
	    "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager/Settings", 
	    "org.freedesktop.NetworkManager.Settings",
        QDBusConnection::systemBus()
    ).call("ListConnections");

    if (connsReply.isValid()) {
        foreach (QDBusObjectPath path, connsReply.value()) {
            if (path.path() == "/") continue;
            CutieNetworkConnection* nconn = new CutieNetworkConnection(this);
            nconn->setPath(path.path());
            if (qdbus_cast<QString>(qdbus_cast<QMap<QString,QVariant>>(nconn->data().value("connection")).value("type")) == "802-11-wireless") {
                m_savedConnections.insert(path, nconn);
                emit savedConnectionsChanged(savedConnections());
            }
        }
    }

    QDBusConnection::systemBus().connect(
        "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager", 
        "org.freedesktop.DBus.Properties", 
        "PropertiesChanged",
        this, SLOT(onPropertiesChanged(QString,QMap<QString, QVariant>,QStringList)));

    QDBusConnection::systemBus().connect(
        "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager/Settings", 
        "org.freedesktop.NetworkManager.Settings", 
        "NewConnection",
        this, SLOT(onNewConnection(QDBusObjectPath)));

    QDBusConnection::systemBus().connect(
        "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager/Settings", 
        "org.freedesktop.NetworkManager.Settings", 
        "ConnectionRemoved",
        this, SLOT(onConnectionRemoved(QDBusObjectPath)));

    QDBusConnection::systemBus().connect(
        "org.freedesktop.NetworkManager",
        m_wlanPath.path(), 
        "org.freedesktop.NetworkManager.Device.Wireless", 
        "AccessPointAdded",
        this, SLOT(onAccessPointAdded(QDBusObjectPath)));

    QDBusConnection::systemBus().connect(
        "org.freedesktop.NetworkManager",
        m_wlanPath.path(), 
        "org.freedesktop.NetworkManager.Device.Wireless", 
        "AccessPointRemoved",
        this, SLOT(onAccessPointRemoved(QDBusObjectPath)));

    QDBusConnection::systemBus().connect(
        "org.freedesktop.NetworkManager",
        m_wlanPath.path(), 
        "org.freedesktop.DBus.Properties", 
        "PropertiesChanged",
        this, SLOT(onDevicePropertiesChanged(QString,QMap<QString, QVariant>,QStringList)));
}

WifiSettings::~WifiSettings() {}

QList<WifiAccessPoint *> WifiSettings::accessPoints() {
    QList<WifiAccessPoint *> aps = m_accessPoints.values();
    std::sort(aps.begin(), aps.end(), 
      [](WifiAccessPoint* const a, WifiAccessPoint* const b) -> bool { 
        return (qdbus_cast<uint>(a->data().value("Strength")) > qdbus_cast<uint>(b->data().value("Strength"))); });
    return aps;
}

WifiAccessPoint *WifiSettings::activeAccessPoint() {
    return m_accessPoints.value(m_activeAccessPoint);
}

QList<CutieNetworkConnection *> WifiSettings::savedConnections() {
    return m_savedConnections.values();
}

void WifiSettings::onNewConnection(QDBusObjectPath path) {
    CutieNetworkConnection* nconn = new CutieNetworkConnection(this);
    nconn->setPath(path.path());
    m_savedConnections.insert(path, nconn);
    emit savedConnectionsChanged(savedConnections());
}

void WifiSettings::onConnectionRemoved(QDBusObjectPath path) {
    m_savedConnections.remove(path);
    emit savedConnectionsChanged(savedConnections());
}

void WifiSettings::onAccessPointAdded(QDBusObjectPath path) {
    WifiAccessPoint* wifiAP = new WifiAccessPoint(this);
    wifiAP->setPath(path.path());
    m_accessPoints.insert(path, wifiAP);
    emit accessPointsChanged(accessPoints());
}

void WifiSettings::onAccessPointRemoved(QDBusObjectPath path) {
    m_accessPoints.remove(path);
    emit accessPointsChanged(accessPoints());
}

QObject *WifiSettings::provider(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(scriptEngine);
    return new WifiSettings(engine);
}

void WifiSettings::onPropertiesChanged(QString iface, QMap<QString, QVariant> updated, QStringList invalidated) {
    Q_UNUSED(invalidated);
    if (iface == "org.freedesktop.NetworkManager") {
        if (updated.contains("WirelessEnabled")) {
            m_wirelessEnabled = qdbus_cast<bool>(updated.value("WirelessEnabled"));
            emit wirelessEnabledChanged(m_wirelessEnabled);
        }
    };
}

void WifiSettings::onDevicePropertiesChanged(QString iface, QMap<QString, QVariant> updated, QStringList invalidated) {
    Q_UNUSED(invalidated);
    if (iface == "org.freedesktop.NetworkManager.Device.Wireless") {
        if (updated.contains("ActiveAccessPoint")) {
            m_activeAccessPoint = qdbus_cast<QDBusObjectPath>(updated.value("ActiveAccessPoint"));
            emit activeAccessPointChanged(m_accessPoints.value(m_activeAccessPoint));
        }
    };
}

void WifiSettings::requestScan() {
    QDBusInterface(
        "org.freedesktop.NetworkManager",
        m_wlanPath.path(), 
        "org.freedesktop.NetworkManager.Device.Wireless",
        QDBusConnection::systemBus()
    ).call("RequestScan", QMap<QString,QVariant>());
}

void WifiSettings::activateConnection(CutieNetworkConnection *connection, WifiAccessPoint *ap) {
    QDBusInterface(
        "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager", 
        "org.freedesktop.NetworkManager",
        QDBusConnection::systemBus()
    ).call("ActivateConnection", 
        QDBusObjectPath(connection->path()), 
        QDBusObjectPath(m_wlanPath.path()), 
        QDBusObjectPath(ap ? ap->path() : "/"));
}

void WifiSettings::addAndActivateConnection(WifiAccessPoint *ap, QString psk) {
    QMap<QString,QMap<QString,QVariant>> data;

    QMap<QString,QVariant> wireless;
    wireless.insert("id", qdbus_cast<QString>(ap->data().value("Ssid")));
    data.insert("connection", wireless);

    if (psk != "") {
        QMap<QString,QVariant> security;
        security.insert("psk", psk);
        data.insert("802-11-wireless-security", security);
    }

    QDBusInterface(
        "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager", 
        "org.freedesktop.NetworkManager",
        QDBusConnection::systemBus()
    ).call("AddAndActivateConnection", 
        QVariant::fromValue<QMap<QString,QMap<QString,QVariant>>>(data), 
        QDBusObjectPath(m_wlanPath.path()), 
        QDBusObjectPath(ap->path()));
}

bool WifiSettings::wirelessEnabled() {
    return m_wirelessEnabled;
}

void WifiSettings::setWirelessEnabled(bool wirelessEnabled) {
    m_wirelessEnabled = wirelessEnabled;
    QDBusMessage message = QDBusMessage::createMethodCall(
        "org.freedesktop.NetworkManager", 
        "/org/freedesktop/NetworkManager", 
	    "org.freedesktop.DBus.Properties",
        "Set");
    QList<QVariant> arguments;
    arguments << "org.freedesktop.NetworkManager" 
        << "WirelessEnabled" 
        << QVariant::fromValue(
        QDBusVariant(m_wirelessEnabled));
    message.setArguments(arguments);
    QDBusConnection::systemBus().call(message);
}
