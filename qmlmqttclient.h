#pragma once

#include <QtCore/QMap>
#include <QtMqtt/QMqttClient>
#include <QtMqtt/QMqttSubscription>

class Inverter;

class QmlMqttClient : public QMqttClient
{
    Q_OBJECT
    Q_PROPERTY(QList<QObject*> inverters READ inverters NOTIFY invertersChanged)

public:
    QmlMqttClient(QObject* parent = nullptr);

    Q_INVOKABLE void connectToPlant(const QString& plantName);

    QList<QObject*> inverters() const;

Q_SIGNALS:
    void invertersChanged();

private:
    void onConnected();
    void onDisconnected();

    QString m_plantName;
    QList<QObject*> m_inverters;
};
