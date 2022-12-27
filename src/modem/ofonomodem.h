#pragma once
#include <QDebug>
#include <QtQuick>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusReply>
#include <QDBusMetaType>
#include "cutiemodem.h"

class OfonoModem : public CutieModem
{
    Q_OBJECT
    Q_PROPERTY (QString path READ path() NOTIFY pathChanged);
    Q_PROPERTY (QVariantMap data READ data() NOTIFY dataChanged);
    Q_PROPERTY (QVariantMap simData READ simData() NOTIFY simDataChanged);
public:
    OfonoModem(QObject *parent=0);
    ~OfonoModem();

    void setPath(QString path) override;
    Q_INVOKABLE void sendMessage(QString to, QString message) override;
Q_SIGNALS:
    void pathChanged(QString);
    void dataChanged(QVariantMap);
    void simDataChanged(QVariantMap);
	void incomingMessage(QString message, QVariantMap props);

public Q_SLOTS:
    void onPropertyChanged(QString name, QVariant value);
    void onSimPropertyChanged(QString name, QVariant value);
	void onIncomingMessage(QString message, QVariantMap props);

private:
    QString m_path;
    QVariantMap m_data;
    QVariantMap m_simData;
};

typedef QPair<QDBusObjectPath, QVariantMap> OfonoServicePair;
typedef QList<OfonoServicePair> OfonoServiceList;

Q_DECLARE_METATYPE(OfonoServicePair)
Q_DECLARE_METATYPE(OfonoServiceList)