#include "Inverter.h"

#include <QDateTime>
#include <QMqttMessage>
#include <QMqttSubscription>

#include <msgpack.h>

Inverter::Inverter(QMqttSubscription *s, QmlMqttClient *c)
    : m_subscription(s)
    , m_client(c)
{
    connect(m_subscription, &QMqttSubscription::messageReceived, this, &Inverter::onMessageReceived);

    m_powerDcMax.push_back(300);
    m_powerDcMax.push_back(50);
}

Inverter::~Inverter()
{
}

void Inverter::onMessageReceived(const QMqttMessage& message)
{
    auto topic = message.topic();
    qDebug() << topic;

    auto variant = MsgPack::unpack(message.payload()).toMap();
    m_lastUpdate = lastUpdate(variant.value("1").toDateTime().toSecsSinceEpoch());
    m_yieldTotal = variant.value("2").toDouble();
    m_yieldToday = variant.value("3").toDouble();
    auto dcList = variant.value("6").toList();

    m_powerDcNow.resize(dcList.size());
    for (int i = 0; i < dcList.size(); ++i) {
        m_powerDcNow[i] = dcList.value(i).toReal()/m_powerDcMax[i] * 270;
    }

    emit lastUpdateChanged();
    emit yieldChanged();
    emit powerChanged();
}

QString Inverter::lastUpdate(uint32_t secondsSinceEpoch)
{
    QString out;

    auto now = time(nullptr);
    auto diff = now - secondsSinceEpoch;
    if (diff > 365 * 24 * 60 * 60) {
        out = QString::number(diff/(365*24*60*60));
        out += " yr";
    } else if (diff > 30 * 24 * 60 * 60) {
        out = QString::number(diff/(30*24*60*60));
        out += " mo";
    } else if (diff > 7 * 24 * 60 * 60) {
        out = QString::number(diff/(7*24*60*60));
        out += " wk";
    } else if (diff > 24 * 60 * 60) {
        out = QString::number(diff/(24*60*60));
        out += " d";
    } else if (diff > 60 * 60) {
        out = QString::number(diff/(60*60));
        out += " h";
    } else if (diff > 60) {
        out = QString::number(diff/(60));
        out += " min";
    } else {
        out = "online";
    }

    return out;
}
