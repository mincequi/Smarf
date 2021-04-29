import QtQuick 2.12
import QtQuick.Templates 2.12 as T
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12
import QtQuick.Layouts 1.15

T.TextField {
    id: control

    property alias labelText: labelField.text
    property alias helperText: helperField.text
    property bool hasError

    Layout.fillWidth: true
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             contentHeight + topPadding + bottomPadding,
                             placeholder.implicitHeight + topPadding + bottomPadding)

    topPadding: 8
    bottomPadding: 16

    color: enabled ? Material.foreground : Material.hintTextColor
    selectionColor: Material.accentColor
    selectedTextColor: Material.primaryHighlightedTextColor
    placeholderTextColor: Material.hintTextColor
    verticalAlignment: TextInput.AlignVCenter

    cursorDelegate: CursorDelegate { }

    PlaceholderText {
        id: placeholder
        x: control.leftPadding
        y: control.topPadding
        width: control.width - (control.leftPadding + control.rightPadding)
        height: control.height - (control.topPadding + control.bottomPadding)
        text: control.placeholderText
        font: control.font
        color: control.placeholderTextColor
        verticalAlignment: control.verticalAlignment
        elide: Text.ElideRight
        renderType: control.renderType
        visible: !control.length && !control.preeditText && (!control.activeFocus || control.horizontalAlignment !== Qt.AlignHCenter)
    }

    background: Rectangle {
        y: control.height - height - control.bottomPadding + 8
        width: control.width
        height: control.activeFocus || control.hovered ? 2 : 1
        color: control.activeFocus ? control.Material.accentColor
                                   : (control.hovered ? control.Material.primaryTextColor : control.Material.hintTextColor)
    }

    Text {
        id: labelField
        font.pointSize: 12
        x: control.leftPadding
        anchors.baseline: parent.top
        anchors.baselineOffset: -8
        color: control.activeFocus ? control.Material.accentColor
                                   : (control.hovered ? control.Material.primaryTextColor : control.Material.hintTextColor)
    }

    Text {
        id: helperField
        font.pointSize: 12
        anchors.right: background.right
        anchors.rightMargin: 12
        color: control.hasError ? "#CF6679" : Material.hintTextColor
        anchors.baseline: background.bottom
        anchors.baselineOffset: 16
    }
}
