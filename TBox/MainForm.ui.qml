import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
Item {
    anchors.fill: parent
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
                            onClicked: function () {
                                textEdit1.text=qsTr(trssdvfsd.ParseFolder("D:/Projects/trs/TBox/Tests"));
                            }
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
                        TextEdit {
                            id: textEdit1
                            text: qsTr("Text Edit")
                            Layout.minimumHeight: 200
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            font.pixelSize: 12
                        }
                        Rectangle {
                            id: consoleLog
                            height: 200
                            Layout.fillWidth: true
                            color: "lightgray"
                            Text {
                                text: "consoleLog"
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.fill: parent
                            }
                        }
                    }
                }
            }
        }
    }
}
