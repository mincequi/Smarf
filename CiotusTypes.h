#pragma once

#include <QVariant>

namespace cts {

enum class DeviceClass : uint8_t {
    Unknown = 0,
    SolarInverter = 1,
    EnergyMeter = 2,
};

enum class Property : uint8_t {
    // Static properties
    Version = 0,        // uint: Protocol version

    DeviceClass = 1,    // uint
    DeviceId = 2,       // uint64: Unique id (e.g. serial).
    Timestamp = 3,      // Timestamp for this data set
    Name = 4,           // str[31]: human readable name
    Coordinates = 5,    // geo coordinates ext type

    PowerMax = 7,   // Nominal inverter power

    // Dynamic properties

    Interval = 13,      // Interval in 5 seconds steps
    YieldTotal = 9,     // Total yield in Wh
    YieldToday = 10,    // Today's yield in Wh
    Power = 11,         // Current power
    PowerMaxToday = 12, // Today's peak power

    // Key for PV string properties (stored in array of maps)
    Strings = 16,       // Data per PV string

    // String specific properties
    StringName = Name,
    StringAzimuth = 17,
    StringElevation = 18,
    StringPowerMax = PowerMax,          // Peak power

    // Dynamic
    StringPower = Power,   // Current power
    StringPowerMaxToday = PowerMaxToday, // Today's peak

    PropertyMax = 128
};
} // namespace cts

struct StringConfig
{
    QString name = "MPP";
    //float azimuth = 180.0f;
    //float elevation = 30.0f;
    float powerPeak = 10000.0f;

    static std::vector<StringConfig> fromMsgPack(const QVariant& byteArray);
};

struct InverterConfig
{
    QString     manufacturer;
    QString     name;
    uint32_t    serial = 0;
    QString     mqttHost;
    uint16_t    mqttPort;

    std::vector<StringConfig> strings;

    bool isValid() const;
};

class StringData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name MEMBER name CONSTANT)
    Q_PROPERTY(float power MEMBER power CONSTANT)
    Q_PROPERTY(float powerPeak MEMBER powerPeak CONSTANT)
    Q_PROPERTY(float powerPeakToday MEMBER powerPeakToday CONSTANT)

public:
    StringData(QObject* parent = nullptr);
    ~StringData();

    QString name = "MPP";
    float power = 0.0f;
    float powerPeak = 10000.0f;
    float powerPeakToday = 0.0f;
};

QString toIntString(cts::Property prop);
