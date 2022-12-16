#include <QDebug>
#include <QtQuick>
#include <QtQml/qqml.h>
#include <QtQml/QQmlExtensionPlugin>
#include "cutie_shell_interface.h"

class AtmosphereModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path NOTIFY pathChanged);
    Q_PROPERTY(QString variant READ variant NOTIFY variantChanged);
    org::cutie_shell::SettingsDaemon::Atmosphere *atmosphere;
    QString p_path;
    QString p_variant;
public:
    AtmosphereModel(QObject *parent=0);

    ~AtmosphereModel();

    Q_INVOKABLE QString path();
    Q_INVOKABLE QString variant();

    static QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine);

public Q_SLOTS:
    void onAtmospherePathChanged();
    void onAtmosphereVariantChanged();

Q_SIGNALS:
    void pathChanged();
    void variantChanged();
};