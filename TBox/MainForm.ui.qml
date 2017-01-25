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
    Item {
        id: showMenu
        function menuForSuite() {
            testToolBar.visible=true;
            newTest.visible=true;
            newSuite.visible=true;
            testEdit.visible=false;
        }
        function menuForTest() {
            testToolBar.visible=true;
            newTest.visible=false;
            newSuite.visible=false;
            testEdit.visible=true;
        }
        function hideAll() {
            testToolBar.visible=false;
        }
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
                              onClicked: {
                                  jsCodeEdit.text = theModel.FindTest(styleData.index);
                                  if(theModel.GetType()=="test") {
                                      showMenu.menuForTest();
                                  }
                                  else if(theModel.GetType()=="suite") {
                                      showMenu.menuForSuite();
                                  }
                                  else {
                                    showMenu.hideAll();
                                  }
                                  testName.text=theModel.Get("name");
                                  if(theModel.Get("disable")=="false"){
                                      testStatus.iconSource="icons/icons/turnon.png";
                                  }
                                  else {
                                      testStatus.iconSource="icons/icons/turnoff.png";
                                  }
                              }
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
                            Layout.minimumHeight: 200
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            Rectangle {
                                height: 30
                                Layout.fillWidth: true
                                ColumnLayout {
                                    anchors.fill: parent
                                    ToolBar {
                                        id : testToolBar
                                        visible: false;
                                        Layout.fillWidth: true
                                        RowLayout {
                                            spacing: 5
                                            anchors.fill: parent
                                            Text {
                                                id:testName
                                            }
                                            ToolButton {
                                                id: testStatus
                                                onClicked: {
                                                    if(theModel.Get("disable")=="true"){
                                                        testStatus.iconSource="icons/icons/turnon.png";
                                                        theModel.Set("disable","false");
                                                    }
                                                    else {
                                                        testStatus.iconSource="icons/icons/turnoff.png";
                                                        theModel.Set("disable","true");
                                                    }
                                                }
                                                iconSource: "icons/icons/turnon.png"
                                            }
                                            ToolButton {
                                                id: testRun
                                                iconSource: "icons/icons/Run.png"
                                                onClicked: theModel.RunOne()
                                            }
                                            Item { Layout.fillWidth: true }
                                            ToolButton {
                                                id: newTest
                                                iconSource: "icons/icons/newtest.png"
                                                onClicked: {
                                                    theModel.SetNewType("test");
                                                    addNewItem.show();
                                                }
                                            }
                                            ToolButton {
                                                id: newSuite
                                                iconSource: "icons/icons/newsuite.png"
                                                onClicked: {
                                                    theModel.SetNewType("suite");
                                                    addNewItem.show();
                                                }
                                            }
                                            ToolButton {
                                                id: testDelete
                                                iconSource: "icons/icons/testdelete.png"
                                                onClicked:{}
                                            }
                                            ToolButton {
                                                id: testEdit
                                                iconSource: "icons/icons/testedit.png"
                                                onClicked:{}
                                            }
                                            ToolButton {
                                                id: saveJS
                                                visible: false;
                                                onClicked: theModel.FindJSFile(jsCodeEdit.text);
                                                iconSource: "icons/icons/jssave.png"
                                            }
                                            ToolButton {
                                                id: testSetting
                                                iconSource: "icons/icons/testsetting.png"
                                                onClicked:{}
                                            }
                                        }
                                    }
                                }
                            }
                            ScrollView {
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
                        }
                        Rectangle {
                            id: consoleRect
                            Layout.minimumHeight: 10
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
                                                    onClicked:{
                                                        consoleLog.visible=false;
                                                        consoleUp.visible=true;
                                                        consoleRect.height=10;
                                                    }
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
                                        onClicked: {
                                            consoleLog.visible=true;
                                            consoleUp.visible=false;
                                            consoleRect.height=200;
                                        }
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
                        anchors.rightMargin: 3
                        anchors.leftMargin: 3
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
    Window {
        id: addNewItem
        width: 320
        height: 100
        ColumnLayout {
            anchors.topMargin: 5
            anchors.bottomMargin: 10
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            anchors.fill: parent
            RowLayout {
                width: 100
                height: 100
                spacing: 10

                Text {
                    text: qsTr("Name")
                    font.pixelSize: 12
                }
                Rectangle {
                    id: newNameBorder
                    width: 82
                    height: 22
                    border.color: "lightgray"
                    border.width: 1
                    Layout.fillWidth: true
                    TextInput {
                        id: newName
                        verticalAlignment: TextInput.AlignVCenter
                        selectByMouse: true
                        anchors.fill: parent
                        anchors.rightMargin: 3
                        anchors.leftMargin: 3
                        smooth: true
                        layer.enabled: true
                        font.pixelSize: 12
                        onFocusChanged: {
                                    if(focus){
                                        newNameBorder.border.color = "#569ffd"
                                    }else{
                                        newNameBorder.border.color = "lightgray"
                                    }
                                }
                    }
                }
            }
            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
            RowLayout {
                width: 100
                height: 100
                Button {
                    id: newCancel
                    text: qsTr("Cancel")
                    onClicked: {
                        addNewItem.close();
                        newName.text="";
                    }
                }
                Button {
                    id: newOk
                    text: qsTr("Ok")
                    onClicked: {
                        if(newName.text!="") {
                            var res=theModel.AddNew(newName.text);
                            if(res!="") {
                                messageDialog.text=res;
                                messageDialog.open();
                            }
                            theModel.Load(settingFile.getRootDir());
                            addNewItem.close();
                            newName.text="";
                        }
                        else {
                            //show error
                        }
                    }
                }
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            }
        }
    }
    MessageDialog {
        id: messageDialog
        title: "Warning"
        onAccepted: {
            Qt.quit()
        }
    }
}
