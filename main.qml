import QtQuick 2.15
import QtQuick.Window 2.2
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.3
import QtQuick.Shapes 1.15
import MqttClient 1.0

import Smarf.LiveModel 1.0
import Smarf.ThemeModel 1.0

ApplicationWindow {
    visible: true
    // iPhone 6, 7, 8, SE2
    width: 375
    height: 667
    //width: 768
    //height: 1024
    title: "Smarf - A SMA Remote Facility"
    id: root

    Material.theme: Material.Dark
    Material.accent: "#BB86FC"
    Material.background: "#121212"

    property var inverterModel: 0

    property int appState: Qt.application.state

    Component.onCompleted: {
        ThemeModel.primaryColor = Material.color(Material.Blue, Material.Shade500)
        ThemeModel.secondaryColor = Material.color(Material.Teal, Material.Shade500)
    }

    /*
    onAppStateChanged: {
        console.log("onAppStateChanged: " + appState)
        switch (appState) {
        case Qt.ApplicationActive:
        case Qt.ApplicationInactive:
            client.start();
            break;
        case Qt.ApplicationHidden:
        case Qt.ApplicationSuspended:
            client.stop();
            break;
        default:
            break;
        }
    }
    */

    MqttClient {
        id: client
    }

    header: ToolBar {

        background: Rectangle {
            implicitHeight: 56
            color: "#2e2300"
        }

        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: qsTr("‹")
                onClicked: stack.pop()
            }
            ColumnLayout {
                Label {
                    text: "Smarf"
                    elide: Label.ElideLeft
                    anchors.bottom: lastSeen.top
                    Layout.fillWidth: true
                }
                Label {
                    id: lastSeen
                    text: LiveModel.lastUpdate
                    color: "gray"
                    font.pointSize: 12
                    font.weight: Font.Thin
                    anchors.bottom: parent.bottom
                    //verticalAlignment: "AlignBottom"
                    elide: Label.ElideLeft
                    Layout.fillWidth: true
                }
            }
            ToolButton {
                text: qsTr("⋮")
                onClicked: menu.open()
            }
        }
    }

    footer: TabBar {
        id: bar
        width: parent.width // anchors.fill: parent
        height: 56
        position: TabBar.Footer
        currentIndex: 0
        TabButton {
            height: 56
            anchors.top: parent.top
            text: qsTr("Live")
            icon.source: "qrc:/icons/speedometer.svg"
            display: AbstractButton.TextUnderIcon
            font.pointSize: 12
            font.capitalization: Font.MixedCase
            font.weight: Font.Normal
        }
        TabButton {
            height: 56
            anchors.top: parent.top
            text: qsTr("History")
            icon.source: "qrc:/icons/chart-line.svg"
            display: AbstractButton.TextUnderIcon
            font.pointSize: 12
            font.capitalization: Font.MixedCase
            font.weight: Font.Normal
        }
        TabButton {
            height: 56
            anchors.bottom: parent.bottom
            text: qsTr("Settings")
            icon.source: "qrc:/icons/cog-outline.svg"
            icon.height: 24
            display: AbstractButton.TextUnderIcon
            font.pointSize: 12
            font.capitalization: Font.MixedCase
            font.weight: Font.Normal
        }
    }

    StackLayout {
        width: parent.width
        currentIndex: bar.currentIndex
        LivePage {
            id: homeTab
        }
    }
}
