import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import ca.models 1.0
import QtQml.Models 2.2
Item {
    id: root
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
                            onClicked: theModel.Run();
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
                            onClicked: theModel.Reload()
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
                    id : ttree;
                    width: 200
                    Layout.maximumWidth: 400
                    MyTreeModel {
                        id: theModel
                    }
                    TreeView {
                       id: mainTree
                       anchors.fill: parent
                       model: theModel
                       itemDelegate: Rectangle {
                          id : recid
                          color: ( styleData.row % 2 == 0 ) ? "white" : "#f6f6f6"
                          height: 20
                          Text {
                              anchors.verticalCenter: parent.verticalCenter
                              text: styleData.value
                          }
                          MouseArea{
                              anchors.fill: parent
                              onClicked: jsCodeEdit.text = theModel.getJS(styleData.index)
                          }
                       }
                       TableViewColumn {
                           role: "name_role"
                           title: "Tests"
                       }

                   }
                }
                Rectangle {
                    id: centerItem
                    Layout.minimumWidth: 200
                    Layout.fillWidth: true
                    SplitView {
                        anchors.fill: parent
                        orientation: Qt.Vertical
                        ScrollView {
                            Layout.minimumHeight: 200
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            TextEdit {
                                id: jsCodeEdit
                                textFormat: Text.PlainText
                                renderType: Text.NativeRendering
                                selectByMouse: true
                                text: qsTr("Text Edit")
                                font.pixelSize: 12
                            }
                        }
                        Rectangle {
                            id: consoleLog
                            height: 200
                            Layout.fillWidth: true
                            color: "lightgray"
                            Text {
                                id: consoleText
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
