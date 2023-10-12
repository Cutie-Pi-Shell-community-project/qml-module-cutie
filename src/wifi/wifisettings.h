#pragma once
#include <QDebug>
#include <QtQuick>
#include <QtQml/qqml.h>
#include <QtQml/QQmlExtensionPlugin>
#include <QDBusObjectPath>
#include "wifiaccesspoint.h"
#include "cutienetworkconnection.h"

class WifiSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<WifiAccessPoint *> accessPoints READ accessPoints NOTIFY accessPointsChanged)
    Q_PROPERTY(WifiAccessPoint *activeAccessPoint READ activeAccessPoint NOTIFY activeAccessPointChanged)
    Q_PROPERTY(QList<CutieNetworkConnection *> savedConnections READ savedConnections NOTIFY savedConnectionsChanged)
    Q_PROPERTY(bool wirelessEnabled READ wirelessEnabled WRITE setWirelessEnabled NOTIFY wirelessEnabledChanged)
public:
    WifiSettings(QObject *parent=0);
    ~WifiSettings();

    QList<WifiAccessPoint *> accessPoints();
    WifiAccessPoint *activeAccessPoint();
    QList<CutieNetworkConnection *> savedConnections();
    bool wirelessEnabled();

    void setWirelessEnabled(bool wirelessEnabled);

    Q_INVOKABLE void requestScan();
    Q_INVOKABLE void activateConnection(CutieNetworkConnection *connection, WifiAccessPoint *ap);
    Q_INVOKABLE void addAndActivateConnection(WifiAccessPoint *ap, QString psk);

    static QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine);
Q_SIGNALS:
    void accessPointsChanged(QList<WifiAccessPoint *>);
    void activeAccessPointChanged(WifiAccessPoint*);
    void savedConnectionsChanged(QList<CutieNetworkConnection *>);
    void wirelessEnabledChanged(bool);
public Q_SLOTS:
    void onNewConnection(QDBusObjectPath path);
    void onConnectionRemoved(QDBusObjectPath path);
    void onAccessPointAdded(QDBusObjectPath path);
    void onAccessPointRemoved(QDBusObjectPath path);
    void onPropertiesChanged(QString iface, QMap<QString, QVariant> updated, QStringList invalidated);
    void onDevicePropertiesChanged(QString iface, QMap<QString, QVariant> updated, QStringList invalidated);
private:
    QMap<QDBusObjectPath,WifiAccessPoint *> m_accessPoints;
    QDBusObjectPath m_activeAccessPoint;
    QDBusObjectPath m_wlanPath;
    QMap<QDBusObjectPath,CutieNetworkConnection *> m_savedConnections;
    bool m_wirelessEnabled;
};