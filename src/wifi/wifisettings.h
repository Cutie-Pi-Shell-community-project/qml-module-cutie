#include <QDebug>
#include <QtQuick>
#include <QtQml/qqml.h>
#include <QtQml/QQmlExtensionPlugin>
#include "cutie_shell_interface.h"
#include "wifiaccesspoint.h"

class WifiSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<WifiAccessPoint *> accessPoints READ accessPoints NOTIFY accessPointsChanged)
    Q_PROPERTY(WifiAccessPoint *activeAccessPoint READ activeAccessPoint NOTIFY activeAccessPointChanged)
public:
    WifiSettings(QObject *parent=0);
    ~WifiSettings();

    QList<WifiAccessPoint *> accessPoints();
    WifiAccessPoint *activeAccessPoint();

    Q_INVOKABLE void requestScan();

    static QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine);
Q_SIGNALS:
    void accessPointsChanged(QList<WifiAccessPoint *>);
    void activeAccessPointChanged(WifiAccessPoint*);
public Q_SLOTS:
    void onAccessPointAdded(QDBusObjectPath path);
    void onAccessPointRemoved(QDBusObjectPath path);
    void onPropertiesChanged(QString iface, QMap<QString, QVariant> updated, QStringList invalidated);
private:
    QMap<QDBusObjectPath,WifiAccessPoint *> m_accessPoints;
    QDBusObjectPath m_activeAccessPoint;
    QDBusObjectPath m_wlanPath;
};