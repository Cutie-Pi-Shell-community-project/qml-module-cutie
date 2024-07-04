#include "plugin.h"

void CutiePlugin::registerTypes(const char *uri)
{
	qmlRegisterSingletonType<ModemSettings>(uri, 1, 0, "CutieModemSettings",
						&ModemSettings::provider);
	qmlRegisterSingletonType<Notifications>(uri, 1, 0, "CutieNotifications",
						&Notifications::provider);
	qmlRegisterSingletonType<Feedback>(uri, 1, 0, "CutieFeedback",
					      &Feedback::provider);
	qmlRegisterSingletonType<AtmosphereModel>(uri, 1, 0, "Atmosphere",
						  &AtmosphereModel::provider);
	qmlRegisterSingletonType<CutiePhonenumberHelper>(uri, 1, 0, "CutiePhonenumberHelper",
					     &CutiePhonenumberHelper::provider);

	qmlRegisterType<CutieStore>(uri, 1, 0, "CutieStore");
	qmlRegisterType<CutieModem::NetworkStatus>(uri, 1, 0, "NetworkStatus");
	qmlRegisterType<CutieModem::NetworkTechnology>(uri, 1, 0, "NetworkTechnology");
	qmlRegisterType<CutiePhonenumber>(uri, 1, 0, "CutiePhonenumber");

	qmlRegisterUncreatableType<CutieModem>(uri, 1, 0, "CutieModem",
		"Cannot be crated directly, use CutieModemSettings to get available modems");
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
