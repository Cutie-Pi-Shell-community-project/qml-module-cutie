#include "ofonocall.h"

OfonoCall::OfonoCall(QObject *parent, QString path, QVariantMap props) : CutieCall(parent) {
	m_path = path;
	m_data = props;

	QDBusConnection::systemBus().connect(
		"org.ofono",
		m_path, 
		"org.ofono.VoiceCall", 
		"PropertyChanged",
		this, SLOT(onPropertyChanged(QString,QDBusVariant)));

	QDBusConnection::systemBus().connect(
		"org.ofono",
		m_path, 
		"org.ofono.VoiceCall", 
		"DisconnectReason",
		this, SLOT(onDisconnectReason(QString)));
}

OfonoCall::~OfonoCall() {}

void OfonoCall::onPropertyChanged(QString name, QDBusVariant value) {
	m_data.insert(name, value.variant());
	emit dataChanged(m_data);
}

void OfonoCall::onDisconnectReason(QString reason) {
	emit disconnected(reason);
}

void OfonoCall::answer() {
	QDBusInterface(
		"org.ofono",
		m_path, 
		"org.ofono.VoiceCall",
		QDBusConnection::systemBus()
	).call("Answer");
}

void OfonoCall::hangup() {
	QDBusInterface(
		"org.ofono",
		m_path, 
		"org.ofono.VoiceCall",
		QDBusConnection::systemBus()
	).call("Hangup");
}
