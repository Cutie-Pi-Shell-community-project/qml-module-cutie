#pragma once
#include <QDebug>
#include <QtQuick>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusReply>
#include <QDBusMetaType>

class CutieModem;

class CutieCall : public QObject
{
    Q_OBJECT
    Q_PROPERTY (QString path READ path() NOTIFY pathChanged);
    Q_PROPERTY (QVariantMap data READ data() NOTIFY dataChanged);
    Q_PROPERTY (CutieModem *modem READ modem());

public:
    CutieCall(QObject *parent=0);
    ~CutieCall();

    QString path();
    QVariantMap data();
    CutieModem *modem();

    virtual Q_INVOKABLE void answer() = 0;
    virtual Q_INVOKABLE void hangup() = 0;

Q_SIGNALS:
    void pathChanged(QString);
    void dataChanged(QVariantMap);
    void disconnected(QString);

protected:
    QString m_path;
    QVariantMap m_data;
};