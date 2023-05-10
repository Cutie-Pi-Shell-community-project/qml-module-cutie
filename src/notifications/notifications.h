#pragma once
#include <QDebug>
#include <QtQuick>
#include <QtQml/qqml.h>
#include <QtQml/QQmlExtensionPlugin>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusReply>

class Notifications : public QObject
{
    Q_OBJECT
public:
    Notifications(QObject *parent=0);

    ~Notifications();

    Q_INVOKABLE uint notify(QString appName, uint replacesId, QString appIcon, QString summary, QString body, QStringList actions, QVariantMap hints, int expireTimeout);

    static QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine);
};