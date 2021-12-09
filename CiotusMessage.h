#pragma once

#include <QByteArray>
#include <QDateTime>

#include "CiotusTypes.h"

namespace cts {

class CiotusMessageBuilder;

class CiotusMessage {
public:
    CiotusMessage();
    ~CiotusMessage();
    static CiotusMessage fromByteArray(const QByteArray& data);
    static CiotusMessageBuilder create();
    static CiotusMessageBuilder createFrom(const CiotusMessage& from);

    QVariant value(Property property) const;

    DeviceClass deviceClass() const;
    uint32_t deviceId() const;
    QDateTime timestamp() const;
    double power() const;

private:
    friend class CiotusMessageBuilder;
    QMap<QString, QVariant> m_map;
};

class CiotusMessageBuilder {
public:
    operator CiotusMessage() const;

    CiotusMessageBuilder& deviceClass(DeviceClass deviceClass);
    CiotusMessageBuilder& deviceId(uint32_t deviceId);
    CiotusMessageBuilder& timestamp(const QDateTime& timestamp);
    CiotusMessageBuilder& power(double power);

private:
    CiotusMessageBuilder();
    CiotusMessageBuilder(const CiotusMessage& from);

    friend class CiotusMessage;
    CiotusMessage msg;
};

} // namespace cts
