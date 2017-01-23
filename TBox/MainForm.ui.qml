import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2
import cMainTree 1.0
import MainSetting 1.0
import QtQml.Models 2.2
Item {
    id: root
    anchors.fill: parent
    function runNext() {
        theModel.RunNext();
    }
    function writeLog(msg) {
        consoleText.text=consoleText.text+msg+"\n";
    }
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
                            onClicked: mainsetting.show()
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
                    MainTree {
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
                        ColumnLayout {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            ScrollView {
                                Layout.minimumHeight: 200
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                TextEdit {
                                    id: jsCodeEdit
                                    textFormat: Text.PlainText
                                    renderType: Text.NativeRendering
                                    selectByMouse: true
                                    font.pixelSize: 12
                                }
                            }
                            RowLayout {
                                height: 30
                                Layout.alignment: Qt.AlignRight
                                Layout.fillWidth: true
                                Button {
                                    id: saveJS
                                    text: qsTr("Save")
                                    onClicked: theModel.setJS(jsCodeEdit.text);
                                }

                            }
                        }
                        Rectangle {
                            id: consoleLog
                            height: 200
                            Layout.fillWidth: true
                            color: "#f6f6f6"
                            ScrollView {
                                anchors.fill: parent
                                TextEdit {
                                    id: consoleText
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    selectByMouse: true
                                    font.pixelSize: 12
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    Setting {
        id:settingFile
    }
    Window {
        id:mainsetting
        width: 300
        height: 200
        ColumnLayout {
            id: columnLayout1
            anchors.fill: parent
            RowLayout {
                id: rowLayout1
                width: 100
                height: 100
                clip: false
                spacing: 10
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                Layout.fillHeight: true
                Layout.fillWidth: true
                Text {
                    id: text1
                    text: qsTr("Root directory")
                    font.pixelSize: 12
                }
                Rectangle {
                    id: rootDirInput
                    width: 82
                    height: 22
                    border.color: "lightgray"
                    border.width: 1
                    Layout.fillWidth: true
                    TextInput {
                        id: rootDir
                        verticalAlignment: TextInput.AlignVCenter
                        selectByMouse: true
                        anchors.fill: parent
                        smooth: true
                        text: {
                            var dir=settingFile.getRootDir();
                            theModel.Load(dir);
                            return dir;
                        }
                        layer.enabled: true
                        font.pixelSize: 12
                        onFocusChanged: {
                                    if(focus){
                                        rootDirInput.border.color = "#569ffd"
                                    }else{
                                        rootDirInput.border.color = "lightgray"
                                    }
                                }
                    }
                }
            }
            RowLayout {
                id: rowLayout2
                width: 100
                height: 100
                Layout.preferredWidth: -1
                Layout.alignment: Qt.AlignRight | Qt.AlignBottom
                Layout.fillHeight: false
                Layout.maximumHeight: 65535
                Layout.rowSpan: 1
                Layout.fillWidth: true

                Button {
                    id: saveSetting
                    text: qsTr("Save")
                    onClicked: {
                        theModel.Load(rootDir.text);
                        settingFile.setRootDir(rootDir.text);
                        mainsetting.close();
                    }
                }

                Button {
                    id: cancelSetting
                    onClicked: mainsetting.close()
                    text: qsTr("Cancel")
                }
            }
        }
    }
}
