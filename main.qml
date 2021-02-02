import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
//import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.1
import QtQuick.Shapes 1.15
import MqttClient 1.0

ApplicationWindow {
    visible: true
    width: 375
    height: 667
    //width: 768
    //height: 1024
    title: "Smarf - A SMA Remote Facility"
    id: root

    Material.theme: Material.Dark

    property var inverterModel: 0
    property var portNumber: 1883   // workaround to assign port to MqttClient

    MqttClient {
        id: client
        hostname: hostnameField.text
        port: portNumber
    }

    GridLayout {
        id: gridLayout
        Layout.fillWidth: true
        anchors.margins: 10
        columns: 2

        Label {
            text: "Hostname:"
            enabled: client.state === MqttClient.Disconnected
        }

        TextField {
            id: hostnameField
            Layout.fillWidth: true
            text: "broker.hivemq.com"
            placeholderText: "<Your plant's MQTT broker>"
            enabled: client.state === MqttClient.Disconnected
        }

        Label {
            text: "Plant name:"
            enabled: client.state === MqttClient.Disconnected
        }

        TextField {
            id: plantnameField
            Layout.fillWidth: true
            text: "RohrbachII"
            placeholderText: "<Your plant's name>"
            enabled: client.state === MqttClient.Disconnected
        }

        Button {
            id: connectButton
            Layout.fillWidth: true
            text: client.state === MqttClient.Connected ? "Disconnect" : "Connect"
            onClicked: {
                if (client.state === MqttClient.Connected) {
                    client.disconnectFromHost()
                } else
                    client.connectToPlant(plantnameField.text)
            }
        }

        Button {
            id: toggleButton
            Layout.fillWidth: true
            text: "Toggle"
            onClicked: {
                client.toggleMppCount()
            }
        }
    } // GridLayout

    Flow {
        Layout.columnSpan: 2
        anchors.top: gridLayout.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: lastUpdateLabel.top

        Label {
            text: "DFSFDF"
        }

        Repeater {
            model: client.inverters

            Gauge {
                barCount: 2
                inverter: modelData
            }
        } // Repeater
    }

    Label {
        id: lastUpdateLabel
        anchors.bottom: statusLine.top
        Layout.columnSpan: 2
        Layout.fillWidth: true
        //color: "#333333"
        text: inverterModel.lastUpdate
    }

    Label {
        id: statusLine
        function stateToString(value) {
            if (value === 0)
                return "Disconnected"
            else if (value === 1)
                return "Connecting"
            else if (value === 2)
                return "Connected"
            else
                return "Unknown"
        }

        anchors.left: parent.left
        anchors.bottom: parent.bottom
        Layout.columnSpan: 2
        Layout.fillWidth: true
        //color: "#333333"
        text: "Status:" + stateToString(client.state) + "(" + client.state + ")"
        enabled: client.state === MqttClient.Connected
    }
}
