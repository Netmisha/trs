import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Layouts 1.3
import QtWebEngine 1.2

Item {
    width: 640
    height: 480
    ColumnLayout{
        anchors.fill: parent
        spacing: 2
        Rectangle{
            id: mainToolBar
            height: 33
            Layout.fillWidth: true
            ToolBar {
                    id: navigationBar
                    x: 0
                    y: 0
                    Layout.fillHeight: true
                    Rectangle {
                        RowLayout {
                            id: layout
                            spacing: 5
                            anchors.fill: parent;
                            ToolButton {
                                id: startButton
                                iconSource: "icons/icons/Run.png"
                            }
                            ToolButton {
                                id: stopButton
                                iconSource: "icons/icons/Stop.png"
                            }
                            ToolButton {
                                id: reportsButton
                                iconSource: "icons/icons/Edit.png"
                            }
                            ToolButton {
                                id: settingButton
                                iconSource: "icons/icons/Settings.png"
                            }
                        }
                    }
                }
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            SplitView {
                anchors.fill: parent
                orientation: Qt.Horizontal
                Rectangle {
                    id: mainTree
                    width: 200
                    Layout.maximumWidth: 400
                    color: "lightblue"
                    Text {
                        text: "mainTree"
                        anchors.centerIn: parent
                    }
                }
                Rectangle {
                    id: centerItem
                    Layout.minimumWidth: 200
                    Layout.fillWidth: true
                    SplitView {
                        anchors.fill: parent
                        orientation: Qt.Vertical
                        Rectangle {
                            id: pageView
                            Layout.minimumHeight: 200
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            WebEngineView {
                                    anchors.fill: parent
                                    url: "http://www.qt.io"
                                }
                        }
                        Rectangle {
                            id: consoleLog
                            height: 200
                            Layout.fillWidth: true
                            color: "lightgreen"
                            Text {
                                text: "consoleLog"
                                anchors.centerIn: parent
                            }
                        }
                    }
                }
            }
        }
    }
}
