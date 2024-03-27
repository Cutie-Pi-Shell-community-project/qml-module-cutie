#include "plugin.h"

void CutiePlugin::registerTypes(const char *uri)
{
	qmlRegisterSingletonType<WifiSettings>(uri, 1, 0, "CutieWifiSettings",
					       &WifiSettings::provider);
	qmlRegisterSingletonType<MobileNetwork>(uri, 1, 0, "CutieMobileNetwork",
						&MobileNetwork::provider);
	qmlRegisterSingletonType<ModemSettings>(uri, 1, 0, "CutieModemSettings",
						&ModemSettings::provider);
	qmlRegisterSingletonType<Notifications>(uri, 1, 0, "CutieNotifications",
						&Notifications::provider);
	qmlRegisterSingletonType<Feedback>(uri, 1, 0, "CutieFeedback",
					      &Feedback::provider);
	qmlRegisterSingletonType<CutieVolume>(uri, 1, 0, "CutieVolume",
					      &CutieVolume::provider);
	qmlRegisterSingletonType<AtmosphereModel>(uri, 1, 0, "Atmosphere",
						  &AtmosphereModel::provider);
	qmlRegisterType<CutieStore>(uri, 1, 0, "CutieStore");
	qmlRegisterType<WifiAccessPoint>(uri, 1, 0, "CutieWifiAccessPoint");
	qmlRegisterType<CutieNetworkConnection>(uri, 1, 0,
						"CutieNetworkConnection");
	qmlRegisterType<CutieModem>(uri, 1, 0, "CutieModem");
	qmlRegisterUncreatableType<CutieCall>(
		uri, 1, 0, "CutieCall",
		"Cannot be crated directly, use dial() on the modem object to call");
}

void CutiePlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
	Q_UNUSED(uri);
	QIcon::setThemeName(
		qEnvironmentVariable("CUTIE_ICON_THEME", "cutie"));
	engine->addImageProvider("icon", &iconProvider);
}
