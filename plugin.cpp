#include "plugin.h"

void CutiePlugin::registerTypes(const char *uri)
{
    qmlRegisterSingletonType<WifiSettings>(uri, 1, 0, "CutieWifiSettings", &WifiSettings::provider);
    qmlRegisterSingletonType<AtmosphereModel>(uri, 1, 0, "Atmosphere", &AtmosphereModel::provider);
}