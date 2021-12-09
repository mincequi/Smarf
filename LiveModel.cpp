#include "LiveModel.h"

#include <QDateTime>

#include "CiotusMessage.h"

LiveModel::LiveModel(QObject *parent) :
    QObject(parent) {
}

void LiveModel::feedPower(uint32_t timestamp, double gridPower, std::vector<double> generatorPowers) {
    m_lastUpdate = QDateTime::fromTime_t(timestamp);

    if (abs(gridPower) >= 10000.0) {
        m_gridPowerValue = round(gridPower / 100.0) / 10.0;
        m_gridPowerUnit = "kW";
    } else {
        m_gridPowerValue = round(gridPower / 10.0) * 10.0;
        m_gridPowerUnit = "W";
    }

    double generatorPowerSum = 0.0;
    for (const auto& generator : generatorPowers) {
        generatorPowerSum += generator;
    }
    if (abs(generatorPowerSum) >= 10000.0) {
        m_generatorPowerValue = round(generatorPowerSum / 100.0) / 10.0;
        m_generatorPowerUnit = "kW";
    } else {
        m_generatorPowerValue = round(generatorPowerSum / 10.0) * 10.0;
        m_generatorPowerUnit = "W";
    }

    const double homePower = gridPower - generatorPowerSum;
    if (abs(homePower) >= 10000.0) {
        m_homePowerValue = round(homePower / 100.0) / 10.0;
        m_homePowerUnit = "kW";
    } else {
        m_homePowerValue = round(homePower / 10.0) * 10.0;
        m_homePowerUnit = "W";
    }

    emit liveDataChanged();
}

QString LiveModel::lastUpdate() const {
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

