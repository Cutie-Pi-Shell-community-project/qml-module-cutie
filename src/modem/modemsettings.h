#pragma once
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusReply>
#include <QDBusMetaType>
#include "cutiemodem.h"

class ModemSettings : public QObject {
	Q_OBJECT
	Q_PROPERTY(QList<CutieModem *> modems READ modems NOTIFY modemsChanged)
public:
	ModemSettings(QObject *parent = 0);
	QList<CutieModem *> modems();

	static QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine);

Q_SIGNALS:
	void modemsChanged(QList<CutieModem *> modems);

private:
	QMap<QString,CutieModem *> m_modems;
};