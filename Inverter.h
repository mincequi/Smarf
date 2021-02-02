#pragma once

#include <QObject>

class QmlMqttClient;
class QMqttMessage;
class QMqttSubscription;

class Inverter : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QMqttTopicFilter topic MEMBER m_topic NOTIFY topicChanged)
    Q_PROPERTY(QString lastUpdate MEMBER m_lastUpdate NOTIFY lastUpdateChanged)
    Q_PROPERTY(double yieldTotal MEMBER m_yieldTotal NOTIFY yieldChanged)
    Q_PROPERTY(double yieldToday MEMBER m_yieldToday NOTIFY yieldChanged)
    Q_PROPERTY(std::vector<qreal> powerDc MEMBER m_powerDcNow NOTIFY powerChanged)
    Q_PROPERTY(std::vector<qreal> powerDcMaxToday MEMBER m_powerDcMaxToday NOTIFY powerMaxTodayChanged)
    Q_PROPERTY(double powerAc MEMBER m_powerAcNow NOTIFY powerChanged)
    Q_PROPERTY(double powerAcMaxToday MEMBER m_powerAcMaxToday NOTIFY powerMaxTodayChanged)

public:
    Inverter(QMqttSubscription *s, QmlMqttClient *c);
    ~Inverter();

Q_SIGNALS:
    //void topicChanged(QString);
    void lastUpdateChanged();
    void messageReceived(const QString &msg);
    void yieldChanged();
    void powerChanged();
    void powerMaxTodayChanged();

public slots:
    void onMessageReceived(const QMqttMessage &qmsg);

private:
    QString lastUpdate(uint32_t secondsSinceEpoch);

    QMqttSubscription* m_subscription;
    QmlMqttClient* m_client;

    QString m_lastUpdate;
    double m_yieldTotal = 0.0;
    double m_yieldToday = 0.0;
    std::vector<qreal> m_powerDcNow;
    std::vector<qreal> m_powerDcMax;
    std::vector<qreal> m_powerDcMaxToday;
    double m_powerAcNow = 0.0;
    double m_powerAcMaxToday = 0.0;
};
