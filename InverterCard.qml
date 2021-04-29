import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.1
import QtQuick.Shapes 1.15
import MqttClient 1.0

Item {
    id: inverterCard

    property var inverter: 0

    width: 344
    //height: 88 + gauge.implicitHeight + 16
    height: 240-8 //+ gauge.pointerSize * 2
    x: (parent.width-width)/2

    Popup {
        visible: true
        width: parent.width
        height: parent.height
        leftPadding: 16
        rightPadding: 16
        topPadding: 0
        closePolicy: Popup.NoAutoClose

        Text {
            text: "Inverter " + inverter.name
            color: "white"
            elide: Text.ElideRight
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.baseline: parent.top
            anchors.baselineOffset: 34
            font.weight: Font.Medium
            font.pointSize: 20
        }

        Text {
            id: lastSeen
            text: inverter.lastUpdate
            color: Material.hintTextColor
            font.pointSize: 14
            anchors.baseline: parent.top
            anchors.baselineOffset: 56
        }

        /*
        Text {
            text: inverter.lastUpdate
            color: Material.primaryTextColor
            font.pointSize: 14
            anchors.left: lastSeen.right
            anchors.baseline: parent.top
            anchors.baselineOffset: 56
        }
        */

        Gauge {
            id: gauge
            radius: 64
            y: 72   // Constant for Card Layout
            x: 0
            inverter: inverterCard.inverter
            //anchors.left: parent.left
            //anchors.leftMargin: 16
        }

        GridLayout {
            id: gridLayout
            anchors.left: gauge.right
            anchors.leftMargin: 24
            anchors.right: parent.right
            anchors.top: gauge.top
            columns: 3
            rowSpacing: -4

            Text {
                text: "Yield Total"
                font.pointSize: 12
                bottomPadding: 8
                color: Material.hintTextColor
            }
            Text {
                text: inverter.yieldTotal < 10000000 ? (inverter.yieldTotal/1000).toFixed(0) : (inverter.yieldTotal/1000000).toFixed(2)
                Layout.alignment: Qt.AlignRight
                font.bold: true
                font.pointSize: 14
                bottomPadding: 8
                color: "white"
            }
            Text {
                text: inverter.yieldTotal < 10000000 ? "kWh" : "MWh"
                font.pointSize: 12
                bottomPadding: 8
                color: "white"
            }

            Text {
                text: "Yield Today"
                font.pointSize: 12
                bottomPadding: 8
                color: Material.hintTextColor
            }
            Text {
                text: (inverter.yieldToday/1000).toFixed(1)
                Layout.alignment: Qt.AlignRight
                //Layout.fillWidth: true
                font.bold: true
                font.pointSize: 14
                bottomPadding: 8
                color: "white"
            }
            Text {
                text: "kWh"
                font.pointSize: 12
                bottomPadding: 8
                color: "white"
            }

            Text {
                text: "Power AC"
                font.pointSize: 12
                bottomPadding: 8
                color: Material.hintTextColor
            }
            Text {
                text: inverter.powerAc < 10000 ? inverter.powerAc.toFixed(0) : (inverter.powerAc/1000.0).toFixed(1)
                Layout.alignment: Qt.AlignRight
                font.bold: true
                font.pointSize: 14
                bottomPadding: 8
                color: "white"
            }
            Text {
                text: inverter.powerAc < 10000 ? "W" : "kW"
                font.pointSize: 12
                bottomPadding: 8
                color: "white"
            }

            Text {
                text: "Efficiency"
                font.pointSize: 12
                bottomPadding: 8
                color: Material.hintTextColor
            }
            Text {
                text: ((inverter.powerAc/inverter.powerDcTotal) * 100.0).toFixed(1)
                Layout.alignment: Qt.AlignRight
                font.bold: true
                font.pointSize: 14
                bottomPadding: 8
                color: "white"
            }
            Text {
                text: "%"
                font.pointSize: 12
                bottomPadding: 8
                color: "white"
            }

            // Just for spacing
            Text {
                text: ""
                font.pointSize: 12
                bottomPadding: 8
                color: Material.hintTextColor
            }
            Text {
                text: ""
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignRight
                font.bold: true
                font.pointSize: 14
                bottomPadding: 8
                color: "white"
            }
            Text {
                text: ""
                font.pointSize: 12
                bottomPadding: 8
                color: "white"
            }
        } // GridLayout
    } // Popup
}
