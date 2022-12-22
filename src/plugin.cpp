#include "plugin.h"

void CutiePlugin::registerTypes(const char *uri)
{
    qmlRegisterSingletonType<WifiSettings>(uri, 1, 0, "CutieWifiSettings", &WifiSettings::provider);
    qmlRegisterSingletonType<ModemSettings>(uri, 1, 0, "CutieModemSettings", &ModemSettings::provider);
    qmlRegisterSingletonType<Notifications>(uri, 1, 0, "CutieNotifications", &Notifications::provider);
    qmlRegisterSingletonType<AtmosphereModel>(uri, 1, 0, "Atmosphere", &AtmosphereModel::provider);
    qmlRegisterType<WifiAccessPoint>(uri, 1, 0, "CutieWifiAccessPoint");
    qmlRegisterType<CutieNetworkConnection>(uri, 1, 0, "CutieNetworkConnection");
    qmlRegisterType<OfonoModem>(uri, 1, 0, "CutieOfonoModem");
}