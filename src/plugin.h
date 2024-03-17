#pragma once
#include <QDebug>
#include <QtQuick>
#include <QtQml/qqml.h>
#include <QtQml/QQmlExtensionPlugin>

#include <atmosphere.h>
#include <cutiestore.h>
#include <cutiemodem.h>
#include <cutienotification.h>
#include <cutiefeedback.h>

#include "iconprovider.h"
#include "wifi/wifisettings.h"
#include "wifi/wifisettings.h"
#include "volume/cutievolume.h"
#include "mobilenetwork/mobilenetwork.h"

class CutiePlugin : public QQmlExtensionPlugin {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID QQmlEngineExtensionInterface_iid FILE
			  "cutie.json")
    public:
	explicit CutiePlugin()
	{
	}

	void registerTypes(const char *uri) override;
	void initializeEngine(QQmlEngine *engine, const char *uri) override;

    private:
	IconProvider iconProvider = IconProvider(QQmlImageProviderBase::Pixmap);
};