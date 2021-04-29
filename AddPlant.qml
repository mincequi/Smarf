import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.15

import MqttClient 1.0

Item {
    property var client: 0

    function stateToString(value) {
        if (value === 0)
            return "Unknown"
        else if (value === 1)
            return "Checking"
        else if (value === 2)
            return "Invalid"
        else if (value === 3)
            return "Valid"
        else
            return "Unknown"
    }

    Dialog {
        id: opoup
        //anchors.centerIn: parent
        Layout.fillWidth: true
        Layout.margins: 24
        width: parent.width - 32
        x: (parent.width - width)/2
        y: 240

        footer: DialogButtonBox {
            id: buttons
            standardButtons: Dialog.Ok | Dialog.Cancel
        }

        onAccepted: {
            client.subscribeToInverter()
        }

        GridLayout {
            id: gridLayout
            width: parent.width
            columns: 2
            rowSpacing: 16

            Text {
                text: "Host"
                bottomPadding: 8
                color: hostnameField.activeFocus ? Material.accentColor
                                           : (hostnameField.hovered ? Material.primaryTextColor : Material.hintTextColor)
            }

            MaterialTextField {
                function clientStateToString(value) {
                    if (value === 0)
                        return "Disconnected"
                    else if (value === 1)
                        return "Connecting"
                    else if (value === 2)
                        return "Connected"
                    else
                        return "Unknown"
                }

                id: hostnameField
                Layout.fillWidth: true
                text: "broker.hivemq.com"
                helperText: clientStateToString(client.state)
                hasError: false
                placeholderText: "<Address>"
                leftPadding: 16
                onTextChanged: {
                    client.validateHost(text)
                }
                onVisibleChanged: {
                    if (visible) {
                        client.validateHost(text)
                    }
                }
            }

            /*
            Text {
                text: "Plant"
                bottomPadding: 8
                color: plantnameField.activeFocus ? Material.accentColor
                                           : (plantnameField.hovered ? Material.primaryTextColor : Material.hintTextColor)
            }

            MaterialTextField {
                id: plantnameField
                Layout.fillWidth: true
                text: ""
                helperText: stateToString(client.plantState)
                placeholderText: "<Name>"
                leftPadding: 16
                enabled: client.state === MqttClient.Connected
                onTextChanged: {
                    client.validatePlant(text)
                }
            }
            */

            Text {
                text: "Inverter"
                bottomPadding: 8
                color: inverterField.activeFocus ? Material.accentColor
                                                 : (inverterField.hovered ? Material.primaryTextColor : Material.hintTextColor)
            }

            MaterialTextField {
                id: inverterField
                Layout.fillWidth: true
                text: client.currentInverter
                helperText: stateToString(client.inverterState)
                placeholderText: "<Serial>"
                inputMethodHints: Qt.ImhDigitsOnly
                //validator: IntValidator { bottom: 2000000000; top: 3009999999 }
                validator: RegExpValidator { regExp: /[0-9]{10}/ }
                leftPadding: 16
                enabled: client.state === MqttClient.Connected
                onTextChanged: {
                    client.validateInverter(text)
                }
            }
        } // GridLayout
    } // Popup

    RoundButton {
        visible: !opoup.opened
        height: 48
        //width: 56
        leftPadding: 12
        rightPadding: 20
        icon.source: "qrc:/icons/wrench.svg"
        icon.height: 24
        text: "Set Inverter"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 16
        onClicked: {
            // Anchors do not seem to work with Menus/Popups, so use absolute placement
            //opoup.x = parent.width-16
            opoup.open()
        }
    }

    RoundButton {
        visible: opoup.opened
        height: 56
        width: 56
        icon.source: "qrc:/icons/close-24px.svg"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 16
        onClicked: {
            opoup.close()
        }
    }
} // Item
