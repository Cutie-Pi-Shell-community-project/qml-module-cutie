#include "plugin.h"

MobileNetwork::MobileNetwork(QObject *parent) : QObject(parent) {
    qDBusRegisterMetaType<QMap<QString,QMap<QString,QVariant>>>();
    qDBusRegisterMetaType<OfonoServicePair>();
    qDBusRegisterMetaType<OfonoServiceList>();
    QDBusInterface networkManager(
	    "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager", 
	    "org.freedesktop.NetworkManager",
        QDBusConnection::systemBus()
    );

    QDBusReply<QList<QDBusObjectPath>> devicesReply = networkManager.call("GetDevices");
    if (!devicesReply.isValid()) return;
    QList<QDBusObjectPath> devices = devicesReply.value();

    m_path = QDBusObjectPath("/");
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
            if (type == 8) {
                m_path = path;
                break;
            }
        }
    }

    if (m_path.path() == "") return;
    
    QDBusInterface deviceInterface(
        "org.freedesktop.NetworkManager",
        m_path.path(), 
        "org.freedesktop.DBus.Properties",
        QDBusConnection::systemBus()
        );

    m_mobileDataEnabled = false;

    QDBusReply<QDBusVariant> actConReply = deviceInterface.call(
        "Get", "org.freedesktop.NetworkManager.Device", "ActiveConnection"
        );
    if (!actConReply.isValid()){
        qDebug()<<actConReply.error();
    } else {
        QDBusInterface actConIface(
            "org.freedesktop.NetworkManager",
            qdbus_cast<QDBusObjectPath>(actConReply.value().variant()).path(), 
            "org.freedesktop.DBus.Properties",
            QDBusConnection::systemBus()
        );
        QDBusReply<QDBusVariant> conReply = actConIface.call(
            "Get", "org.freedesktop.NetworkManager.Connection.Active", "Connection"
        );
        if (!conReply.isValid()){
            qDebug()<<conReply.error();
        } else {
            m_activeConnection = qdbus_cast<QDBusObjectPath>(conReply.value().variant());
            m_mobileDataEnabled = m_activeConnection.path() != "/";
            emit activeConnectionChanged(m_activeConnection.path());
            emit mobileDataEnabledChanged(m_mobileDataEnabled);
        }
    }

    QDBusReply<QDBusVariant> enabledReply = QDBusInterface(
        "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager", 
        "org.freedesktop.DBus.Properties",
        QDBusConnection::systemBus()
    ).call(
        "Get", "org.freedesktop.NetworkManager", "WwanEnabled"
    );
    m_cellularEnabled = enabledReply.isValid() 
        ? qdbus_cast<bool>(enabledReply.value().variant())
        : false;

    QDBusReply<QDBusVariant> interfaceReply = deviceInterface.call(
        "Get", "org.freedesktop.NetworkManager.Device", "Interface"
        );
    if (!interfaceReply.isValid()){
        qDebug()<<interfaceReply.error();
    } else {
        m_deviceId = qdbus_cast<QString>(interfaceReply.value().variant());
    }

    scanAvailableConnections();

    QDBusConnection::systemBus().connect(
        "org.freedesktop.NetworkManager",
        m_path.path(), 
        "org.freedesktop.DBus.Properties", 
        "PropertiesChanged",
        this, SLOT(onDevicePropertiesChanged(QString,QMap<QString, QVariant>,QStringList)));

    QDBusConnection::systemBus().connect(
        "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager", 
        "org.freedesktop.DBus.Properties", 
        "PropertiesChanged",
        this, SLOT(onPropertiesChanged(QString,QMap<QString, QVariant>,QStringList)));
}

MobileNetwork::~MobileNetwork() {}

QObject *MobileNetwork::provider(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(scriptEngine);
    return new MobileNetwork(engine);
}

bool MobileNetwork::mobileDataEnabled() {
    return m_mobileDataEnabled;
}

bool MobileNetwork::cellularEnabled() {
    return m_cellularEnabled;
}

QVariantList MobileNetwork::availableConnections(){
    return m_availableConnections;
}

QString MobileNetwork::activeConnection(){
    return m_activeConnection.path();
}

void MobileNetwork::setMobileDataEnabled(bool mobileDataEnabled) {
    if(!mobileDataEnabled){
        QDBusInterface(
            "org.freedesktop.NetworkManager",
            m_path.path(), 
            "org.freedesktop.NetworkManager.Device",
            QDBusConnection::systemBus()
        ).call("Disconnect");
        m_mobileDataEnabled = mobileDataEnabled;
        emit mobileDataEnabledChanged(m_mobileDataEnabled);
    } else {
        if (m_activeConnection.path() == "/")
            return;
        m_mobileDataEnabled = true;
        setActiveConnection(m_activeConnection.path());
        emit mobileDataEnabledChanged(m_mobileDataEnabled);
    }
}

void MobileNetwork::setCellularEnabled(bool cellularEnabled) {
    QDBusMessage message = QDBusMessage::createMethodCall(
        "org.freedesktop.NetworkManager", 
        "/org/freedesktop/NetworkManager", 
        "org.freedesktop.DBus.Properties",
        "Set");
    QList<QVariant> arguments;
    arguments << "org.freedesktop.NetworkManager" 
        << "WwanEnabled" 
        << QVariant::fromValue(
        QDBusVariant(cellularEnabled));
    message.setArguments(arguments);
    QDBusConnection::systemBus().call(message);
}

void MobileNetwork::setActiveConnection(QString path) {
    setMobileDataEnabled(false);

    QDBusReply<QDBusObjectPath> connsReply = QDBusInterface(
        "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager", 
        "org.freedesktop.NetworkManager",
        QDBusConnection::systemBus()
        ).call("ActivateConnection", 
        QDBusObjectPath(path), 
        m_path, 
        QDBusObjectPath("/"));

    if(!connsReply.isValid()){
        qDebug()<<connsReply.error();
    } else {
        m_activeConnection = QDBusObjectPath(path);
        scanAvailableConnections();
        foreach (QVariant connection, m_availableConnections) {
            if (connection.toMap().value("path").toString() == path) {
                syncOfonoContext(
                    connection.toMap().value("name").toString(), 
                    connection.toMap().value("apn").toString());
            }
        }
        emit activeConnectionChanged(m_activeConnection.path());
    }
}

QString MobileNetwork::addConnection(QString con_name, QString apn){ 
    bool wasMobileDataEnabled = m_mobileDataEnabled; 
    setMobileDataEnabled(false);

    QMap<QString,QMap<QString,QVariant>> data;
    QMap<QString,QVariant> conn;
    conn.insert("id", con_name);
    data.insert("connection", conn);

    QMap<QString,QVariant> gsm;
    gsm.insert("auto-config", false);
    gsm.insert("apn", apn);
    gsm.insert("device-id", m_deviceId);
    data.insert("gsm", gsm);

    QDBusReply<QDBusObjectPath> connsReply = QDBusInterface(
        "org.freedesktop.NetworkManager",
        "/org/freedesktop/NetworkManager/Settings", 
        "org.freedesktop.NetworkManager.Settings",
        QDBusConnection::systemBus()
        ).call("AddConnection", 
        QVariant::fromValue<QMap<QString,QMap<QString,QVariant>>>(data));

    if(!connsReply.isValid()){
        qDebug()<<connsReply.error();
    } else {
        scanAvailableConnections();
        syncOfonoContext(con_name, apn);
        emit mobileDataEnabledChanged(m_mobileDataEnabled);
        setMobileDataEnabled(wasMobileDataEnabled);
        return connsReply.value().path();
    }
    return "/";
}

void MobileNetwork::addAndActivateConnection(QString con_name, QString apn){ 
    QString conPath = addConnection(con_name, apn);
    setActiveConnection(conPath);
}

void MobileNetwork::updateConnection(QString path, QString con_name, QString apn){
    bool wasMobileDataEnabled = m_mobileDataEnabled;
    setMobileDataEnabled(false);

    QMap<QString,QMap<QString,QVariant>> data;

    QMap<QString,QVariant> conn;
    conn.insert("id", con_name);
    data.insert("connection", conn);

    QMap<QString,QVariant> gsm;
    gsm.insert("auto-config", false);
    gsm.insert("apn", apn);
    gsm.insert("device-id", m_deviceId);
    data.insert("gsm", gsm);
    QDBusInterface(
        "org.freedesktop.NetworkManager",
        path, 
        "org.freedesktop.NetworkManager.Settings.Connection",
        QDBusConnection::systemBus()
        ).call("Update", 
        QVariant::fromValue<QMap<QString,QMap<QString,QVariant>>>(data)
        );

    scanAvailableConnections();
    syncOfonoContext(con_name, apn);
    setMobileDataEnabled(wasMobileDataEnabled);
}

void MobileNetwork::deleteConnection(QString path){
    bool wasMobileDataEnabled = m_mobileDataEnabled;
    setMobileDataEnabled(false);
    QDBusInterface(
        "org.freedesktop.NetworkManager",
        path, 
        "org.freedesktop.NetworkManager.Settings.Connection",
        QDBusConnection::systemBus()
        ).call("Delete");

    if (m_activeConnection.path() == path) {
        m_activeConnection.setPath("/");
        activeConnectionChanged(m_activeConnection.path());
    } else {
        setMobileDataEnabled(wasMobileDataEnabled);
    }

    scanAvailableConnections();
}

void MobileNetwork::onDevicePropertiesChanged(QString iface, QMap<QString, QVariant> updated, QStringList invalidated) {
    Q_UNUSED(invalidated);
    if (iface == "org.freedesktop.NetworkManager.Device") {
        if (updated.contains("ActiveConnection")) {            
            QDBusInterface actConIface(
                "org.freedesktop.NetworkManager",
                qdbus_cast<QDBusObjectPath>(updated.value("ActiveConnection")).path(),
                "org.freedesktop.DBus.Properties",
                QDBusConnection::systemBus()
            );
            QDBusReply<QDBusVariant> conReply = actConIface.call(
                "Get", "org.freedesktop.NetworkManager.Connection.Active", "Connection"
            );
            if (!conReply.isValid()){
                qDebug()<<conReply.error();
                m_activeConnection = QDBusObjectPath("/");
            } else {
                m_activeConnection = qdbus_cast<QDBusObjectPath>(conReply.value().variant());
            }
            
            m_mobileDataEnabled = m_activeConnection.path() != "/";
            emit activeConnectionChanged(m_activeConnection.path());
            emit mobileDataEnabledChanged(m_mobileDataEnabled);
        }
    }
}

void MobileNetwork::onPropertiesChanged(QString iface, QMap<QString, QVariant> updated, QStringList invalidated) {
    Q_UNUSED(invalidated);
    if (iface == "org.freedesktop.NetworkManager.Device") {
        if (updated.contains("WwanEnabled")) {
            m_cellularEnabled = qdbus_cast<bool>(updated.value("WwanEnabled"));
            emit cellularEnabledChanged(m_cellularEnabled);
        }
    }
}

QMap<QString,QMap<QString,QVariant>> MobileNetwork::getConnectionSettings(QDBusObjectPath path){
    QDBusReply<QMap<QString,QMap<QString,QVariant>>> connsReply = QDBusInterface(
            "org.freedesktop.NetworkManager",
            path.path(), 
            "org.freedesktop.NetworkManager.Settings.Connection",
            QDBusConnection::systemBus()
        ).call("GetSettings");

    if (!connsReply.isValid()){
        qDebug() << connsReply.error();
        return QMap<QString,QMap<QString,QVariant>>();
    } else {
        return connsReply;
    }
}

void MobileNetwork::scanAvailableConnections(){
    QDBusInterface deviceInterface(
        "org.freedesktop.NetworkManager",
        m_path.path(), 
        "org.freedesktop.DBus.Properties",
        QDBusConnection::systemBus()
    );

    QDBusReply<QDBusVariant> availableCon = deviceInterface.call(
        "Get", "org.freedesktop.NetworkManager.Device", "AvailableConnections"
    );

    if (!availableCon.isValid()){
        qDebug() << availableCon.error();
    } else {
        QList<QDBusObjectPath> repList = qdbus_cast<QList<QDBusObjectPath>>(availableCon.value().variant());
        QVariantList conList;
        if(!repList.isEmpty()){
            foreach (QDBusObjectPath path, repList) {
                if (path.path() == "/") continue;
                QVariantMap conMap;
                QMap<QString,QMap<QString,QVariant>> settings = getConnectionSettings(path);
                conMap.insert("path", path.path());
                conMap.insert("name", settings.value("connection").value("id"));
                conMap.insert("apn", settings.value("gsm").value("apn"));
                conList << conMap;
            }
            m_availableConnections = conList;
            availableConnectionsChanged();
        }
    }
}

void MobileNetwork::syncOfonoContext(QString name, QString apn){
    QDBusPendingReply<OfonoServiceList> contexts = QDBusInterface(
        "org.ofono",
        "/ril_0", 
        "org.ofono.ConnectionManager",
        QDBusConnection::systemBus()
        ).call("GetContexts");
    contexts.waitForFinished();

    if (contexts.isValid()){
        foreach (QPair pair, contexts.value()) {
            QString contextPath = pair.first.path();
            if(pair.second.value("Type").toString() != "internet") continue;

            if(pair.second.value("AccessPointName").toString() != apn || 
                pair.second.value("Name").toString() != name){
                setOfonoContextProperty(contextPath, "Active", false);
                setOfonoContextProperty(contextPath, "AccessPointName", apn);
                setOfonoContextProperty(contextPath, "Name", name);
                setOfonoContextProperty(contextPath, "Active", true);
            }
        }
    } else {
        qDebug()<<contexts.error();
    }
}

void MobileNetwork::setOfonoContextProperty(QString path, QString property, QVariant value){
    QDBusInterface(
        "org.ofono",
        path, 
        "org.ofono.ConnectionContext",
        QDBusConnection::systemBus()
    ).call("SetProperty", property, QVariant::fromValue(QDBusVariant(value)));
}