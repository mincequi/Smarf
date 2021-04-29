import QtQuick 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Shapes 1.15

Item {
    id: item
    property var radius: 64
    property var color: Material.color(Material.Blue, Material.Shade500)
    property var size: 8

    Behavior on rotation { SmoothedAnimation { duration: 4000; velocity: -1; easing.type: "OutQuad" } }

    Shape {
        ShapePath {
            strokeWidth: 1
            strokeColor: "#121212"
            fillColor: item.color
            startY: item.radius
            PathLine { relativeX: size/2; relativeY: size }
            PathLine { relativeX: -size; relativeY: 0 }
            PathLine { relativeX: size/2; relativeY: -size }
        }
    }
}
