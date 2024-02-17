#include "wifiaccesspoint.h"

WifiAccessPoint::WifiAccessPoint(QObject *parent)
	: QObject(parent)
{
}

WifiAccessPoint::~WifiAccessPoint()
{
}

void WifiAccessPoint::setPath(QString path)
{
	m_path = path;
	QDBusConnection::systemBus().connect(
		"org.freedesktop.NetworkManager", path,
		"org.freedesktop.DBus.Properties", "PropertiesChanged", this,
		SLOT(onPropertiesChanged(QString, QMap<QString, QVariant>,
					 QStringList)));
	emit pathChanged(path);
	QDBusReply<QMap<QString, QVariant> > apReply =
		QDBusInterface("org.freedesktop.NetworkManager", path,
			       "org.freedesktop.DBus.Properties",
			       QDBusConnection::systemBus())
			.call("GetAll",
			      "org.freedesktop.NetworkManager.AccessPoint");
	if (apReply.isValid())
		m_data = apReply.value();
	else
		m_data = QMap<QString, QVariant>();
	emit dataChanged(m_data);
}

QString WifiAccessPoint::path()
{
	return m_path;
}

QMap<QString, QVariant> WifiAccessPoint::data()
{
	return m_data;
}

void WifiAccessPoint::onPropertiesChanged(QString iface,
					  QMap<QString, QVariant> updated,
					  QStringList invalidated)
{
	Q_UNUSED(invalidated);
	if (iface == "org.freedesktop.NetworkManager.AccessPoint") {
		m_data.insert(updated);
		emit dataChanged(m_data);
	};
}