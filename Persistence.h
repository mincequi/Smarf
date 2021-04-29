#pragma once

#include <QObject>
#include <QSettings>

using PlantConfig = QList<QVariant>;
using PlantLiveData = QList<QVariant>;
using InverterDayData = QMap<QString,QVariant>;

class Persistence : public QObject
{
    Q_OBJECT

public:
    explicit Persistence(QObject *parent = nullptr);

    void setCurrentHost(const QString& hostName);
    QString currentHost() const;

    void setCurrentInverter(const QString& plantName);
    QString currentInverter() const;

    QStringList plants() const;

    PlantConfig plantConfig(const QString& plantName);
    void setPlantConfig(const QString& plantName, const PlantConfig& config);

    PlantLiveData plantLiveData(const QString& plantName);
    void setPlantLiveData(const QString& plantName, const PlantLiveData& config);

    InverterDayData inverterDayData(const QString& inverter, const QDate& day);
    void setInverterDayData(const QString& inverter, const InverterDayData& data);

signals:

private:
    QSettings m_settings;
};
