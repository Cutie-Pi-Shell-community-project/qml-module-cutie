#include <QDebug>
#include <QtQuick>
#include <QtQml/qqml.h>
#include <QtQml/QQmlExtensionPlugin>
#include "cutie_shell_interface.h"

class WifiSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QMap<QString,QVariant> activeConnection READ activeConnection NOTIFY activeConnectionChanged)
    Q_PROPERTY(QList<QMap<QString,QVariant>> connections READ connections NOTIFY connectionsChanged)
public:
    WifiSettings(QObject *parent=0);
    ~WifiSettings();

    QMap<QString,QVariant> activeConnection();
    QList<QMap<QString,QVariant>> connections();

    static QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine);
Q_SIGNALS:
    void activeConnectionChanged(QMap<QString,QVariant> activeConnection);
    void connectionsChanged(QList<QMap<QString,QVariant>>);
public Q_SLOTS:
    void onConnectionStrengthChanged(uchar strength);
    void onServicesChanged(QList<QDBusObjectPath> services);
    void onActiveServiceChanged(QDBusObjectPath activeService);
private:
    QDBusInterface *wifiDevice;
    QDBusObjectPath m_activePath;
    QMap<QString, QMap<QString,QVariant>> m_connections;
    QList<QDBusInterface *> m_connectionIfaces;

    void updateConnections(QList<QDBusObjectPath> netservices);
};