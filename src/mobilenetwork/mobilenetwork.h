#pragma once
#include <QDebug>
#include <QtQuick>
#include <QtQml/qqml.h>
#include <QtQml/QQmlExtensionPlugin>
#include <QDBusObjectPath>

class MobileNetwork : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool mobileDataEnabled READ mobileDataEnabled WRITE setMobileDataEnabled NOTIFY mobileDataEnabledChanged)
    Q_PROPERTY(bool cellularEnabled READ cellularEnabled WRITE setCellularEnabled NOTIFY cellularEnabledChanged)
    Q_PROPERTY(QVariantList availableConnections READ availableConnections NOTIFY availableConnectionsChanged)
    Q_PROPERTY(QString activeConnection READ activeConnection WRITE setActiveConnection NOTIFY activeConnectionChanged)

public:
    MobileNetwork(QObject *parent=0);
    ~MobileNetwork();
    
    bool mobileDataEnabled();
    bool cellularEnabled();
    QVariantList availableConnections();
    QString activeConnection();

    void setMobileDataEnabled(bool mobileDataEnabled);
    void setCellularEnabled(bool cellularEnabled);
    void setActiveConnection(QString path);
    Q_INVOKABLE void addAndActivateConnection(QString con_name, QString apn);
    Q_INVOKABLE QString addConnection(QString con_name, QString apn);
    Q_INVOKABLE void updateConnection(QString path, QString con_name, QString apn);
    Q_INVOKABLE void deleteConnection(QString path);

    static QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine);

Q_SIGNALS:
    void mobileDataEnabledChanged(bool);
    void availableConnectionsChanged();
    void cellularEnabledChanged(bool);
    void activeConnectionChanged(QString);

public Q_SLOTS:
    void onDevicePropertiesChanged(QString iface, QMap<QString, QVariant> updated, QStringList invalidated);
    void onPropertiesChanged(QString iface, QMap<QString, QVariant> updated, QStringList invalidated);

private:
    QDBusObjectPath m_path;
    QString m_deviceId;
    QDBusObjectPath m_activeConnection;
    bool m_mobileDataEnabled;
    bool m_cellularEnabled;

    QVariantList m_availableConnections;
    QMap<QString,QMap<QString,QVariant>> getConnectionSettings(QDBusObjectPath path);
    void scanAvailableConnections();
    void syncOfonoContext(QString name, QString apn);
    void setOfonoContextProperty(QString path, QString property, QVariant value);
};

typedef QPair<QDBusObjectPath, QVariantMap> OfonoServicePair;
typedef QList<OfonoServicePair> OfonoServiceList;

Q_DECLARE_METATYPE(OfonoServicePair)
Q_DECLARE_METATYPE(OfonoServiceList)
