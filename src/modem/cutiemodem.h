#pragma once
#include <QDebug>
#include <QtQuick>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusReply>
#include <QDBusMetaType>
#include "cutiecall.h"

class CutieModem : public QObject
{
    Q_OBJECT
    Q_PROPERTY (QString path READ path() NOTIFY pathChanged);
    Q_PROPERTY (QVariantMap data READ data() NOTIFY dataChanged);
    Q_PROPERTY (QVariantMap simData READ simData() NOTIFY simDataChanged);
    Q_PROPERTY (uint audioMode READ audioMode() WRITE setAudioMode NOTIFY audioModeChanged);
public:
    CutieModem(QObject *parent=0);
    ~CutieModem();

    QString path();
    QVariantMap data();
    QVariantMap simData();
    uint audioMode();
    void setAudioMode(uint mode);

    virtual void setPath(QString path) = 0;
    virtual Q_INVOKABLE void sendMessage(QString to, QString message) = 0;
    virtual Q_INVOKABLE QString dial(QString to, QString hideID = QString()) = 0;
Q_SIGNALS:
    void pathChanged(QString);
    void dataChanged(QVariantMap);
    void simDataChanged(QVariantMap);
    void audioModeChanged(uint mode);
	void incomingMessage(QString message, QVariantMap props);
	void newCall(CutieCall* call);

public Q_SLOTS:
    void onCallAudioPropertiesChanged(QString iface, QMap<QString, QVariant> updated, QStringList invalidated);

protected:
    QString m_path;
    QVariantMap m_data;
    QVariantMap m_simData;
    QMap<QString, CutieCall*> m_calls;
    uint m_audioMode;
};