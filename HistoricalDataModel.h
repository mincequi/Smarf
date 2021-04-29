#ifndef HISTORICALDATAMODEL_H
#define HISTORICALDATAMODEL_H

#include <QLineSeries>
#include <QObject>

class HistoricalDataModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QtCharts::QLineSeries* powerString1 READ powerString1)
    Q_PROPERTY(QtCharts::QLineSeries* powerString2 READ powerString2)
    Q_PROPERTY(QtCharts::QLineSeries* powerTotal READ powerTotal)

public:
    explicit HistoricalDataModel(QObject *parent = nullptr);

    QtCharts::QLineSeries* powerString1();
    QtCharts::QLineSeries* powerString2();
    QtCharts::QLineSeries* powerTotal();

signals:

private:
    void onDataReceived(const QMap<QString, QVariant>& data);

    QtCharts::QLineSeries m_powerString1;
    QtCharts::QLineSeries m_powerString2;
    QtCharts::QLineSeries m_powerTotal;
};

#endif // HISTORICALDATAMODEL_H
