#include "CiotusMessage.h"

#include <msgpack.h>

namespace cts {

CiotusMessage::CiotusMessage() {
}

CiotusMessage::~CiotusMessage() {
}

CiotusMessage CiotusMessage::fromByteArray(const QByteArray& data) {
    CiotusMessage msg;
    msg.m_map = MsgPack::unpack(data).toMap();

    return msg;
}

CiotusMessageBuilder CiotusMessage::create() {
    return CiotusMessageBuilder();
}

CiotusMessageBuilder CiotusMessage::createFrom(const CiotusMessage& from) {
    return CiotusMessageBuilder(from);
}

QVariant CiotusMessage::value(Property property) const {
    return m_map.value(QString::number(static_cast<int>(property)));
}

DeviceClass CiotusMessage::deviceClass() const {
    return static_cast<DeviceClass>(m_map.value(QString::number(static_cast<int>(Property::DeviceClass)), 0).toUInt());
}

uint32_t CiotusMessage::deviceId() const {
    return m_map.value(QString::number(static_cast<int>(Property::DeviceId)), 0).toUInt();
}

QDateTime CiotusMessage::timestamp() const {
    return m_map.value(QString::number(static_cast<int>(Property::Timestamp)), 0).toDateTime();
}

double CiotusMessage::power() const {
    return m_map.value(QString::number(static_cast<int>(Property::Power)), 0.0).toDouble();
}

CiotusMessageBuilder::CiotusMessageBuilder() {
}

CiotusMessageBuilder::CiotusMessageBuilder(const CiotusMessage& from) {
    msg = from;
}

CiotusMessageBuilder::operator CiotusMessage() const {
    return msg;
}

CiotusMessageBuilder& CiotusMessageBuilder::deviceClass(DeviceClass deviceClass) {
    msg.m_map[QString::number(static_cast<int>(Property::DeviceClass))] = static_cast<uint32_t>(deviceClass);
    return *this;
}

CiotusMessageBuilder& CiotusMessageBuilder::deviceId(uint32_t deviceId) {
    msg.m_map[QString::number(static_cast<int>(Property::DeviceId))] = deviceId;
    return *this;
}

CiotusMessageBuilder& CiotusMessageBuilder::timestamp(const QDateTime& timestamp) {
    msg.m_map[QString::number(static_cast<int>(Property::Timestamp))] = timestamp;
    return *this;
}

CiotusMessageBuilder& CiotusMessageBuilder::power(double power) {
    msg.m_map[QString::number(static_cast<int>(Property::Power))] = power;
    return *this;
}

} // namespace cts
