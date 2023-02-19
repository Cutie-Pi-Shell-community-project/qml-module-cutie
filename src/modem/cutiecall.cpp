#include "cutiemodem.h"

CutieCall::CutieCall(QObject *parent) : QObject(parent) {}

CutieCall::~CutieCall() {}

QString CutieCall::path() {
	return m_path;
}

QVariantMap CutieCall::data() {
	return m_data;
}

CutieModem *CutieCall::modem() {
	return qobject_cast<CutieModem *>(parent());
}