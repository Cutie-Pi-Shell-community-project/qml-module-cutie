#pragma once
#include <QDebug>
#include <QtQuick>
#include <QtQml/qqml.h>
#include <QtQml/QQmlExtensionPlugin>

#include <atmosphere.h>
#include <cutiestore.h>
#include <cutiemodem.h>

#include "wifi/wifisettings.h"
#include "notifications/notifications.h"
#include "volume/cutievolume.h"
#include "mobilenetwork/mobilenetwork.h"

class CutiePlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlEngineExtensionInterface_iid FILE "cutie.json")
    void registerTypes(const char *uri);
};