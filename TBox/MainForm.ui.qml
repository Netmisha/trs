import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2
import cMainTree 1.0
import MainSetting 1.0
import QtQml.Models 2.2
import QtQuick.Controls.Styles 1.0
import QtQuick.Controls.Private 1.0
import QtQuick.Dialogs 1.2
import FileSave 1.0
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
                        ComboBox {
                            id: runTags
                            width: 200
                            activeFocusOnPress: true
                            validator: IntValidator {bottom: 0; top: 10;}
                            onCurrentIndexChanged: theModel.setCurrentTag(currentText);
                        }

                        ToolButton {
                            id: startButton
                            onClicked: {
                                consoleText.text="";
                                theModel.Run();
                            }
                            iconSource: "icons/icons/Run.png"
                        }
                        ToolButton {
                            id: stopButton
                            iconSource: "icons/icons/Stop.png"
                            onClicked: theModel.Stop();
                        }
                        ToolButton {
                            id: reportsButton
                            iconSource: "icons/icons/report.png"
                        }
                        ToolButton {
                            id: settingButton
                            onClicked: mainsetting.show();
                            iconSource: "icons/icons/Settings.png"
                        }
                        ToolButton {
                            id: saveJS
                            onClicked: theModel.FindJSFile(jsCodeEdit.text);
                            iconSource: "icons/icons/jssave.png"
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
                              onClicked: jsCodeEdit.text = theModel.FindTest(styleData.index)
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
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                textFormat: Text.PlainText
                                renderType: Text.NativeRendering
                                selectByMouse: true
                                font.pixelSize: 12
                            }
                        }
                        Rectangle {
                            id: consoleRect
                            height: 10
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            ColumnLayout {
                                anchors.fill: parent
                                Rectangle {
                                    id: consoleLog
                                    visible: false;
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                    color: "#f6f6f6"
                                    ColumnLayout {
                                        anchors.fill: parent
                                        ToolBar {
                                            Layout.fillWidth: true
                                            RowLayout {
                                                id: consoleLayout
                                                spacing: 5
                                                anchors.fill: parent
                                                Item { Layout.fillWidth: true }
                                                ToolButton {
                                                    id: consoleSave
                                                    onClicked: {
                                                        saveFile.open();
                                                    }
                                                    iconSource: "icons/icons/jssave.png"
                                                }
                                                ToolButton {
                                                    id: consoleClear
                                                    iconSource: "icons/icons/clear.png"
                                                    onClicked: consoleText.text="";
                                                }
                                                ToolButton {
                                                    id: consoleHide
                                                    iconSource: "icons/icons/hide.png"
                                                    onClicked:{consoleLog.visible=false; consoleUp.visible=true; consoleRect.height=10;}
                                                }
                                            }
                                        }
                                        ScrollView {
                                            Layout.fillWidth: true
                                            Layout.fillHeight: true
                                            TextEdit {
                                                id: consoleText
                                                anchors.horizontalCenter: parent.horizontalCenter
                                                selectByMouse: true
                                                font.pixelSize: 12
                                            }
                                        }
                                    }
                                }
                                Rectangle {
                                    id: consoleUp
                                    visible: true
                                    height: 10;
                                    Layout.fillWidth: true
                                    color: "lightgray"
                                    Text {
                                        text: qsTr("^")
                                        anchors.fill: parent
                                        horizontalAlignment: Text.AlignHCenter
                                    }
                                    MouseArea {
                                        anchors.fill: parent
                                        onClicked: {consoleLog.visible=true; consoleUp.visible=false;consoleRect.height=200;}
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    FileSaveDialog {
            id: saveFile
            title: "Save file"
            filename: "log.txt"
            nameFilters: ["Text file (*.txt)", "All files (*)"]

            onAccepted: {
                var request = new XMLHttpRequest();
                request.open("PUT", saveFile.fileUrl, false);
                request.send(consoleText.text);
                return request.status;
            }
            onRejected: outputSaveFile.text = "File selected: –"
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
                            runTags.model=theModel.GetTags();
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
