#include "notifications.h"

Notifications::Notifications(QObject *parent) : QObject(parent) {}

Notifications::~Notifications() {}

uint Notifications::notify(QString appName, uint replacesId, QString appIcon, QString summary, QString body, QStringList actions, QVariantMap hints, int expireTimeout) {
    QDBusReply<uint> idReply = QDBusInterface(
		"org.freedesktop.Notifications",
		"/org/freedesktop/Notifications", 
		"org.freedesktop.Notifications",
		QDBusConnection::sessionBus()
	).call("Notify", appName, replacesId, appIcon, summary, body, actions, hints, expireTimeout);
    qDebug() << idReply.error().name() << idReply.error().message();
    return idReply.isValid() ? idReply.value() : 0;
}

QObject *Notifications::provider(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(scriptEngine);
    return new Notifications(engine);
}