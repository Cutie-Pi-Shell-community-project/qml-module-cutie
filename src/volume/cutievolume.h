#include <QDebug>
#include <QtQuick>
#include <QtQml/qqml.h>
#include <QtQml/QQmlExtensionPlugin>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QDBusReply>
#include <pulse/pulseaudio.h>

class CutieVolume : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(bool muted READ muted WRITE setMuted NOTIFY mutedChanged)
public:
    CutieVolume(QObject *parent=0);
    ~CutieVolume();

    float volume();
    bool muted();
    void setVolume(float volume);
    void setMuted(bool muted);

    static QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine);

Q_SIGNALS:
    void volumeChanged(float volume);
    void mutedChanged(bool muted);

private:
    pa_threaded_mainloop* _mainloop;
    pa_mainloop_api* _mainloop_api;
    pa_context* _context;
    QString _default_sink_name;
    pa_cvolume _cvolume;

    float m_volume;
    bool m_muted;

    static void onContextStateCallback(pa_context *c, void *userdata);
    static void onServerInfoCallback(pa_context *c, const pa_server_info *i, void *userdata);
    static void onSubscribeCallback(pa_context *c, pa_subscription_event_type_t type, uint32_t idx, void *userdata);
    static void onSinkInfoCallback(pa_context *c, const pa_sink_info *i, int eol, void *userdata);
};