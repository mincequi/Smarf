#include "qmlmqttclient.h"

#include <QDebug>
#include <QTimer>
#include <msgpack.h>

#include "Persistence.h"
#include "InverterModel.h"
#include "Types.h"

QmlMqttClient::QmlMqttClient(QObject* parent)
    : QMqttClient(parent)
{
    connect(this, &QMqttClient::connected, this, &QmlMqttClient::onConnected);
    //connect(this, &QMqttClient::disconnected, this, &QmlMqttClient::onDisconnected);
    //connect(this, &QMqttClient::stateChanged, this, &QmlMqttClient::onStateChanged);
}

QmlMqttClient::~QmlMqttClient()
{
}

void QmlMqttClient::start()
{
    if (state() != Disconnected) {
        return;
    }

    // We need to delay a little bit
    QTimer::singleShot(0, this, [this]() {
        m_autoConnect = true;
        validateHost(m_config.currentHost());
    });
}

void QmlMqttClient::stop()
{
    disconnectFromHost();
}

void QmlMqttClient::onStateChanged(QMqttClient::ClientState state)
{
//    switch (state) {
//    case QMqttClient::ClientState::Disconnected:
//        m_hostState = Invalid;
//    case QMqttClient::ClientState::Connecting:
//        m_hostState = Checking;
//    case QMqttClient::ClientState::Disconnected:
//        m_hostState = Invalid;
//    }
}

void QmlMqttClient::onConnected()
{
    m_config.setCurrentHost(hostname());
    validateInverter(m_config.currentInverter());
}

void QmlMqttClient::onDisconnected()
{
    m_plantState = Unknown;
    m_inverterState = Unknown;

    emit plantStateChanged();
    emit inverterStateChanged();

    // Update inverters
    for (auto& inverter : m_inverters) {
        delete inverter;
    }
    m_inverters.clear();
    emit invertersChanged();
}

void QmlMqttClient::validateHost(const QString& hostname)
{
    disconnectFromHost();
    setHostname(hostname);
    connectToHost();
}

/*
void QmlMqttClient::validatePlant(const QString& plantname)
{
    if (plantname.isEmpty()) {
        m_plantState = Unknown;
        emit plantStateChanged();
        return;
    }

    m_plantState = Checking;
    emit plantStateChanged();

    auto sub = subscribe("sbfspot_" + plantname + "/sma_1234" + "/config");
    connect(sub, &QMqttSubscription::messageReceived, this, [=]() {
        sub->unsubscribe();
        m_plantState = Valid;
        emit plantStateChanged();
    });

    QTimer::singleShot(3500, this, [=]() {
        sub->unsubscribe();
        if (m_plantState != Valid) {
            m_plantState = Invalid;
            emit plantStateChanged();
        }
    });
}
*/

void QmlMqttClient::validateInverter(const QString& inverterSerial)
{
    // Only 10 digits serials are valid and we can only validate if we are connected
    if (inverterSerial.size() != 10 || state() != ClientState::Connected) {
        m_inverterState = Unknown;
        emit inverterStateChanged();
        return;
    }

    m_inverterState = Checking;
    emit inverterStateChanged();

    auto sub = subscribe("sbfspot_" + inverterSerial + "/config");
    connect(sub, &QMqttSubscription::messageReceived, this, [=](const QMqttMessage& msg) {
        sub->unsubscribe();
        m_inverterState = Valid;
        emit inverterStateChanged();

        m_inverterConfig.manufacturer = "SMA";
        m_inverterConfig.name = MsgPack::unpack(msg.payload()).toMap().value(toIntString(InverterProperty::Name)).toString();
        m_inverterConfig.serial = inverterSerial.toUInt();
        m_inverterConfig.mqttHost = hostname();
        m_inverterConfig.mqttPort = port();
        m_inverterConfig.strings = StringConfig::fromMsgPack(MsgPack::unpack(msg.payload()).toMap().value(toIntString(InverterProperty::Strings)));

        if (m_autoConnect) {
            //disconnectFromHost();
            m_autoConnect = false;
            subscribeToInverter();
        }
    });

    QTimer::singleShot(3500, this, [=]() {
        sub->unsubscribe();
        if (m_inverterState != Valid) {
            m_inverterState = Invalid;
            emit inverterStateChanged();
        }
    });
}

void QmlMqttClient::subscribeToInverter()
{
    if (m_inverterState != Valid) {
        return;
    }

    disconnectFromHost();
    m_inverters.push_back(new InverterModel(m_inverterConfig));
    emit invertersChanged();
}

QString QmlMqttClient::currentInverter() const
{
    return m_config.currentInverter();
}

QList<QObject*> QmlMqttClient::inverters() const
{
    return m_inverters;
}
