#include "cutiemodem.h"

CutieModem::CutieModem(QObject *parent) : QObject(parent) {
    QDBusReply<QDBusVariant> audioModeReply = QDBusInterface(
	    "org.mobian_project.CallAudio",
        "/org/mobian_project/CallAudio", 
	    "org.freedesktop.DBus.Properties",
        QDBusConnection::sessionBus()
    ).call(
        "Get", "org.mobian_project.CallAudio", "AudioMode"
    );
    m_audioMode = audioModeReply.isValid() 
        ? qdbus_cast<uint>(audioModeReply.value().variant())
        : 0;

    QDBusConnection::sessionBus().connect(
        "org.mobian_project.CallAudio",
        "/org/mobian_project/CallAudio", 
        "org.freedesktop.DBus.Properties", 
        "PropertiesChanged",
        this, SLOT(onCallAudioPropertiesChanged(QString,QMap<QString, QVariant>,QStringList)));
}

CutieModem::~CutieModem() {}

QString CutieModem::path() {
	return m_path;
}

QVariantMap CutieModem::data() {
	return m_data;
}

QVariantMap CutieModem::simData() {
	return m_simData;
}

QVariantMap CutieModem::netData() {
	return m_netData;
}

uint CutieModem::audioMode() {
	return m_audioMode;
}

void CutieModem::setAudioMode(uint mode) {
    QDBusInterface(
	    "org.mobian_project.CallAudio",
        "/org/mobian_project/CallAudio", 
	    "org.mobian_project.CallAudio",
        QDBusConnection::sessionBus()
    ).call(
        "SelectMode", mode
    );
}

void CutieModem::onCallAudioPropertiesChanged(QString iface, QMap<QString, QVariant> updated, QStringList invalidated) {
    Q_UNUSED(invalidated);
    if (iface == "org.mobian_project.CallAudio") {
        if (updated.contains("AudioMode")) {
            m_audioMode = qdbus_cast<uint>(updated.value("AudioMode"));
            emit audioModeChanged(m_audioMode);
        }
    };
}