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
	
	QDBusReply<QVariantMap> netProps = QDBusInterface(
		"org.ofono",
		m_path, 
		"org.ofono.NetworkRegistration",
		QDBusConnection::systemBus()
	).call("GetProperties");
	if (netProps.isValid())
		m_netData = netProps.value();
	else m_netData = QVariantMap();
	emit netDataChanged(m_netData);

	QDBusConnection::systemBus().connect(
		"org.ofono",
		m_path, 
		"org.ofono.Modem", 
		"PropertyChanged",
		this, SLOT(onPropertyChanged(QString,QDBusVariant)));

	QDBusConnection::systemBus().connect(
		"org.ofono",
		m_path, 
		"org.ofono.SimManager", 
		"PropertyChanged",
		this, SLOT(onSimPropertyChanged(QString,QDBusVariant)));

	QDBusConnection::systemBus().connect(
		"org.ofono",
		m_path, 
		"org.ofono.NetworkRegistration", 
		"PropertyChanged",
		this, SLOT(onNetPropertyChanged(QString,QDBusVariant)));

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

void OfonoModem::onPropertyChanged(QString name, QDBusVariant value) {
	m_data.insert(name, value.variant());
	emit dataChanged(m_data);
}

void OfonoModem::onSimPropertyChanged(QString name, QDBusVariant value) {
	m_simData.insert(name, value.variant());
	emit simDataChanged(m_simData);
}

void OfonoModem::onNetPropertyChanged(QString name, QDBusVariant value) {
	m_netData.insert(name, value.variant());
	emit netDataChanged(m_netData);
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

void OfonoModem::setProp(QString key, QVariant value) {
	QDBusReply<QVariantMap> props = QDBusInterface(
		"org.ofono",
		m_path, 
		"org.ofono.Modem",
		QDBusConnection::systemBus()
	).call("SetProperty", key, value);
}

void OfonoModem::setSimProp(QString key, QVariant value) {
	QDBusReply<QVariantMap> props = QDBusInterface(
		"org.ofono",
		m_path, 
		"org.ofono.SimManager",
		QDBusConnection::systemBus()
	).call("SetProperty", key, value);
}

void OfonoModem::setNetProp(QString key, QVariant value) {
	QDBusReply<QVariantMap> props = QDBusInterface(
		"org.ofono",
		m_path, 
		"org.ofono.NetworkRegistration",
		QDBusConnection::systemBus()
	).call("SetProperty", key, value);
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
