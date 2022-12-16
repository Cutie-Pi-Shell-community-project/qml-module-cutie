#include <QDebug>
#include <QtQuick>
#include <QtQml/qqml.h>
#include <QtQml/QQmlExtensionPlugin>
#include "cutie_shell_interface.h"
#include "wifiaccesspoint.h"
#include "cutienetworkconnection.h"

class WifiSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<WifiAccessPoint *> accessPoints READ accessPoints NOTIFY accessPointsChanged)
    Q_PROPERTY(WifiAccessPoint *activeAccessPoint READ activeAccessPoint NOTIFY activeAccessPointChanged)
    Q_PROPERTY(QList<CutieNetworkConnection *> savedConnections READ savedConnections NOTIFY savedConnectionsChanged)
public:
    WifiSettings(QObject *parent=0);
    ~WifiSettings();

    QList<WifiAccessPoint *> accessPoints();
    WifiAccessPoint *activeAccessPoint();
    QList<CutieNetworkConnection *> savedConnections();

    Q_INVOKABLE void requestScan();
    Q_INVOKABLE void activateConnection(CutieNetworkConnection *connection, WifiAccessPoint *ap);

    static QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine);
Q_SIGNALS:
    void accessPointsChanged(QList<WifiAccessPoint *>);
    void activeAccessPointChanged(WifiAccessPoint*);
    void savedConnectionsChanged(QList<CutieNetworkConnection *>);
public Q_SLOTS:
    void onNewConnection(QDBusObjectPath path);
    void onConnectionRemoved(QDBusObjectPath path);
    void onAccessPointAdded(QDBusObjectPath path);
    void onAccessPointRemoved(QDBusObjectPath path);
    void onPropertiesChanged(QString iface, QMap<QString, QVariant> updated, QStringList invalidated);
private:
    QMap<QDBusObjectPath,WifiAccessPoint *> m_accessPoints;
    QDBusObjectPath m_activeAccessPoint;
    QDBusObjectPath m_wlanPath;
    QMap<QDBusObjectPath,CutieNetworkConnection *> m_savedConnections;
};