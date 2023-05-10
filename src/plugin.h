#pragma once
#include <QDebug>
#include <QtQuick>
#include <QtQml/qqml.h>
#include <QtQml/QQmlExtensionPlugin>
#include "cutie_shell_interface.h"
#include "atmosphere/atmospheremodel.h"
#include "wifi/wifisettings.h"
#include "modem/modemsettings.h"
#include "modem/ofonomodem.h"
#include "modem/ofonocall.h"
#include "notifications/notifications.h"
#include "volume/cutievolume.h"
#include "store/cutiestore.h"

class CutiePlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlEngineExtensionInterface_iid FILE "cutie.json")
    void registerTypes(const char *uri);
};