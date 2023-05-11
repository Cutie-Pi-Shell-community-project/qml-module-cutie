#include "plugin.h"
#include <QDir>
#include <QStandardPaths>

AtmosphereModel::AtmosphereModel(QObject *parent) : QObject(parent)
{
    this->atmosphere = new org::cutie_shell::SettingsDaemon::Atmosphere(
        "org.cutie_shell.SettingsDaemon", "/atmosphere",
        QDBusConnection::systemBus());
    connect(this->atmosphere, SIGNAL(PathChanged()), this, SLOT(onAtmospherePathChanged()));
    connect(this->atmosphere, SIGNAL(VariantChanged()), this, SLOT(onAtmosphereVariantChanged()));
    onAtmospherePathChanged();
    onAtmosphereVariantChanged();
}

AtmosphereModel::~AtmosphereModel()
{
}

QString AtmosphereModel::path() {
    return p_path;
}

QString AtmosphereModel::variant() {
    return p_variant;
}

QString AtmosphereModel::primaryColor() {
    return p_primaryColor;
}

QString AtmosphereModel::primaryAlphaColor() {
    return p_primaryAlphaColor;
}

QString AtmosphereModel::secondaryColor() {
    return p_secondaryColor;
}

QString AtmosphereModel::secondaryAlphaColor() {
    return p_secondaryAlphaColor;
}

QString AtmosphereModel::accentColor() {
    return p_accentColor;
}

QString AtmosphereModel::textColor() {
    return p_textColor;
}

QVariantList AtmosphereModel::atmosphereList() {
    return p_atmosphereList;
}

void AtmosphereModel::onAtmospherePathChanged() {
    QString old_path = p_path;
    p_path = this->atmosphere->GetPath();
    if (old_path != p_path) pathChanged();

    QStringList dirs = QStandardPaths::standardLocations(QStandardPaths::GenericDataLocation);
    QVariantList myList;
    foreach (const QString &str, dirs) {
        QDir checkDir = str+"/atmospheres";
        if(checkDir.exists()){
            foreach(const QString &atmosphere_dir, checkDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot)){
                QVariantMap myMap;
                if(atmosphere_dir != "Current"){
                    QSettings settings(checkDir.absolutePath()+"/"+atmosphere_dir+"/settings.ini", QSettings::IniFormat);
                    myMap.insert("name", atmosphere_dir);
                    myMap.insert("path", checkDir.absolutePath()+"/"+atmosphere_dir);
                    myMap.insert("variant", settings.value("variant").toString());
                    myList << myMap;
                }
            }
        }
    }
    p_atmosphereList = myList;
    atmosphereListChanged();

    QSettings settings(p_path+"/settings.ini", QSettings::IniFormat);
    p_primaryColor = "#"+settings.value("primaryColor").toString();
    primaryColorChanged();
    p_primaryAlphaColor = "#"+settings.value("primaryAlphaColor").toString();
    primaryAlphaColorChanged();
    p_secondaryColor = "#"+settings.value("secondaryColor").toString();
    secondaryColorChanged();
    p_secondaryAlphaColor = "#"+settings.value("secondaryAlphaColor").toString();
    secondaryAlphaColorChanged();
    p_accentColor = "#"+settings.value("accentColor").toString();
    accentColorChanged();
    p_textColor = "#"+settings.value("textColor").toString();
    textColorChanged();
}

void AtmosphereModel::onAtmosphereVariantChanged() {
    QString old_variant = p_variant;
    p_variant = this->atmosphere->GetVariant();
    if (old_variant != p_variant) variantChanged();
}

QObject *AtmosphereModel::provider(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(scriptEngine);
    return new AtmosphereModel(engine);
}