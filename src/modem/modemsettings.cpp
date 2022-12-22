#include "modemsettings.h"
#include "ofonomodem.h"

ModemSettings::ModemSettings(QObject *parent) : QObject(parent) {
	qDBusRegisterMetaType<OfonoServicePair>();
	qDBusRegisterMetaType<OfonoServiceList>();
	QDBusReply<OfonoServiceList> ofonoModems = QDBusInterface(
		"org.ofono",
		"/", 
		"org.ofono.Manager",
		QDBusConnection::systemBus()
	).call("GetModems");
	if (ofonoModems.isValid()) {
		foreach (OfonoServicePair p, ofonoModems.value()) {
			OfonoModem *m = new OfonoModem();
			m->setPath(p.first.path());
			m_modems.insert(p.first.path(), m);
		}

		emit modemsChanged(m_modems.values());
	}
}

QList<CutieModem *> ModemSettings::modems() {
	return m_modems.values();
}

QObject *ModemSettings::provider(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(scriptEngine);
    return new ModemSettings(engine);
}