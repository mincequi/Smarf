#include "Persistence.h"

#include <QDate>
#include <QStringList>

#include "CiotusTypes.h"

Persistence::Persistence(QObject *parent) : QObject(parent),
    m_settings("mincequi", "Smarf")
{
}

void Persistence::setCurrentHost(const QString& hostName)
{
    m_settings.setValue("currentHostName", hostName);
}

QString Persistence::currentHost() const
{
    return m_settings.value("currentHostName").toString();
}

void Persistence::setCurrentInverter(const QString& plantName)
{
    m_settings.setValue("currentPlant", plantName);
}

QString Persistence::currentInverter() const
{
    return m_settings.value("currentPlant").toString();
}

QStringList Persistence::plants() const
{
    return m_settings.allKeys();
}

PlantConfig Persistence::plantConfig(const QString& plantName)
{
    PlantConfig config;

    // "plants/<plantName>/<inverterNumber>/config"
    m_settings.beginGroup("plants");
    m_settings.beginGroup(plantName);
    for (const QString& inverter : m_settings.childKeys()) {
        m_settings.beginGroup(inverter);
        config.append(m_settings.value("config"));
        m_settings.endGroup();
    }
    m_settings.endGroup();
    m_settings.endGroup();

    return config;
}

void Persistence::setPlantConfig(const QString& plantName, const PlantConfig& config)
{
    // "plants/<plantName>/<inverterNumber>/config"
    m_settings.beginGroup("plants");
    m_settings.beginGroup(plantName);
    int i = 0;
    for (const QVariant& inverter : config) {
        m_settings.beginGroup(QString::number(i)); // inverterNumber
        m_settings.setValue("config", inverter);
        m_settings.endGroup();
        ++i;
    }
    m_settings.endGroup();
    m_settings.endGroup();
}

PlantLiveData Persistence::plantLiveData(const QString& plantName)
{
    PlantLiveData data;

    // "plants/<plantName>/<inverterNumber>/live"
    m_settings.beginGroup("plants");
    m_settings.beginGroup(plantName);
    for (const QString& inverter : m_settings.childKeys()) {
        m_settings.beginGroup(inverter);
        data.append(m_settings.value("live"));
        m_settings.endGroup();
    }
    m_settings.endGroup();
    m_settings.endGroup();

    return data;
}

void Persistence::setPlantLiveData(const QString& plantName, const PlantLiveData& data)
{
    // "plants/<plantName>/<inverterNumber>/live"
    m_settings.beginGroup("plants");
    m_settings.beginGroup(plantName);
    int i = 0;
    for (const QVariant& inverter : data) {
        m_settings.beginGroup(QString::number(i)); // inverterNumber
        m_settings.setValue("live", inverter);
        m_settings.endGroup();
        ++i;
    }
    m_settings.endGroup();
    m_settings.endGroup();
}

InverterDayData Persistence::inverterDayData(const QString& inverter, const QDate& day)
{
    InverterDayData out;

    m_settings.beginGroup("inverters");
    m_settings.beginGroup(inverter);
    m_settings.beginGroup("dayData");
    QString dayAsString = QString::number(day.toJulianDay());
    out = m_settings.value(dayAsString).toMap();
    m_settings.endGroup();
    m_settings.endGroup();
    m_settings.endGroup();

    return out;
}

void Persistence::setInverterDayData(const QString& inverter, const InverterDayData& data)
{
    m_settings.beginGroup("inverters");
    m_settings.beginGroup(inverter);
    m_settings.beginGroup("dayData");
    QString day = QString::number(data.value(toIntString(cts::Property::Timestamp)).toDate().toJulianDay());
    m_settings.setValue(day, data);
    m_settings.endGroup();
    m_settings.endGroup();
    m_settings.endGroup();
}
