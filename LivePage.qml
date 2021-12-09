import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import QtQuick.Window 2.15

import Smarf.LiveModel 1.0

Item {

    property int flowDistance: 20

    LiveNode {
        id: generator1
        icon: "qrc:/icons/solar-power.svg"
        value: LiveModel.generatorPowerValue
        unit: LiveModel.generatorPowerUnit
        anchors.top: statusLabel.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 16
    }

    LiveNode {
        id: grid
        icon: "qrc:/icons/transmission-tower.svg"
        value: Math.abs(LiveModel.gridPowerValue)
        unit: LiveModel.gridPowerUnit
        orientation: LiveNode.Orientation.Vertical
        anchors.left: parent.left
        anchors.top: generator1.bottom
        anchors.margins: 16
    }

    LiveNode {
        id: home
        icon: "qrc:/icons/home.svg"
        value: Math.abs(LiveModel.homePowerValue)
        unit: LiveModel.homePowerUnit
        anchors.top: grid.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 16
    }

    Shape {
        visible: LiveModel.gridPowerValue > 0.0
        ShapePath {
            id: generatorToGrid
            strokeColor: "white"
            strokeWidth: 2.0
            fillColor: "transparent"
            capStyle: ShapePath.FlatCap
            startX: generator1.x + generator1.width*0.5 - flowDistance
            startY: generator1.y + generator1.height
            PathQuad {
                x: grid.x + grid.width
                y: grid.y + grid.height*0.5
                controlX: generatorToGrid.startX
                controlY: y
            }
        }
        ShapePath {
            id: generatorToGridArrow
            strokeColor: "white"
            fillColor: "transparent"
            strokeWidth: 2.0
            capStyle: ShapePath.FlatCap
            startX: grid.x + grid.width + 8
            startY: grid.y + grid.height*0.5 - 8
            PathLine { x: grid.x + grid.width; y: grid.y + grid.height*0.5 }
            PathLine { x: grid.x + grid.width + 8; y: grid.y + grid.height*0.5 + 8}
        }
    }

    Shape {
        visible: LiveModel.homePowerValue < 0.0
        ShapePath {
            id: generatorToHome
            strokeColor: "white"
            strokeWidth: 2.0
            fillColor: "transparent"
            capStyle: ShapePath.FlatCap
            startX: generator1.x + generator1.width*0.5
            startY: generator1.y + generator1.height
            PathQuad {
                x: home.x + home.width*0.5
                y: home.y
                controlX: generatorToHome.startX
                controlY: y
            }
        }
        ShapePath {
            id: generatorToHomeArrow
            strokeColor: "white"
            fillColor: "transparent"
            strokeWidth: 2.0
            startX: home.x + home.width*0.5 - 8
            startY: home.y - 8
            PathLine { x: home.x + home.width*0.5; y: home.y }
            PathLine { x: home.x + home.width*0.5 + 8; y: home.y - 8 }
        }
    }

    Shape {
        visible: LiveModel.gridPowerValue < 0.0
        ShapePath {
            id: gridToHome
            strokeColor: "white"
            strokeWidth: 2.0
            fillColor: "transparent"
            capStyle: ShapePath.FlatCap
            startX: grid.x + grid.width
            startY: grid.y + grid.height*0.5
            PathQuad {
                x: home.x + home.width*0.5 - flowDistance
                y: home.y
                controlX: x
                controlY: gridToHome.startY
            }
        }
        ShapePath {
            id: gridToHomeArrow
            strokeColor: "white"
            fillColor: "transparent"
            strokeWidth: 2.0
            startX: home.x + home.width*0.5 - 8 - flowDistance
            startY: home.y - 8
            PathLine { x: home.x + home.width*0.5 - flowDistance; y: home.y }
            PathLine { x: home.x + home.width*0.5 + 8 - flowDistance; y: home.y - 8 }
        }
    }
}
