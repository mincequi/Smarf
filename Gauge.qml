import QtQuick 2.11
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.15
import QtQuick.Shapes 1.15

import QtGraphicalEffects 1.12

Item {
    id: gauge

    property var inverter: 0
    property var radius: 64
    property var strokeWidth: 8
    property var pointerSize: 10
    property var barMargin: 2
    property var barCount: inverter.stringLiveData.length

    //Layout.fillWidth: true
    //Layout.fillHeight: true
    implicitWidth: radius*2 + Math.max(gauge.strokeWidth, 2*gauge.pointerSize)
    implicitHeight: radius*2 + Math.max(gauge.strokeWidth, 2*gauge.pointerSize)
    //anchors.centerIn: parent
    //anchors.bottom: parent.bottom
    //anchors.right: parent.right
    // multisample, decide based on your scene settings
    layer.enabled: true
    layer.samples: 4

    // Gauge 1
    Shape {
        id: gauge1
        ShapePath {
            fillColor: "transparent"
            strokeColor: Material.color(Material.Grey, Material.Shade900)
            strokeWidth: gauge.strokeWidth
            capStyle: ShapePath.FlatCap

            PathAngleArc {
                centerX: width/2 //radius + strokeWidth/2
                centerY: width/2 //radius + strokeWidth/2
                radiusX: radius
                radiusY: radius
                startAngle: 90
                sweepAngle: 270
            }
        }

        ShapePath {
            fillColor: "transparent"
            strokeColor: Material.color(Material.Blue, Material.Shade500)
            strokeWidth: gauge.strokeWidth
            capStyle: ShapePath.FlatCap
            Material.elevation: 4

            PathAngleArc {
                centerX: width/2 //radius + strokeWidth/2
                centerY: width/2 //radius + strokeWidth/2
                radiusX: radius
                radiusY: radius
                startAngle: 90
                sweepAngle: inverter.stringLiveData[0].power/inverter.stringLiveData[0].powerPeak*270.0

                Behavior on sweepAngle { SmoothedAnimation { duration: 4000; velocity: -1; easing.type: "OutQuad" } }
            }
        }

        GaugePointer {
            x: gauge.width/2 // gauge.radius + strokeWidth/2
            y: gauge.width/2 //gauge.radius + strokeWidth/2
            size: pointerSize
            radius: gauge.radius
            color: Material.color(Material.Blue, Material.Shade500)
            rotation: inverter.stringLiveData[0].powerPeakToday/inverter.stringLiveData[0].powerPeak*270.0
        }

        Text {
            x: gauge.radius + strokeWidth + gauge.pointerSize/2
            y: 2*gauge.radius + gauge.pointerSize/2 - 1
            text: inverter.stringLiveData[0].name
            //anchors.bottom: gauge.bottom
            //anchors.baseline: parent.bottom
            font.pixelSize: 10
            color: Material.color(Material.Blue, Material.Shade500)
        }
    }

    // Gauge 2
    Shape {
        id: gauge2
        visible: barCount  > 1
        ShapePath {
            fillColor: "transparent"
            strokeColor: Material.color(Material.Grey, Material.Shade900)
            strokeWidth: gauge.strokeWidth
            capStyle: ShapePath.FlatCap

            PathAngleArc {
                centerX: width/2
                centerY: height/2
                radiusX: gauge.radius - gauge.strokeWidth - gauge.barMargin
                radiusY: gauge.radius - gauge.strokeWidth - gauge.barMargin
                startAngle: 90
                sweepAngle: 270
            }
        }

        ShapePath {
            fillColor: "transparent"
            strokeColor: Material.color(Material.Teal, Material.Shade500)
            strokeWidth: gauge.strokeWidth
            capStyle: ShapePath.FlatCap
            Material.elevation: 4

            PathAngleArc {
                centerX: width/2
                centerY: height/2
                radiusX: gauge.radius - gauge.strokeWidth - gauge.barMargin
                radiusY: gauge.radius - gauge.strokeWidth - gauge.barMargin
                startAngle: 90
                sweepAngle: inverter.stringLiveData[1].power/inverter.stringLiveData[1].powerPeak*270.0

                Behavior on sweepAngle { SmoothedAnimation { duration: 4000; velocity: -1; easing.type: "OutQuad" } }
            }
        }

        GaugePointer {
            x: gauge.width/2 // gauge.radius + strokeWidth/2
            y: gauge.width/2 //gauge.radius + strokeWidth/2
            size: -pointerSize
            radius: gauge.radius - gauge.strokeWidth - gauge.barMargin
            color: Material.color(Material.Teal, Material.Shade500)
            rotation: inverter.stringLiveData[1].powerPeakToday/inverter.stringLiveData[1].powerPeak*270.0
        }

        Text {
            x: gauge.radius + strokeWidth + gauge.pointerSize/2
            y: 2*gauge.radius - strokeWidth - gauge.barMargin - 1 + gauge.pointerSize/2
            text: inverter.stringLiveData[1].name
            font.pixelSize: 10
            color: Material.color(Material.Teal, Material.Shade500)
        }
    } // Shape

    // Text
    GridLayout {
        anchors.right: parent.right
        anchors.rightMargin: gauge.pointerSize/2
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: (gauge.radius + strokeWidth/2 - barCount * strokeWidth - (barCount-1)*barMargin)/2
        columns: 2
        rowSpacing: -6.0
        Text {
            Layout.alignment: Qt.AlignRight
            color: Material.color(Material.Blue, Material.Shade500)
            text: "10023" //inverter.stringLiveData[0].power < 10000 ? inverter.stringLiveData[0].power.toFixed(0) : (inverter.stringLiveData[0].power/1000.0).toFixed(1)
            font.bold: true
            font.pointSize: 20
        }
        Text {
            Layout.alignment: Qt.AlignRight
            color: Material.color(Material.Blue, Material.Shade500)
            text: "W" //inverter.stringLiveData[0].power < 10000 ? "W" : "kW"
            font.pointSize: 16
        }
        Text {
            id: readout2
            visible: barCount > 1
            Layout.alignment: Qt.AlignRight
            color: Material.color(Material.Teal, Material.Shade500)
            text: inverter.stringLiveData[1].power < 10000 ? inverter.stringLiveData[1].power.toFixed(0) : (inverter.stringLiveData[1].power/1000.0).toFixed(1)
            font.bold: true
            font.pointSize: 20
        }
        Text {
            id: unit2
            visible: barCount > 1
            Layout.alignment: Qt.AlignRight
            color: Material.color(Material.Teal, Material.Shade500)
            text: inverter.stringLiveData[1].power < 10000 ? "W" : "kW"
            font.pointSize: 16
        }
    }

} // Item
