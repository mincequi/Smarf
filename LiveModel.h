#ifndef LIVEMODEL_H
#define LIVEMODEL_H

#include <set>

#include <QDateTime>
#include <QObject>
#include <QSet>
#include <QVariant>

#include "CayenneLPPMessage.h"
#include <CayenneLPPPowerMeasurement.h>
#include "CiotusMessage.h"

class LiveModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString lastUpdate READ lastUpdate NOTIFY liveDataChanged)
    Q_PROPERTY(qreal generatorPowerValue MEMBER m_generatorPowerValue NOTIFY liveDataChanged)
    Q_PROPERTY(QString generatorPowerUnit MEMBER m_generatorPowerUnit NOTIFY liveDataChanged)
    Q_PROPERTY(qreal homePowerValue MEMBER m_homePowerValue NOTIFY liveDataChanged)
    Q_PROPERTY(QString homePowerUnit MEMBER m_homePowerUnit NOTIFY liveDataChanged)
    Q_PROPERTY(qreal gridPowerValue MEMBER m_gridPowerValue NOTIFY liveDataChanged)
    Q_PROPERTY(QString gridPowerUnit MEMBER m_gridPowerUnit NOTIFY liveDataChanged)

public:
    explicit LiveModel(QObject* parent = nullptr);

    void feedPower(uint32_t timestamp, double gridPower, std::vector<double> generatorPowers);

signals:
    void liveDataChanged();

private:
    QString lastUpdate() const;

    //std::map<uint32_t, cts::CiotusMessage> m_generatorData;
    std::vector<std::pair<uint32_t, double>> m_generators;
    uint8_t m_homeChannel = 0;
    uint8_t m_gridChannel = 0;
    std::pair<uint32_t, double> m_grid;

    QDateTime m_lastUpdate;
    double m_generatorPowerValue = 0.0;
    QString m_generatorPowerUnit = "W";
    double m_homePowerValue = 0.0;
    QString m_homePowerUnit = "W";
    double m_gridPowerValue = 0.0;
    QString m_gridPowerUnit = "W";

};

#endif // LIVEMODEL_H
