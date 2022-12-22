#include "cutiemodem.h"

CutieModem::CutieModem(QObject *parent) : QObject(parent) {}

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