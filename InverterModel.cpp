#include "InverterModel.h"

#include "Types.h"

#include <QDateTime>

#include <msgpack.h>
#include <qmqtt.h>

InverterModel::InverterModel(const InverterConfig& config)
    : m_config(config),
      m_client(new QMQTT::Client()) {
    connect(m_client, &QMQTT::Client::connected, this, &InverterModel::onConnected);
    connect(m_client, &QMQTT::Client::disconnected, this, &InverterModel::onDisconnected);
    connect(m_client, &QMQTT::Client::error, this, &InverterModel::onErrorChanged);
    m_client->setHostName(m_config.mqttHost);
    m_client->setPort(m_config.mqttPort);

    connectToHost();
}

InverterModel::~InverterModel() {
    disconnectFromHost();
    m_client->deleteLater();
}

QString InverterModel::name() const {
    return m_config.name;
}

QList<QObject*> InverterModel::stringLiveData() {
    QList<QObject*> objects;
    for (auto& data : m_stringLiveData) {
        objects.push_back(data);
    }
    return objects;
}

void InverterModel::connectToHost() {
    m_client->connectToHost();
}

void InverterModel::disconnectFromHost()
{
    m_client->disconnectFromHost();
}

void InverterModel::onConnected()
{
    m_liveTopic = "sbfspot_" + QString::number(m_config.serial) + "/live";
    m_client->subscribe(m_liveTopic, 0);
    m_statsTopic = "sbfspot_" + QString::number(m_config.serial) + "/today/stats";
    m_client->subscribe(m_statsTopic, 1);

    connect(m_client, &QMQTT::Client::received, this, &InverterModel::onMessageReceived);

    for (const auto& config : m_config.strings) {
        auto data = new StringData;
        data->name = config.name;
        data->powerPeak = config.powerPeak;
        m_stringLiveData.push_back(data);
    }

    m_updateTimer.callOnTimeout(this, &InverterModel::liveDataChanged);
    m_updateTimer.start(30*1000);
}

void InverterModel::onDisconnected()
{
    qDebug() << "onDisconnected";
    m_client->unsubscribe(m_liveTopic);
    m_client->unsubscribe(m_statsTopic);
    m_updateTimer.stop();

    for (auto& data : m_stringLiveData) {
        delete data;
    }
    m_stringLiveData.clear();
    emit liveDataChanged();
}

void InverterModel::onErrorChanged(const QMQTT::ClientError error)
{
    qDebug() << "onError:" << error;
}

void InverterModel::onMessageReceived(const QMQTT::Message& message)
{
    auto topic = message.topic();
    qDebug() << topic << ":" << message.payload().size();

    if (topic.endsWith("/live")) {
        // Inverter live data
        auto variant = MsgPack::unpack(message.payload()).toMap();
        m_lastUpdate = variant.value(toIntString(InverterProperty::Timestamp)).toDateTime();
        m_yieldTotal = variant.value(toIntString(InverterProperty::YieldTotal)).toDouble();
        m_yieldToday = variant.value(toIntString(InverterProperty::YieldToday)).toDouble();
        m_powerAcNow = variant.value(toIntString(InverterProperty::Power)).toDouble();

        // String live data
        auto strings = variant.value(toIntString(InverterProperty::Strings)).toList();
        int i = 0;
        int j = 0;
        m_powerDcTotal = 0.0;
        for (; (i < strings.size()) && (j < m_stringLiveData.size()); ++i, ++j) {
            m_stringLiveData[i]->power = strings.value(i).toMap().value(toIntString(InverterProperty::StringPower)).toReal();
            m_powerDcTotal += m_stringLiveData[i]->power;
        }

        emit liveDataChanged();
    } else if (topic.endsWith("/stats")) {
        // Inverter stats data
        auto variant = MsgPack::unpack(message.payload()).toMap();

        // String stats data
        auto strings = variant.value(toIntString(InverterProperty::Strings)).toList();
        int i = 0;
        int j = 0;
        for (; (i < strings.size()) && (j < m_stringLiveData.size()); ++i, ++j) {
            m_stringLiveData[i]->powerPeakToday = strings.value(i).toMap().value(toIntString(InverterProperty::StringPowerMaxToday)).toReal();
        }

        emit liveDataChanged();
    }
}

QString InverterModel::lastUpdate()
{
    QString out;

    QDateTime now = QDateTime::currentDateTime();

    if (m_lastUpdate.secsTo(now) < 90) {
        out = "online";
    } else if (m_lastUpdate.secsTo(now) < 3570) {
        out = "last seen " + QString::number((m_lastUpdate.secsTo(now) + 30)/60) + " min ago";
    } else if (m_lastUpdate.daysTo(now) == 0) {
        out = "last seen today at " + m_lastUpdate.toString("hh:mm");
    } else if (m_lastUpdate.daysTo(now) == 1) {
        out = "last seen yesterday at " + m_lastUpdate.toString("hh:mm");
    } else {
        out = "last seen " + m_lastUpdate.toString("d.M.yy") + " at " + m_lastUpdate.toString("hh:mm");
    }

    return out;
}
