#pragma once

#include "Persistence.h"
#include "Types.h"

#include <QtCore/QMap>
#include <QtMqtt/QMqttClient>

class QmlMqttClient : public QMqttClient
{
public:
    enum State {
        Unknown = 0,
        Checking,
        Invalid,
        Valid
    };

private:
    Q_OBJECT
    Q_ENUMS(State)
    Q_PROPERTY(State hostState MEMBER m_hostState NOTIFY hostStateChanged)
    Q_PROPERTY(State plantState MEMBER m_plantState NOTIFY plantStateChanged)
    Q_PROPERTY(State inverterState MEMBER m_inverterState NOTIFY inverterStateChanged)

    Q_PROPERTY(QString currentInverter READ currentInverter)

    Q_PROPERTY(QList<QObject*> inverters READ inverters NOTIFY invertersChanged)

public:
    QmlMqttClient(QObject* parent = nullptr);
    virtual ~QmlMqttClient();

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void validateHost(const QString& hostname);
    //Q_INVOKABLE void validatePlant(const QString& plantname);
    Q_INVOKABLE void validateInverter(const QString& inverter);
    Q_INVOKABLE void subscribeToInverter();

    QString currentInverter() const;
    QList<QObject*> inverters() const;

Q_SIGNALS:
    void hostStateChanged();
    void plantStateChanged();
    void inverterStateChanged();

    void invertersChanged();

private:
    void onStateChanged(QMqttClient::ClientState state);
    void onConnected();
    void onDisconnected();

    InverterConfig m_inverterConfig;
    Persistence m_config;

    bool m_autoConnect = false;
    State m_hostState = Unknown;
    State m_plantState = Unknown;
    State m_inverterState = Unknown;
    QString m_inverterName;
    QString m_plantName;
    QList<QObject*> m_inverters;
};
