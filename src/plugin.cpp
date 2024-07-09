#include "plugin.h"

void CutiePlugin::registerTypes(const char *uri)
{
	qmlRegisterSingletonType<Feedback>(uri, 1, 0, "CutieFeedback",
					      &Feedback::provider);
	qmlRegisterSingletonType<AtmosphereModel>(uri, 1, 0, "Atmosphere",
						  &AtmosphereModel::provider);
}

void CutiePlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
	Q_UNUSED(uri);
	QIcon::setThemeName(
		qEnvironmentVariable("CUTIE_ICON_THEME", "cutie"));
	engine->addImageProvider("icon", &iconProvider);
}
