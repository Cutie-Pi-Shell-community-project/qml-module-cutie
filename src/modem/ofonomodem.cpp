#include "ofonomodem.h"

OfonoModem::OfonoModem(QObject *parent) : CutieModem(parent) {}

OfonoModem::~OfonoModem() {}

void OfonoModem::setPath(QString path) {
	m_path = path;
	
	QDBusReply<QVariantMap> props = QDBusInterface(
		"org.ofono",
		m_path, 
		"org.ofono.Modem",
		QDBusConnection::systemBus()
	).call("GetProperties");
	if (props.isValid())
		m_data = props.value();
	else m_data = QVariantMap();
	emit dataChanged(m_data);
	
	QDBusReply<QVariantMap> simProps = QDBusInterface(
		"org.ofono",
		m_path, 
		"org.ofono.SimManager",
		QDBusConnection::systemBus()
	).call("GetProperties");
	if (simProps.isValid())
		m_simData = simProps.value();
	else m_simData = QVariantMap();
	emit simDataChanged(m_simData);

	QDBusConnection::systemBus().connect(
		"org.ofono",
		m_path, 
		"org.ofono.Modem", 
		"ProperyChanged",
		this, SLOT(onPropertyChanged(QString,QVariant)));

	QDBusConnection::systemBus().connect(
		"org.ofono",
		m_path, 
		"org.ofono.SimManager", 
		"ProperyChanged",
		this, SLOT(onSimPropertyChanged(QString,QVariant)));

	QDBusConnection::systemBus().connect(
		"org.ofono",
		m_path, 
		"org.ofono.MessageManager", 
		"IncomingMessage",
		this, SLOT(onIncomingMessage(QString,QVariantMap)));

	QDBusConnection::systemBus().connect(
		"org.ofono",
		m_path, 
		"org.ofono.VoiceCallManager", 
		"CallAdded",
		this, SLOT(onCallAdded(QDBusObjectPath,QVariantMap)));

	QDBusConnection::systemBus().connect(
		"org.ofono",
		m_path, 
		"org.ofono.VoiceCallManager", 
		"CallRemoved",
		this, SLOT(onCallRemoved(QDBusObjectPath)));
}

void OfonoModem::onPropertyChanged(QString name, QVariant value) {
	m_data.insert(name, value);
	emit dataChanged(m_data);
}

void OfonoModem::onSimPropertyChanged(QString name, QVariant value) {
	m_simData.insert(name, value);
	emit simDataChanged(m_simData);
}

void OfonoModem::onIncomingMessage(QString message, QVariantMap props) {
	emit incomingMessage(message, props);
}

void OfonoModem::onCallAdded(QDBusObjectPath path, QVariantMap props) {
	OfonoCall *call = new OfonoCall(this, path.path(), props);
	m_calls.insert(path.path(), call);
	emit newCall(call);
}

void OfonoModem::onCallRemoved(QDBusObjectPath path) {
	m_calls.remove(path.path());
}

void OfonoModem::sendMessage(QString to, QString message) {
	QDBusInterface(
		"org.ofono",
		m_path, 
		"org.ofono.MessageManager",
		QDBusConnection::systemBus()
	).call("SendMessage", to, message);
}

QString OfonoModem::dial(QString to, QString hideID) {
	QDBusReply<QDBusObjectPath> path = QDBusInterface(
		"org.ofono",
		m_path, 
		"org.ofono.VoiceCallManager",
		QDBusConnection::systemBus()
	).call("Dial", to, hideID);
	if (path.isValid()) 
		return path.value().path();
	return QString();
}
