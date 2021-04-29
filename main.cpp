#include "qmlmqttclient.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QLoggingCategory>

#include "InverterModel.h"
#include "Persistence.h"
#include "ThemeModel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ThemeModel themeModel;

    QQmlApplicationEngine engine;
    QQuickStyle::setStyle("Material");

    qmlRegisterType<QmlMqttClient>("MqttClient", 1, 0, "MqttClient");
    qmlRegisterType<Persistence>("MqttClient", 1, 0, "MqttConfig");
    qmlRegisterUncreatableType<InverterModel>("MqttClient", 1, 0, "MqttSubscription", QLatin1String("Subscriptions are read-only"));
    qmlRegisterUncreatableType<ThemeModel>("MqttClient", 1, 0, "MqttSubscription", QLatin1String("Subscriptions are read-only"));
    qmlRegisterSingletonInstance<ThemeModel>("Smarf.ThemeModel", 1, 0, "ThemeModel", &themeModel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
