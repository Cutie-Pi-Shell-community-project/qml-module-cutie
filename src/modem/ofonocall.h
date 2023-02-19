#pragma once
#include <QDebug>
#include <QtQuick>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusReply>
#include <QDBusMetaType>
#include "cutiecall.h"

class OfonoCall : public CutieCall
{
    Q_OBJECT
    Q_PROPERTY (QString path READ path() NOTIFY pathChanged);
    Q_PROPERTY (QVariantMap data READ data() NOTIFY dataChanged);
public:
    OfonoCall(QObject *parent, QString path, QVariantMap props);
    ~OfonoCall();

    Q_INVOKABLE void answer() override;
    Q_INVOKABLE void hangup() override;
    
Q_SIGNALS:
    void pathChanged(QString);
    void dataChanged(QVariantMap);
    void disconnected(QString);

public Q_SLOTS:
    void onPropertyChanged(QString name, QDBusVariant value);
    void onDisconnectReason(QString reason);
};