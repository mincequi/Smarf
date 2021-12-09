import QtQuick 2.0
import QtQuick.Controls 2.15

Item {
    property alias icon: button.icon.source
    property alias iconWidth: button.icon.width
    property alias iconHeight: button.icon.height

    property alias value: value.text
    property alias unit: unit.text

    property int orientation: LiveNode.Orientation.Horizontal

    width: iconWidth + 16
    height: iconHeight + 16

    enum Orientation {
        Horizontal,
        Vertical
    }

    Button {
        id: button
        flat: true
        checkable: false
        icon.height: 80
        icon.width: 80
    }

    Text {
        id: value
        anchors.left: orientation === LiveNode.Orientation.Horizontal ? button.right : undefined
        anchors.right: orientation === LiveNode.Orientation.Horizontal ? undefined : unit.left
        anchors.rightMargin: 4.0
        anchors.baseline: unit.baseline
        color: "white"
        text: "1234"
        font.bold: true
        font.pointSize: 20
    }
    Text {
        id: unit
        anchors.left: orientation === LiveNode.Orientation.Horizontal ? value.right : undefined
        anchors.right: orientation === LiveNode.Orientation.Horizontal ? undefined : button.right
        anchors.top: orientation === LiveNode.Orientation.Horizontal ? undefined : button.bottom
        anchors.leftMargin: 4.0
        anchors.rightMargin: 16.0
        anchors.verticalCenter: orientation === LiveNode.Orientation.Horizontal ? button.verticalCenter : undefined
        color: "white"
        text: "W"
        font.pointSize: 16
    }
}
