#pragma once
#include <QDebug>
#include <QtQuick>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusReply>
#include <QDBusMetaType>
#include "cutiemodem.h"
#include "ofonocall.h"

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
    Q_INVOKABLE QString dial(QString to, QString hideID = QString()) override;
Q_SIGNALS:
    void pathChanged(QString);
    void dataChanged(QVariantMap);
    void simDataChanged(QVariantMap);
	void incomingMessage(QString message, QVariantMap props);
	void newCall(OfonoCall* call);

public Q_SLOTS:
    void onPropertyChanged(QString name, QVariant value);
    void onSimPropertyChanged(QString name, QVariant value);
	void onIncomingMessage(QString message, QVariantMap props);
	void onCallAdded(QDBusObjectPath path, QVariantMap props);
	void onCallRemoved(QDBusObjectPath path);
};

typedef QPair<QDBusObjectPath, QVariantMap> OfonoServicePair;
typedef QList<OfonoServicePair> OfonoServiceList;

Q_DECLARE_METATYPE(OfonoServicePair)
Q_DECLARE_METATYPE(OfonoServiceList)