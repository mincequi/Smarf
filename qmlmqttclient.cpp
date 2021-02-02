#include "qmlmqttclient.h"

#include <QDebug>
#include <msgpack.h>

#include "Inverter.h"

QmlMqttClient::QmlMqttClient(QObject *parent)
    : QMqttClient(parent)
{
    connect(this, &QMqttClient::connected, this, &QmlMqttClient::onConnected);
    connect(this, &QMqttClient::disconnected, this, &QmlMqttClient::onDisconnected);
}

void QmlMqttClient::onConnected()
{
    QStringList serials = { "2110329726", "2110337850" };

    for (const auto& serial : serials) {
        QString topic = "sbfspot_" + m_plantName + "/sma_" + serial + "/now";
        auto sub = QMqttClient::subscribe(topic, 0);
        m_inverters.push_back(new Inverter(sub, this));
    }

    emit invertersChanged();
}

void QmlMqttClient::onDisconnected()
{
    for (auto& inverter : m_inverters) {
        delete inverter;
    }

    m_inverters.clear();
}

void QmlMqttClient::connectToPlant(const QString& plantName)
{
    m_plantName = plantName;
    connectToHost();
}

QList<QObject*> QmlMqttClient::inverters() const
{
    return m_inverters;
}
