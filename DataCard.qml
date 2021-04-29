import QtCharts 2.15
import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.1
import QtQuick.Shapes 1.15
import MqttClient 1.0
import Smarf.ThemeModel 1.0

Item {
    id: dataCard

    width: 344
    height: 240-8 //+ gauge.pointerSize * 2
    x: (parent.width-width)/2

    Popup {
        visible: true
        width: parent.width
        height: parent.height
        leftPadding: 0
        rightPadding: 0
        topPadding: 0
        bottomPadding: 0
        margins: 0
        closePolicy: Popup.NoAutoClose

        ChartView {
            backgroundColor: "transparent"
            margins.left: 0
            margins.right: 0
            margins.top: 0
            margins.bottom: 0
            anchors.fill: parent
            antialiasing: true
            legend.visible: false

            // Define x-axis to be used with the series instead of default one
            ValueAxis {
                id: valueAxis
                min: 6
                max: 18
                tickCount: 7
                labelFormat: "%.0f"
                gridVisible: false
            }

            AreaSeries {
                name: "East"
                color: ThemeModel.primaryColor
                axisX: valueAxis
                upperSeries: LineSeries {
                    XYPoint { x: 0; y: 1 }
                    XYPoint { x: 1; y: 1 }
                    XYPoint { x: 2; y: 1 }
                    XYPoint { x: 3; y: 1 }
                    XYPoint { x: 4; y: 1 }
                    XYPoint { x: 5; y: 0 }
                    XYPoint { x: 6; y: 1 }
                    XYPoint { x: 7; y: 1 }
                    XYPoint { x: 8; y: 4 }
                    XYPoint { x: 9; y: 7 }
                    XYPoint { x: 10; y: 12 }
                    XYPoint { x: 11; y: 14 }
                    XYPoint { x: 12; y: 15 }
                    XYPoint { x: 13; y: 13 }
                    XYPoint { x: 14; y: 12 }
                    XYPoint { x: 15; y: 11 }
                    XYPoint { x: 16; y: 7 }
                    XYPoint { x: 17; y: 4 }
                    XYPoint { x: 18; y: 2 }
                    XYPoint { x: 19; y: 1 }
                    XYPoint { x: 20; y: 0 }
                    XYPoint { x: 21; y: 1 }
                    XYPoint { x: 22; y: 0 }
                    XYPoint { x: 23; y: 1 }
                    XYPoint { x: 24; y: 0 }
                } // LineSeries
            } // AreaSeries
        } // ChartView
    } // Popup
}
