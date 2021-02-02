import QtQuick 2.11
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.15
import QtQuick.Shapes 1.15

import QtGraphicalEffects 1.12

Item {
    id: gauge

    property var inverter: 0
    property var radius: 80
    property var strokeWidth: 12
    property var margin: 4
    property var barCount: 2

    //Layout.fillWidth: true
    //Layout.fillHeight: true
    implicitWidth: radius*2 + strokeWidth
    implicitHeight: radius*2 + strokeWidth
    //anchors.centerIn: parent
    //anchors.bottom: parent.bottom
    //anchors.right: parent.right
    // multisample, decide based on your scene settings
    layer.enabled: true
    layer.samples: 4

    Shape {
        id: gauge1
        ShapePath {
            fillColor: "transparent"
            strokeColor: Material.color(Material.Grey, Material.Shade900)
            strokeWidth: gauge.strokeWidth
            capStyle: ShapePath.FlatCap

            PathAngleArc {
                centerX: width/2
                centerY: height/2
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
                centerX: width/2
                centerY: height/2
                radiusX: radius
                radiusY: radius
                startAngle: 90
                sweepAngle: inverter.powerDc[0]

                Behavior on sweepAngle { SmoothedAnimation { duration: 4000; velocity: -1; easing.type: "OutQuad" } }
            }
        }

        Text {
            x: radius + strokeWidth
            y: 2*radius //+ implicitHeight/2
            text: "MPP A"
            //font.bold: true
            font.pixelSize: 12
            color: Material.color(Material.Blue, Material.Shade500)
        }
    }

    Shape {
        id: gauge2
        visible: barCount > 1
        ShapePath {
            fillColor: "transparent"
            strokeColor: Material.color(Material.Grey, Material.Shade900)
            strokeWidth: gauge.strokeWidth
            capStyle: ShapePath.FlatCap

            PathAngleArc {
                centerX: width/2
                centerY: height/2
                radiusX: gauge.radius - gauge.strokeWidth - gauge.margin
                radiusY: gauge.radius - gauge.strokeWidth - gauge.margin
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
                radiusX: gauge.radius - gauge.strokeWidth - gauge.margin
                radiusY: gauge.radius - gauge.strokeWidth - gauge.margin
                startAngle: 90
                sweepAngle: inverter.powerDc[1]

                Behavior on sweepAngle { SmoothedAnimation { duration: 4000; velocity: -1; easing.type: "OutQuad" } }
            }
        }

        Text {
            x: radius + strokeWidth
            y: 2*radius - strokeWidth - margin
            text: "MPP B"
            //font.bold: true
            font.pixelSize: 12
            color: Material.color(Material.Teal, Material.Shade500)
        }
    } // Shape

    GridLayout {
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: (radius + strokeWidth/2 - barCount * strokeWidth - (barCount-1)*margin)/2
        columns: 2
        rowSpacing: -8.0
        Text {
            Layout.alignment: Qt.AlignRight
            color: Material.color(Material.Blue, Material.Shade500)
            text: "5135"
            font.bold: true
            font.pointSize: 24
        }
        Text {
            Layout.alignment: Qt.AlignRight
            color: Material.color(Material.Blue, Material.Shade500)
            text: "W"
            font.pointSize: 20
        }
        Text {
            id: readout2
            visible: barCount > 1
            Layout.alignment: Qt.AlignRight
            color: Material.color(Material.Teal, Material.Shade500)
            text: "5.23"
            font.bold: true
            font.pointSize: 24
        }
        Text {
            id: unit2
            visible: barCount > 1
            Layout.alignment: Qt.AlignRight
            color: Material.color(Material.Teal, Material.Shade500)
            text: "kW"
            font.pointSize: 20
        }
    }

} // Item
