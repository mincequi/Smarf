#include "HistoricalDataModel.h"

#include "Types.h"

#include <QDateTime>

HistoricalDataModel::HistoricalDataModel(QObject *parent) :
    QObject(parent)
{
}

QtCharts::QLineSeries* HistoricalDataModel::powerString1()
{
    return &m_powerString1;
}

QtCharts::QLineSeries* HistoricalDataModel::powerString2()
{
    return &m_powerString2;
}

QtCharts::QLineSeries* HistoricalDataModel::powerTotal()
{
    return &m_powerTotal;
}

void HistoricalDataModel::onDataReceived(const QMap<QString, QVariant>& data)
{
    const auto tss = data.value(toIntString(InverterProperty::Timestamp)).toDateTime();
    const auto interval = data.value(toIntString(InverterProperty::Interval)).toUInt();
    const auto pDc1 = data.value(toIntString(InverterProperty::Strings)).toList().value(0).toMap().value(toIntString(InverterProperty::StringPower)).toList();
    const auto pDc2 = data.value(toIntString(InverterProperty::Strings)).toList().value(1).toMap().value(toIntString(InverterProperty::StringPower)).toList();
    const auto pAc = data.value(toIntString(InverterProperty::Power)).toList();

    {
        QVector<QPointF> pointsDc1;
        pointsDc1.reserve(pDc1.size());
        auto ts = tss;
        uint32_t i = 0;
        for (const auto& dc : pDc1) {
            pointsDc1.push_back(QPointF(ts.addSecs(interval*i*10).toSecsSinceEpoch(), dc.toDouble()));
            ++i;
        }
        m_powerString1.replace(pointsDc1);
    }

    {
        QVector<QPointF> pointsDc2;
        pointsDc2.reserve(pDc2.size());
        auto ts = tss;
        uint32_t i = 0;
        for (const auto& dc : pDc2) {
            pointsDc2.push_back(QPointF(ts.addSecs(interval*i*10).toSecsSinceEpoch(), dc.toDouble()));
            ++i;
        }
        m_powerString2.replace(pointsDc2);
    }

    {
        QVector<QPointF> pointsAc;
        pointsAc.reserve(pAc.size());
        auto ts = tss;
        uint32_t i = 0;
        for (const auto& ac : pAc) {
            pointsAc.push_back(QPointF(ts.addSecs(interval*i*10).toSecsSinceEpoch(), ac.toDouble()));
            ++i;
        }
        m_powerTotal.replace(pointsAc);
    }
}
