#include <QDebug>
#include <QtQuick>
#include <QtQml/qqml.h>
#include <QtQml/QQmlExtensionPlugin>
#include "cutie_shell_interface.h"

class CutieNetworkConnection : public QObject
{
    Q_OBJECT
    Q_PROPERTY (QString path READ path() NOTIFY pathChanged);
    Q_PROPERTY (QMap<QString,QVariant> data READ data() NOTIFY dataChanged);
public:
    CutieNetworkConnection(QObject *parent=0);
    ~CutieNetworkConnection();

    QString path();
    void setPath(QString path);
    QMap<QString,QVariant> data();
Q_SIGNALS:
    void pathChanged(QString path);
    void dataChanged(QMap<QString,QVariant> data);
public Q_SLOTS:
    void onUpdated();
private:
    QString m_path;
    QMap<QString,QMap<QString,QVariant>> m_data;
};
