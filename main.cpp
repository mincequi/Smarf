#include "qmlmqttclient.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QLoggingCategory>

#include "InverterModel.h"
#include "LiveModel.h"
#include "Persistence.h"
#include "ThemeModel.h"

#include "thirdparty/CayenneLPP/src/CayenneLPP.h"
#include "thirdparty/CayenneLPP/src/CayenneLPPMessage.h"

int randomPower(int min = -20000, int max = 20000) {
    return min + (std::rand() % (max - min + 1));
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ThemeModel themeModel;
    LiveModel liveModel;

    QQmlApplicationEngine engine;
    QQuickStyle::setStyle("Material");

    qmlRegisterType<QmlMqttClient>("MqttClient", 1, 0, "MqttClient");
    qmlRegisterType<Persistence>("MqttClient", 1, 0, "MqttConfig");
    qmlRegisterUncreatableType<InverterModel>("MqttClient", 1, 0, "MqttSubscription", QLatin1String("Subscriptions are read-only"));
    qmlRegisterUncreatableType<ThemeModel>("MqttClient", 1, 0, "MqttSubscription", QLatin1String("Subscriptions are read-only"));
    qmlRegisterSingletonInstance<ThemeModel>("Smarf.ThemeModel", 1, 0, "ThemeModel", &themeModel);
    qmlRegisterSingletonInstance<LiveModel>("Smarf.LiveModel", 1, 0, "LiveModel", &liveModel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QTimer timer;
    timer.callOnTimeout([&]() {
        const double inv1 = randomPower(0, 10000);
        const double inv2 = randomPower(0, 10000);
        const auto grid = randomPower(-5000, 5000);
        const uint32_t timestamp = QDateTime::currentDateTime().toTime_t() - randomPower(0, 10000);
        liveModel.feedPower(timestamp, grid, { inv1, inv2 });
    });
    timer.start(5000);

    CayenneLPPMessage in;
    in.accelerometer[0] = 1.0;
    in.accelerometer[1] = 2.0;
    in.accelerometer[2] = 3.0;
    in.altitude = 4.0;
    in.analogInput = 5.0;
    in.analogOutput = 6.0;
    in.barometricPressure = 7.0;
    in.colour[0] = 8;
    in.colour[1] = 9;
    in.colour[2] = 10;
    in.concentration = 11;
    in.current = 12.0f;
    CayenneLPP clpp(255);
    clpp.addAccelerometer(0, in.accelerometer[0], in.accelerometer[1], in.accelerometer[2]);
    clpp.addAltitude(0, in.altitude);
    clpp.addAnalogInput(0, in.analogInput);
    clpp.addAnalogOutput(0, in.analogOutput);
    clpp.addBarometricPressure(1, in.barometricPressure);
    clpp.addColour(1, in.colour[0], in.colour[1], in.colour[2]);
    clpp.addConcentration(1, in.concentration);
    clpp.addCurrent(1, in.current);

    std::map<uint8_t, CayenneLPPMessage> out;
    out[0] = {};

    clpp.decode(clpp.getBuffer(), clpp.getSize(), out);
    assert(in.accelerometer == out[0].accelerometer);
    assert(in.altitude == out[0].altitude);
    assert(in.analogInput == out[0].analogInput);
    assert(in.analogOutput == out[0].analogOutput);


    return app.exec();
}
