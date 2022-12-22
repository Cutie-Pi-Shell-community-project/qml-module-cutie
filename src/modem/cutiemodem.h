#pragma once
#include <QDebug>
#include <QtQuick>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusReply>
#include <QDBusMetaType>

class CutieModem : public QObject
{
    Q_OBJECT
    Q_PROPERTY (QString path READ path() NOTIFY pathChanged);
    Q_PROPERTY (QVariantMap data READ data() NOTIFY dataChanged);
    Q_PROPERTY (QVariantMap simData READ simData() NOTIFY simDataChanged);
public:
    CutieModem(QObject *parent=0);
    ~CutieModem();

    QString path();
    QVariantMap data();
    QVariantMap simData();

    virtual void setPath(QString path) = 0;
Q_SIGNALS:
    void pathChanged(QString);
    void dataChanged(QVariantMap);
    void simDataChanged(QVariantMap);
	void incomingMessage(QString message, QVariantMap props);

private:
    QString m_path;
    QVariantMap m_data;
    QVariantMap m_simData;
};