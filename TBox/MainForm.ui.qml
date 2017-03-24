import QtQuick 2.4
import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2
import cMainTree 1.0
import MainSetting 1.0
import QtQml.Models 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Private 1.0
import QtQuick.Dialogs 1.2
import FileSave 1.0
import QtWebKit 3.0
import Highlighter 1.0
Item {
    property variant win;
    property  variant list_;
    property  variant db_list;

    id: root
    anchors.fill: parent
    Action {
        id: saveJSAction
        shortcut: "Ctrl+S"
        onTriggered: {
            if(saveJS.visible){
                theModel.FindJSFile(jsCodeEdit.text);
                testStatus.visible=true;
                testRun.visible=true;
                testDelete.visible=true;
                testSetting.visible=true;
                jsCodeEdit.readOnly=true;
                jsCodeRect.color="#f6f6f6";
                testEdit.visible=true;
                saveJS.visible=false;
                cancelJS.visible=false;
                mainTree.enabled=true;
                navigationBar.enabled=true;
                consoleRect.enabled=true;
                fontComboBox.visible=false;
                fontComboBox.currentIndex=4;
            }
        }
    }
    Action {
        id: editJSAction
        shortcut: "Ctrl+E"
        onTriggered: {
            if(testEdit.visible && testEdit.enabled){
                testStatus.visible=false;
                testRun.visible=false;
                testDelete.visible=false;
                testSetting.visible=false;
                testEdit.visible=false;
                jsCodeEdit.readOnly=false;
                jsCodeRect.color="white";
                saveJS.visible=true;
                cancelJS.visible=true;
                mainTree.enabled=false;
                consoleRect.enabled=false;
                navigationBar.enabled=false;
                fontComboBox.visible=true;
            }
        }
    }
    Action {
        id: runJSAction
        shortcut: "Ctrl+R"
        onTriggered: {
            stopTestButton.visible=true;
            theModel.RunOne();
            testRun.visible=false;
            startButton.enabled=false;
            refreshTree.enabled=false;
            runTags.enabled=false;
            reportsButton.enabled=false;
            settingButton.enabled=false;
            testStatus.enabled=false;
            openFolder.enabled=false;
            externalEditor.enabled=false;
            testDelete.enabled=false;
            testEdit.enabled=false;
            testSetting.enabled=false;
        }
    }
    Action {
        id: runAllAction
        shortcut: "Ctrl+Shift+R"
        onTriggered: {
            if(theModel.Run()) {
                stopAllTestsButton.visible=true;
                consoleText.text="";
                startButton.visible=false;
                testRun.enabled=false;
                subToolBar.enabled=false;
                refreshTree.enabled=false;
                runTags.enabled=false;
                reportsButton.enabled=false;
                settingButton.enabled=false;

            }
        }
    }
    Action {
        id: disableAction
        shortcut: "Ctrl+D"
        onTriggered: {
            if(testStatus.enabled==false) {
                return;
            }
            if(theModel.Get("disable")=="true"){
                testStatus.iconSource="icons/icons/turnon.png";
                theModel.Set("disable","false");
            }
            else if(theModel.Get("disable")=="false"){
                testStatus.iconSource="icons/icons/turnoff.png";
                theModel.Set("disable","true");
            }
        }
    }
    Action {
        id: refreshTreeAction
        shortcut: "F5"
        onTriggered: {
            if(navigationBar.enabled) {
                var res=theModel.Load(settingFile.getRootDir());
                runTags.model=theModel.GetTags();
                theModel.setCurrentTag(runTags.currentText);
                if(res!="") {
                    messageDialog.text=res;
                    messageDialog.open()
                    return;
                }
            }
        }
    }
    Action {
        id: stopTestAction
        shortcut: "F12"
        onTriggered: {
            if(stopTestButton.visible || stopAllTestsButton.visible) {
                theModel.Terminate();
                setStopDisable();
            }
        }
    }
    function checkRootDir() {
        if(rootDir.text==""){
            selectFolderDialog.setFromSetting(false);
            selectFolderDialog.show();
        }
    }
    function setStopDisable(){
        stopAllTestsButton.visible=false;
        startButton.visible=true;
        stopTestButton.visible=false;
        testRun.visible=true;
        startButton.enabled=true;
        testRun.enabled=true;
        navigationBar.enabled=true;
        testStatus.enabled=true;
        openFolder.enabled=true;
        externalEditor.enabled=true;
        testDelete.enabled=true;
        testEdit.enabled=true;
        testSetting.enabled=true;
        subToolBar.enabled=true;
        refreshTree.enabled=true;
        runTags.enabled=true;
        reportsButton.enabled=true;
        settingButton.enabled=true;
    }
    function setSelectedFolder(folder) {
        if(selectFolderDialog.isFromSetting()){
            rootDir.text=folder;
        }
        else {
            rootDir.text=folder;
            theModel.setRootDir(rootDir.text);
            settingFile.setRootDir(rootDir.text);
            if(theModel.IsFolderEmpty(folder)) {
                showMenu.menuForSuite();
				addSuiteLayout.enabled=true;
                centerRect.visible=false;
                addSuiteLayout.visible=true;
                testName.text="New Suite";
                textEditSName.text="Main suite";
                testRun.visible=false;
                newTest.visible=false;
                newSuite.visible=false;
                testDelete.visible=false;
                testSetting.visible=false;
                restoreNew.visible=false;
                saveNew.visible=false;
                createNew.visible=true;
                mainTree.enabled=false;
                consoleRect.enabled=false;
                navigationBar.enabled=false;
            }
            else {
                var res=theModel.Load(folder);
                runTags.model=theModel.GetTags();
                theModel.setCurrentTag(runTags.currentText);
                if(res!="") {
                    messageDialog.text=res;
                    messageDialog.open()
                    return;
                }
            }
        }
    }
    function writeLog(msg) {

        consoleText.text=consoleText.text+msg+"\n";
    }
    function showItem (index) {
        theModel.setCurrentItem(index);
        lineRect.visible=false;
        lineRect.width=0;
        testName.text=theModel.Get("name");
        if(theModel.Get("disable")=="false"){
            testStatus.iconSource="icons/icons/turnon.png";
        }
        else {
            testStatus.iconSource="icons/icons/turnoff.png";
        }
        if(theModel.GetType(index)=="test") {
            showMenu.menuForTest();
            jsCodeEdit.text = theModel.FindTest(index);
            lineRect.visible=true;
            lineRect.width=Math.max(jsCodeEdit.lineCount.toString().length, (lineColumn.height/lineColumn.rowHeight).toFixed(0).toString().length)*jsCodeEdit.font.pixelSize;
        }
        else if(theModel.GetType(index)=="suite") {
            showMenu.menuForSuite();
        }
        else {
          showMenu.hideAll();
        }
    }
    function selectItem (idx) {
         mainTree.selection.setCurrentIndex(idx, ItemSelectionModel.ClearAndSelect);
         root.showItem(idx);
    }
	function startRun() {
        if(theModel.Run()) {
            stopAllTestsButton.visible=true;
            consoleText.text="";
            startButton.visible=false;
            testRun.enabled=false;
        }
    }
    Item {
        id: showMenu
        function menuForSuite() {
            testToolBar.visible=true;
            subToolBar.visible=true;
            newTest.visible=true;
            newSuite.visible=true;
            centerRect.visible=false;
            testEdit.visible=false;
            externalEditor.visible=false;
            textEditSName.text=theModel.Get("name");
            textEditSDiscr.text=theModel.Get("description");
            textEditSRepeat.text=theModel.Get("repeat");
            addSuiteLayout.visible=true;
            addSuiteLayout.enabled=false;
        }
        function menuForTest() {
            testToolBar.visible=true;
            subToolBar.visible=true;
            newTest.visible=false;
            newSuite.visible=false;
            centerRect.visible=true;
            testEdit.visible=true;
            externalEditor.visible=true;
            addSuiteLayout.visible=false;
            addSuiteLayout.enabled=true;
            addTestLayout.visible=false;
        }
        function hideAll() {
            testToolBar.visible=false;
        }
    }
     ColumnLayout{
        anchors.fill: parent
        spacing: 0
        ToolBar {
            id: navigationBar
            Layout.fillWidth: true
            RowLayout {
                id: layout
                spacing: 5
                anchors.fill: parent;
                ToolButton {
                    id: refreshTree
                    action: refreshTreeAction
                    iconSource: "icons/icons/refresh.png"
                }
                Text {
                    text: "Tags: "
                }
                ComboBox {
                    id: runTags
                    width: 200
                    activeFocusOnPress: true
                    onCurrentIndexChanged: theModel.setCurrentTag(runTags.currentText);
                    model: []
                }
                ToolButton {
                    id: startButton
                    action: runAllAction
                    iconSource: "icons/icons/Run.png"

                }
                ToolButton {
                    id: stopAllTestsButton
                    visible: false
                    iconSource: "icons/icons/Stop.png"
                    action: stopTestAction
                }
                ToolButton {
                    id: reportsButton
                    iconSource: "icons/icons/report.png"
                    onClicked:{
                        DD.defaultTableValue(qsTr(new Date().toJSON().slice(0,10).replace(/-/g,'/')),qsTr(new Date().toJSON().slice(0,10).replace(/-/g,'/')))
                        report_window_.show();}
                }
                ToolButton {
                    id: settingButton
                    onClicked: mainsetting.show();
                    iconSource: "icons/icons/Settings.png"
                }
                Item {
                    Layout.fillWidth: true;
                }
                ToolButton {
                    id: inspectorButton
                    onClicked: theModel.showInspector();
                    iconSource: "icons/icons/inspector.png"
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
                       TableViewColumn {
                           role: "name_role"
                           title: "Tests"
                       }
                       model: theModel
                       selectionMode: SelectionMode.SingleSelection
                       selection: ItemSelectionModel {
                            model: mainTree.model
                       }
                       itemDelegate: Rectangle {
                          id : recid
                          color: "transparent"
                          height: 20
                          Rectangle {
                              color: "transparent"
                              height: 20
                              width: 20
                              Image {
                                  height: 15
                                  width: 15
                                  verticalAlignment: Image.AlignVCenter
                                  horizontalAlignment: Image.AlignHCenter
                                  source: {
                                      if(theModel.GetType(styleData.index)=="test") {
                                          return "icons/icons/test.png"
                                      }
                                      else {
                                          return "icons/icons/suite.png"
                                      }
                                  }
                              }
                          }
                          Text {
                              x:20
                              anchors.verticalCenter: parent.verticalCenter
                              text: styleData.value
                          }
                       }
                       rowDelegate: Rectangle {
                           color: styleData.selected?"#3399ff":"transparent"
                           height: 20
                       }
                       onClicked: {
                           fontComboBox.currentIndex=4;
                           root.showItem(index);
                       }
                       onDoubleClicked: {
                           fontComboBox.currentIndex=4;
                           if(mainTree.isExpanded(index)) {
                                mainTree.collapse(index);
                           }
                           else {
                                mainTree.expand(index);
                           }
                           root.showItem(index);
                       }
                   }
                }
                Rectangle {
                    id: centerItem
                    Layout.minimumWidth: 200
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    SplitView {
                        anchors.fill: parent
                        orientation: Qt.Vertical
                        ColumnLayout {
                            id: centerColumn
                            Layout.minimumHeight: 200
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            spacing: 0
                            Rectangle {
                                id: subToolBar
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
                                            ComboBox{
                                                id: fontComboBox
                                                width: 50
                                                currentIndex: 4
                                                visible: false
                                                model: ["8","9","10","11","12","14","16","18","20","22","24","26","28","36","48"]
                                                onCurrentIndexChanged: {
                                                    jsCodeEdit.font.pixelSize=parseInt(fontComboBox.currentText);
                                                    highlight1.setFontSize(jsCodeEdit.font.pixelSize);
                                                    lineColumn.rowHeight=jsCodeEdit.font.pixelSize+lineColumn.spaceSizePX[fontComboBox.currentIndex];
                                                    lineRect.width=Math.max(jsCodeEdit.lineCount.toString().length, (lineColumn.height/lineColumn.rowHeight).toFixed(0).toString().length)*jsCodeEdit.font.pixelSize;
                                                }
                                            }
                                            ToolButton {
                                                id: testStatus
                                                action: disableAction
                                                iconSource: "icons/icons/turnon.png"
                                            }
                                            ToolButton {
                                                id: testRun
                                                iconSource: "icons/icons/Run.png"
                                                action: runJSAction
                                            }
                                            ToolButton {
                                                id: stopTestButton
                                                visible: false
                                                iconSource: "icons/icons/Stop.png"
                                                action: stopTestAction
                                            }
                                            ToolButton {
                                                id: openFolder
                                                iconSource: "icons/icons/openfolder.png"
                                                onClicked: theModel.openFolder()
                                            }
                                            ToolButton {
                                                id: externalEditor
                                                iconSource: "icons/icons/editor.png"
                                                onClicked: theModel.OpenInEditor(settingFile.getEditor());
                                                visible: false;
                                                enabled: false;
                                            }
                                            Item { Layout.fillWidth: true }
                                            ToolButton {
                                                id: newTest
                                                iconSource: "icons/icons/newtest.png"
                                                onClicked: {
                                                    centerRect.visible=false;
                                                    addTestLayout.visible=true;
                                                    addSuiteLayout.visible=false;
                                                    testName.text="New Test";
                                                    textEditTName.text="";
                                                    textEditTDiscr.text="";
                                                    textEditTTag.text="";
                                                    textEditTExe.text="";
                                                    textEditTRepeat.text="1"
                                                    testStatus.iconSource="icons/icons/turnon.png";
                                                    testImportant.checked=false;
                                                    testRun.visible=false;
                                                    newTest.visible=false;
                                                    newSuite.visible=false;
                                                    testDelete.visible=false;
                                                    testSetting.visible=false;
                                                    restoreNew.visible=true;
                                                    saveNew.visible=true;
                                                    mainTree.enabled=false;
                                                    consoleRect.enabled=false;
                                                    navigationBar.enabled=false;
                                                }
                                            }
                                            ToolButton {
                                                id: newSuite
                                                iconSource: "icons/icons/newsuite.png"
                                                onClicked: {
                                                    centerRect.visible=false;
                                                    testName.text="New Suite";
                                                    textEditSName.text="";
                                                    textEditSDiscr.text="";
                                                    textEditSRepeat.text="1";
                                                    testRun.visible=false;
                                                    newTest.visible=false;
                                                    newSuite.visible=false;
                                                    testDelete.visible=false;
                                                    testSetting.visible=false;
                                                    restoreNew.visible=true;
                                                    saveNew.visible=true;
                                                    mainTree.enabled=false;
                                                    consoleRect.enabled=false;
                                                    navigationBar.enabled=false;
                                                    addSuiteLayout.enabled=true;
                                                }
                                            }
                                            ToolButton {
                                                id: testDelete
                                                iconSource: "icons/icons/testdelete.png"
                                                onClicked: {
                                                    deleteConfirm.open();
                                                }
                                            }
                                            ToolButton {
                                                id: testEdit
                                                iconSource: "icons/icons/testedit.png"
                                                visible: false
                                                action: editJSAction
                                            }
                                            ToolButton {
                                                id: cancelJS
                                                visible: false;
                                                onClicked: {
                                                    jsCodeEdit.text = theModel.FindTest(theModel.getCurrentIndex());
                                                    testStatus.visible=true;
                                                    testRun.visible=true;
                                                    testDelete.visible=true;
                                                    testSetting.visible=true;
                                                    jsCodeEdit.readOnly=true;
                                                    testEdit.visible=true;
                                                    externalEditor.visible=true;
                                                    saveJS.visible=false;
                                                    jsCodeRect.color="#f6f6f6";
                                                    cancelJS.visible=false;
                                                    mainTree.enabled=true;
                                                    consoleRect.enabled=true;
                                                    navigationBar.enabled=true;
                                                    fontComboBox.visible=false;
                                                    fontComboBox.currentIndex=4;

                                                }
                                                iconSource: "icons/icons/restore.png"
                                            }
                                            ToolButton {
                                                id: saveJS
                                                visible: false;
                                                action: saveJSAction
                                                iconSource: "icons/icons/jssave.png"
                                            }
                                            ToolButton {
                                                id: testSetting
                                                iconSource: "icons/icons/testsetting.png"
                                                onClicked:{
                                                    if(theModel.GetType(theModel.getCurrentIndex()) == "test") {
                                                        textEditTName.text=theModel.Get("name");
                                                        textEditTDiscr.text=theModel.Get("description");
                                                        textEditTTag.text=theModel.Get("tag");
                                                        textEditTExe.text=theModel.Get("execution");
                                                        textEditTRepeat.text=theModel.Get("repeat");
                                                        if(theModel.Get("disable")=="false"){
                                                            testStatus.iconSource="icons/icons/turnon.png";
                                                        }
                                                        else if(theModel.Get("disable")=="true"){
                                                            testStatus.iconSource="icons/icons/turnoff.png";
                                                        }
                                                        if(theModel.Get("important")=="true"){
                                                            testImportant.checked=true;
                                                        }
                                                        else {
                                                            testImportant.checked=false;
                                                        }
                                                        centerRect.visible=false;
                                                        addTestLayout.visible=true;
                                                        testRun.visible=false;
                                                        newTest.visible=false;
                                                        newSuite.visible=false;
                                                        testDelete.visible=false;
                                                        testSetting.visible=false;
                                                        restoreNew.visible=true;
                                                        saveNew.visible=true;
                                                        testEdit.visible=false;
                                                        externalEditor.visible=false;
                                                        mainTree.enabled=false;
                                                        consoleRect.enabled=false;
                                                        navigationBar.enabled=false;
                                                    }
                                                    else if(theModel.GetType(theModel.getCurrentIndex())=="suite") {
                                                        textEditSName.text=theModel.Get("name");
                                                        textEditSDiscr.text=theModel.Get("description");
                                                        textEditSRepeat.text=theModel.Get("repeat");
                                                        centerRect.visible=false;
                                                        addSuiteLayout.visible=true;
                                                        testRun.visible=false;
                                                        newTest.visible=false;
                                                        newSuite.visible=false;
                                                        testDelete.visible=false;
                                                        testSetting.visible=false;
                                                        restoreNew.visible=true;
                                                        saveNew.visible=true;
                                                        mainTree.enabled=false;
                                                        consoleRect.enabled=false;
                                                        navigationBar.enabled=false;
                                                        addSuiteLayout.enabled=true;
                                                        if(theModel.Get("disable")=="false"){
                                                            testStatus.iconSource="icons/icons/turnon.png";
                                                        }
                                                        else if(theModel.Get("disable")=="true"){
                                                            testStatus.iconSource="icons/icons/turnoff.png";
                                                        }
                                                    }
                                                }
                                            }
                                            ToolButton {
                                                id: restoreNew
                                                visible: false;
                                                onClicked: {
                                                    if(testName.text== "New Test") {
                                                        textEditTName.text="";
                                                        textEditTDiscr.text="";
                                                        textEditTExe.text="";
                                                        textEditTTag.text="";
                                                        textEditTRepeat.text="1";
                                                        addTestLayout.visible=false;
                                                        addSuiteLayout.visible=true;
                                                        addSuiteLayout.enabled=false;
                                                        newTest.visible=true;
                                                        newSuite.visible=true;
                                                    }
                                                    else if(testName.text== "New Suite") {
                                                        addSuiteLayout.enabled=false;
                                                        showMenu.menuForSuite();
                                                        newTest.visible=true;
                                                        newSuite.visible=true;
                                                    }
                                                    else {
                                                        if(theModel.GetType(theModel.getCurrentIndex())=="test") {
                                                            textEditTName.text="";
                                                            textEditTDiscr.text="";
                                                            textEditTExe.text="";
                                                            textEditTTag.text="";
                                                            textEditTRepeat.text="1";
                                                            addTestLayout.visible=false;
                                                            centerRect.visible=true;
                                                            testEdit.visible=true;
                                                            externalEditor.visible=true;
                                                        }
                                                        else {
                                                            addSuiteLayout.enabled=false;
                                                            showMenu.menuForSuite();
                                                            newTest.visible=true;
                                                            newSuite.visible=true;
                                                        }
                                                    }
                                                    testName.text=theModel.Get("name");
                                                    testRun.visible=true;
                                                    testDelete.visible=true;
                                                    testSetting.visible=true;
                                                    restoreNew.visible=false;
                                                    saveNew.visible=false;
                                                    mainTree.enabled=true;
                                                    consoleRect.enabled=true;
                                                    navigationBar.enabled=true;
                                                }
                                                iconSource: "icons/icons/restore.png"
                                            }
                                            ToolButton {
                                                id: saveNew
                                                visible: false;
                                                iconSource: "icons/icons/jssave.png"
                                                onClicked: {
                                                    if(testName.text== "New Test") {
                                                        var dis=testStatus.iconSource.toString().indexOf("turnon")!=-1?"false":"true";
                                                        var res=theModel.AddNewTest(textEditTName.text,textEditTDiscr.text, textEditTExe.text, textEditTTag.text, textEditTRepeat.text, dis, testImportant.checked.toString());
                                                        if(res!="") {
                                                            messageDialog.text=res;
                                                            messageDialog.open()
                                                            return;
                                                        }
                                                        textEditTName.text="";
                                                        textEditTDiscr.text="";
                                                        textEditTExe.text="";
                                                        textEditTTag.text="";
                                                        textEditTRepeat.text="1";
                                                        addTestLayout.visible=false;
                                                        addSuiteLayout.visible=false;
                                                        addSuiteLayout.enabled=false;
                                                        newTest.visible=true;
                                                        newSuite.visible=true;
                                                        centerRect.visible=true;
                                                        runTags.model=theModel.GetTags();
                                                    }
                                                    else if(testName.text== "New Suite") {
                                                        var dis=testStatus.iconSource.toString().indexOf("turnon")!=-1?"false":"true";
                                                        var res=theModel.AddNewSuite(textEditSName.text,textEditSDiscr.text, textEditSRepeat.text, dis);
                                                        if(res!="") {
                                                            messageDialog.text=res;
                                                            messageDialog.open()
                                                            return;
                                                        }
                                                        addSuiteLayout.enabled=false;
                                                        newTest.visible=true;
                                                        newSuite.visible=true;
                                                    }
                                                    else {
                                                        var dis=testStatus.iconSource.toString().indexOf("turnon")!=-1?"false":"true";
                                                        if(theModel.GetType(theModel.getCurrentIndex())=="test") {
                                                            if(textEditTName.text!="" && textEditTExe.text!="") {
                                                                theModel.Set("name", textEditTName.text);
                                                                theModel.Set("description", textEditTDiscr.text);
                                                                theModel.Set("tag", textEditTTag.text);
                                                                theModel.Set("execution", textEditTExe.text);
                                                                theModel.Set("repeat", textEditTRepeat.text==""?"1":textEditTRepeat.text);
                                                                theModel.Set("disable", dis);
                                                                theModel.Set("important", testImportant.checked.toString());
                                                                addTestLayout.visible=false;
                                                                centerRect.visible=true;
                                                                testEdit.visible=true;
                                                                externalEditor.visible=true;
                                                                centerRect.visible=true;
                                                                runTags.model=theModel.GetTags();
                                                            }
                                                            else {
                                                                messageDialog.text="Fill all fields correctly!";
                                                                messageDialog.open()
                                                                return;
                                                            }
                                                        }
                                                        else {
                                                            if(textEditSName.text!="") {
                                                                theModel.Set("name", textEditSName.text);
                                                                theModel.Set("description", textEditSDiscr.text);
                                                                theModel.Set("repeat", textEditSRepeat.text==""?"1":textEditSRepeat.text);
                                                                theModel.Set("disable", dis);
                                                                newTest.visible=true;
                                                                newSuite.visible=true;
                                                                addSuiteLayout.enabled=false;
                                                            }
                                                            else {
                                                                messageDialog.text="Fill all fields correctly!";
                                                                messageDialog.open()
                                                                return;
                                                            }
                                                        }
                                                    }
                                                    testRun.visible=true;
                                                    testDelete.visible=true;
                                                    testSetting.visible=true;
                                                    restoreNew.visible=false;
                                                    saveNew.visible=false;
                                                    mainTree.enabled=true;
                                                    consoleRect.enabled=true;
                                                    navigationBar.enabled=true;
                                                }
                                            }
                                            ToolButton {
                                                id: createNew
                                                visible: false;
                                                iconSource: "icons/icons/jssave.png"
                                                onClicked: {
                                                    var dis=testStatus.iconSource.toString().indexOf("turnon")!=-1?"false":"true";
                                                    var res=theModel.AddRootSuite(textEditSName.text,textEditSDiscr.text, textEditSRepeat.text, dis);
                                                    if(res!="") {
                                                        messageDialog.text=res;
                                                        messageDialog.open()
                                                        return;
                                                    }
                                                    textEditSName.text="";
                                                    textEditSDiscr.text="";
                                                    textEditSRepeat.text="1";
                                                    addSuiteLayout.visible=false;
                                                    addSuiteLayout.enabled=true;
                                                    newTest.visible=true;
                                                    newSuite.visible=true;
                                                    res=theModel.Load(settingFile.getRootDir());
                                                    runTags.model=theModel.GetTags();
                                                    if(res!="") {
                                                        messageDialog.text=res;
                                                        messageDialog.open()
                                                    }
                                                    centerRect.visible=true;
                                                    testRun.visible=true;
                                                    testDelete.visible=true;
                                                    testSetting.visible=true;
                                                    restoreNew.visible=false;
                                                    saveNew.visible=false;
                                                    mainTree.enabled=true;
                                                    consoleRect.enabled=true;
                                                    navigationBar.enabled=true;
                                                    createNew.visible=false
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            Rectangle {
                                id: centerRect
                                Layout.minimumWidth: 200
                                Layout.minimumHeight: 200
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                color: "transparent"
                                Rectangle {
                                    id: jsCodeRect
                                    y: 3
                                    width: centerRect.width
                                    height: centerRect.height
                                    color: "#f6f6f6"
                                    Rectangle {
                                        id: lineRect
                                        width: 0
                                        visible: false
                                        height: jsCodeRect.height
                                        ScrollView {
                                            id:lineScroll
                                            anchors.fill: parent
                                            width: lineRect.width
                                            horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
                                            verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff
                                            contentItem: Rectangle {
                                                id: lineColumn
                                                property int rowHeight: jsCodeEdit.font.pixelSize+3
                                                property variant spaceSizePX: [0,3,2,3,3,3,2,2,2,2,3,3,3,3,2]
                                                color: "#f2f2f2"
                                                width: lineRect.width
                                                height: lineRect.height
                                                Rectangle {
                                                    height: parent.height
                                                    anchors.right: parent.right
                                                    width: 1
                                                    color: "#ddd"
                                                }
                                                Column {
                                                    y: -jsCodeEdit.flickableItem.contentY + 4
                                                    width: lineRect.width
                                                    Repeater {
                                                        model: Math.max(jsCodeEdit.lineCount + 2, (lineColumn.height/lineColumn.rowHeight) )
                                                        delegate: Text {
                                                            id: text
                                                            color: "#666"
                                                            font: jsCodeEdit.font
                                                            width: lineColumn.width
                                                            horizontalAlignment: Text.AlignHCenter
                                                            verticalAlignment: Text.AlignBottom
                                                            height: lineColumn.rowHeight
                                                            renderType: Text.NativeRendering
                                                            text: index+1
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    Rectangle {
                                        x:lineRect.width
                                        width: jsCodeRect.width-lineRect.width
                                        height: jsCodeRect.height
                                        color: "transparent"
                                        HighL {
                                            id: highlight1
                                        }
                                        TextArea {
                                            id: jsCodeEdit
                                            readOnly: true
                                            selectByMouse: true
                                            font.pixelSize: 12
                                            font.family: "Courier New"
                                            textFormat: Qt.PlainText
                                            anchors.fill: parent
                                            wrapMode: TextEdit.NoWrap
                                            frameVisible: false
                                            backgroundVisible: false
                                            onLineCountChanged: {
                                                lineRect.width=Math.max(jsCodeEdit.lineCount.toString().length, (lineColumn.height/lineColumn.rowHeight).toFixed(0).toString().length)*jsCodeEdit.font.pixelSize;
                                            }
                                            Component.onCompleted: {
                                                highlight1.setQuickDocument(jsCodeEdit.textDocument)
                                            }
                                            Keys.onPressed: {
                                                if (event.key == Qt.Key_Tab) {
                                                    jsCodeEdit.insert(jsCodeEdit.cursorPosition, "\t");
                                                    event.accepted = true;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            Rectangle {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                ColumnLayout {
                                    id: addSuiteLayout
                                    visible:  false
                                    spacing: 10
                                    anchors.rightMargin: 10
                                    anchors.bottomMargin: 10
                                    anchors.leftMargin: 10
                                    anchors.topMargin: 10
                                    anchors.fill: parent
                                    RowLayout {
                                        y: 0
                                        height: 36
                                        anchors.right: parent.right
                                        Text {
                                            width: 60
                                            text: qsTr("Name")
                                            font.pixelSize: 12
                                            verticalAlignment: Text.AlignVCenter
                                        }
                                        Rectangle {
                                            id: nameSRect
                                            Layout.fillWidth: true
                                            Layout.fillHeight: true
                                            border.color: "lightgray"
                                            border.width: 1
                                            TextEdit {
                                                id: textEditSName
                                                text: qsTr("")
                                                anchors.fill: parent
                                                font.pixelSize: 12
                                                Layout.fillWidth: true
                                                anchors.rightMargin: 3
                                                anchors.leftMargin: 3
                                                selectByMouse: true
                                                smooth: true
                                                verticalAlignment: TextInput.AlignVCenter
                                                onFocusChanged: {
                                                            if(focus){
                                                                nameSRect.border.color = "#569ffd"
                                                            }else{
                                                                nameSRect.border.color = "lightgray"
                                                            }
                                                        }
                                            }
                                        }
                                        transformOrigin: Item.Center
                                        anchors.left: parent.left
                                        spacing: 10
                                        anchors.leftMargin: 0
                                        anchors.rightMargin: 0
                                    }
                                    RowLayout {
                                        y: 0
                                        height: 70
                                        Layout.minimumHeight: 68
                                        anchors.right: parent.right
                                        ColumnLayout {
                                            width: 100
                                            height: 100
                                            Layout.minimumHeight: 66
                                            Text {
                                                text: qsTr("Description")
                                                font.pixelSize: 12
                                                verticalAlignment: Text.AlignVCenter
                                            }
                                            Rectangle {
                                                id: descriptionSRect
                                                Layout.fillWidth: true
                                                Layout.fillHeight: true
                                                border.color: "lightgray"
                                                border.width: 1
                                                TextEdit {
                                                    id: textEditSDiscr
                                                    text: qsTr("")
                                                    anchors.fill: parent
                                                    Layout.minimumHeight: 50
                                                    font.pixelSize: 12
                                                    Layout.fillWidth: true
                                                    anchors.rightMargin: 3
                                                    anchors.leftMargin: 3
                                                    selectByMouse: true
                                                    smooth: true
                                                    onFocusChanged: {
                                                                if(focus){
                                                                    descriptionSRect.border.color = "#569ffd"
                                                                }else{
                                                                    descriptionSRect.border.color = "lightgray"
                                                                }
                                                            }
                                                }
                                            }
                                        }
                                        transformOrigin: Item.Center
                                        anchors.left: parent.left
                                        spacing: 10
                                        anchors.leftMargin: 0
                                        anchors.rightMargin: 0
                                    }
                                    RowLayout {
                                        y: 0
                                        height: 36
                                        anchors.right: parent.right
                                        Text {
                                            width: 60
                                            text: qsTr("Repeat")
                                            font.pixelSize: 12
                                            verticalAlignment: Text.AlignVCenter
                                        }

                                        Rectangle {
                                            id:repeatSRect
                                            Layout.fillWidth: true
                                            Layout.fillHeight: true
                                            border.color: "lightgray"
                                            border.width: 1
                                            TextEdit {
                                                id: textEditSRepeat
                                                text: "1"
                                                anchors.fill: parent
                                                font.pixelSize: 12
                                                Layout.fillWidth: true
                                                anchors.rightMargin: 3
                                                anchors.leftMargin: 3
                                                selectByMouse: true
                                                smooth: true
                                                verticalAlignment: TextInput.AlignVCenter
                                                onFocusChanged: {
                                                            if(focus){
                                                                repeatSRect.border.color = "#569ffd"
                                                            }else{
                                                                repeatSRect.border.color = "lightgray"
                                                            }
                                                        }
                                            }
                                        }
                                        transformOrigin: Item.Center
                                        anchors.left: parent.left
                                        spacing: 10
                                        anchors.rightMargin: 0
                                        anchors.leftMargin: 0
                                    }
                                    Item {
                                        width: 200
                                        height: 200
                                        Layout.fillHeight: true
                                        Layout.fillWidth: true
                                    }
                                }
                                ColumnLayout {
                                    id: addTestLayout
                                    visible:  false
                                    spacing: 10
                                    anchors.rightMargin: 10
                                    anchors.bottomMargin: 10
                                    anchors.leftMargin: 10
                                    anchors.topMargin: 10
                                    anchors.fill: parent
                                    RowLayout {
                                        y: 0
                                        height: 36
                                        anchors.right: parent.right
                                        Text {
                                            width: 60
                                            text: qsTr("Name")
                                            font.pixelSize: 12
                                            verticalAlignment: Text.AlignVCenter
                                        }
                                        Rectangle {
                                            id: nameTRect
                                            Layout.fillWidth: true
                                            Layout.fillHeight: true
                                            border.color: "lightgray"
                                            border.width: 1
                                            TextEdit {
                                                id: textEditTName
                                                text: qsTr("")
                                                anchors.fill: parent
                                                font.pixelSize: 12
                                                Layout.fillWidth: true
                                                anchors.rightMargin: 3
                                                anchors.leftMargin: 3
                                                selectByMouse: true
                                                smooth: true
                                                verticalAlignment: TextInput.AlignVCenter
                                                onFocusChanged: {
                                                            if(focus){
                                                                nameTRect.border.color = "#569ffd"
                                                            }else{
                                                                nameTRect.border.color = "lightgray"
                                                            }
                                                        }
                                                onTextChanged: {
                                                    if(testName.text=="New Test") {
                                                        if(textEditTName.text=="") {
                                                            textEditTExe.text="";
                                                        }
                                                        else {
                                                            textEditTExe.text=textEditTName.text+".js";
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        transformOrigin: Item.Center
                                        anchors.left: parent.left
                                        spacing: 10
                                        anchors.leftMargin: 0
                                        anchors.rightMargin: 0
                                    }
                                    RowLayout {
                                        y: 0
                                        height: 70
                                        Layout.minimumHeight: 68
                                        anchors.right: parent.right
                                        ColumnLayout {
                                            width: 100
                                            height: 100
                                            Layout.minimumHeight: 66
                                            Text {
                                                text: qsTr("Description")
                                                font.pixelSize: 12
                                                verticalAlignment: Text.AlignVCenter
                                            }
                                            Rectangle {
                                                id: descriptionTRect
                                                Layout.fillWidth: true
                                                Layout.fillHeight: true
                                                border.color: "lightgray"
                                                border.width: 1
                                                TextEdit {
                                                    id: textEditTDiscr
                                                    text: qsTr("")
                                                    anchors.fill: parent
                                                    Layout.minimumHeight: 50
                                                    font.pixelSize: 12
                                                    Layout.fillWidth: true
                                                    anchors.rightMargin: 3
                                                    anchors.leftMargin: 3
                                                    selectByMouse: true
                                                    smooth: true
                                                    onFocusChanged: {
                                                                if(focus){
                                                                    descriptionTRect.border.color = "#569ffd"
                                                                }else{
                                                                    descriptionTRect.border.color = "lightgray"
                                                                }
                                                            }
                                                }
                                            }
                                        }
                                        transformOrigin: Item.Center
                                        anchors.left: parent.left
                                        spacing: 10
                                        anchors.leftMargin: 0
                                        anchors.rightMargin: 0
                                    }
                                    RowLayout {
                                        y: 0
                                        height: 36
                                        anchors.right: parent.right
                                        Text {
                                            width: 60
                                            text: qsTr("Tag")
                                            font.pixelSize: 12
                                            verticalAlignment: Text.AlignVCenter
                                        }
                                        Rectangle {
                                            id:tagTRect
                                            Layout.fillWidth: true
                                            Layout.fillHeight: true
                                            border.color: "lightgray"
                                            border.width: 1
                                            TextEdit {
                                                id: textEditTTag
                                                text: qsTr("")
                                                anchors.fill: parent
                                                font.pixelSize: 12
                                                Layout.fillWidth: true
                                                anchors.rightMargin: 3
                                                anchors.leftMargin: 3
                                                selectByMouse: true
                                                smooth: true
                                                verticalAlignment: TextInput.AlignVCenter
                                                onFocusChanged: {
                                                            if(focus){
                                                                tagTRect.border.color = "#569ffd"
                                                            }else{
                                                                tagTRect.border.color = "lightgray"
                                                            }
                                                        }
                                            }
                                        }
                                        transformOrigin: Item.Center
                                        anchors.left: parent.left
                                        spacing: 10
                                        anchors.leftMargin: 0
                                        anchors.rightMargin: 0
                                    }
                                    RowLayout {
                                        y: 0
                                        height: 36
                                        anchors.right: parent.right
                                        Text {
                                            width: 60
                                            text: qsTr("Execution")
                                            font.pixelSize: 12
                                            verticalAlignment: Text.AlignVCenter
                                        }
                                        Rectangle {
                                            id:exeTRect
                                            Layout.fillWidth: true
                                            Layout.fillHeight: true
                                            border.color: "lightgray"
                                            border.width: 1
                                            TextEdit {
                                                id: textEditTExe
                                                text: qsTr("")
                                                anchors.fill: parent
                                                font.pixelSize: 12
                                                Layout.fillWidth: true
                                                anchors.rightMargin: 3
                                                anchors.leftMargin: 3
                                                selectByMouse: true
                                                smooth: true
                                                verticalAlignment: TextInput.AlignVCenter
                                                onFocusChanged: {
                                                            if(focus){
                                                                exeTRect.border.color = "#569ffd"
                                                            }else{
                                                                exeTRect.border.color = "lightgray"
                                                            }
                                                        }
                                            }
                                        }
                                        transformOrigin: Item.Center
                                        anchors.left: parent.left
                                        spacing: 10
                                        anchors.leftMargin: 0
                                        anchors.rightMargin: 0
                                    }
                                    RowLayout {
                                        y: 0
                                        height: 36
                                        anchors.right: parent.right
                                        Text {
                                            width: 60
                                            text: qsTr("Repeat")
                                            font.pixelSize: 12
                                            verticalAlignment: Text.AlignVCenter
                                        }

                                        Rectangle {
                                            id:repeatTRect
                                            Layout.fillWidth: true
                                            Layout.fillHeight: true
                                            border.color: "lightgray"
                                            border.width: 1
                                            TextEdit {
                                                id: textEditTRepeat
                                                text: "1"
                                                anchors.fill: parent
                                                font.pixelSize: 12
                                                Layout.fillWidth: true
                                                anchors.rightMargin: 3
                                                anchors.leftMargin: 3
                                                selectByMouse: true
                                                smooth: true
                                                verticalAlignment: TextInput.AlignVCenter
                                                onFocusChanged: {
                                                            if(focus){
                                                                repeatTRect.border.color = "#569ffd"
                                                            }else{
                                                                repeatTRect.border.color = "lightgray"
                                                            }
                                                        }
                                            }
                                        }
                                        transformOrigin: Item.Center
                                        anchors.left: parent.left
                                        spacing: 10
                                        anchors.rightMargin: 0
                                        anchors.leftMargin: 0
                                    }
                                    RowLayout {
                                        y: 0
                                        height: 36
                                        anchors.right: parent.right
                                        CheckBox {
                                            id: testImportant
                                            style: CheckBoxStyle {
                                                indicator: Rectangle {
                                                                implicitWidth: 16
                                                                implicitHeight: 16
                                                                radius: 3
                                                                border.color: control.activeFocus ? "darkblue" : "gray"
                                                                border.width: 1
                                                                Rectangle {
                                                                    visible: control.checked
                                                                    color: "#555"
                                                                    border.color: "#333"
                                                                    radius: 1
                                                                    anchors.margins: 4
                                                                    anchors.fill: parent
                                                                }
                                                        }
                                                label:Text {
                                                    font.pixelSize: 12
                                                    text: qsTr("Important")
                                                }
                                            }
                                            checked: false
                                        }
                                        transformOrigin: Item.Center
                                        anchors.left: parent.left
                                        spacing: 10
                                        anchors.rightMargin: 0
                                        anchors.leftMargin: 0
                                    }
                                    Item {
                                        width: 200
                                        height: 200
                                        Layout.fillHeight: true
                                        Layout.fillWidth: true
                                    }
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
                                                    enabled: false
                                                    onClicked: {
                                                        saveFile.open();
                                                    }
                                                    iconSource: "icons/icons/jssave.png"
                                                }
                                                ToolButton {
                                                    id: consoleClear
                                                    enabled: false
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
                                            contentItem: TextEdit {
                                                id: consoleText
                                                Layout.fillWidth: true
                                                selectByMouse: true
                                                font.pixelSize: 12
                                                onTextChanged: {
                                                    if(consoleText.text=="") {
                                                        consoleClear.enabled=false;
                                                        consoleSave.enabled=false;
                                                    }
                                                    else {
                                                        consoleClear.enabled=true;
                                                        consoleSave.enabled=true;
                                                    }
                                                }
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
        parent: consoleRect
        onAccepted: {
            if(saveFile.fileUrl.toString().split("///")[1]=="") {
                messageDialog.text="Please, select file";
                messageDialog.open();
                return;
            }
            var request = new XMLHttpRequest();
            request.open("PUT", saveFile.fileUrl, false);
            request.send(consoleText.text);
            return request.status;
        }
    }
    FileSaveDialog {
        id: editorFileDialog
        title: "Select editor"
        dialogMode: true
        parent: columnLayout1
        nameFilters: ["Programs (*.exe)"]
        onAccepted: {
            editorTextInput.text=editorFileDialog.fileUrl.toString().split("///")[1];
        }
    }
    Setting {
        id:settingFile
    }
    Window {
        id:mainsetting
        width: 300
        height: 200
        modality: Qt.ApplicationModal
        ColumnLayout {
            id: columnLayout1
            anchors.fill: parent
            anchors.rightMargin: 5
            anchors.bottomMargin: 5
            anchors.leftMargin: 5
            anchors.topMargin: 5
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
                            rootDir.text=settingFile.getRootDir();
                            theModel.setRootDir(rootDir.text);
                            if(rootDir.text!="") {
                                if(theModel.IsFolderEmpty(rootDir.text)) {
                                    showMenu.menuForSuite();
									addSuiteLayout.enabled=true;
                                    centerRect.visible=false;
                                    addSuiteLayout.visible=true;
                                    testName.text="New Suite";
                                    textEditSName.text="Main suite";
                                    testRun.visible=false;
                                    newTest.visible=false;
                                    newSuite.visible=false;
                                    testDelete.visible=false;
                                    testSetting.visible=false;
                                    restoreNew.visible=false;
                                    saveNew.visible=false;
                                    createNew.visible=true;
                                    mainTree.enabled=false;
                                    navigationBar.enabled=false;
                                }
                                else {
                                    var res=theModel.Load(rootDir.text);
                                    runTags.model=theModel.GetTags();
                                    theModel.setCurrentTag(runTags.currentText);
                                    if(res!="") {
                                        messageDialog.text=res;
                                        messageDialog.open()
                                        return;
                                    }
                                }
                            }
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
                Button {
                    id: selectDir
                    text: "..."
                    Layout.maximumWidth: 30
                    onClicked:{
                        selectFolderDialog.setFromSetting(true);
                        selectFolderDialog.show();
                    }
                }
            }
            RowLayout {
                id: rowLayout2
                width: 100
                height: 100
                clip: false
                spacing: 10
                Layout.alignment: Qt.AlignLeft | Qt.AlignTop
                Layout.fillHeight: true
                Layout.fillWidth: true
                Text {
                    id: text2
                    text: qsTr("External Editor")
                    font.pixelSize: 12
                }
                Rectangle {
                    id: editorRectInput
                    width: 82
                    height: 22
                    border.color: "lightgray"
                    border.width: 1
                    Layout.fillWidth: true
                    TextInput {
                        id: editorTextInput
                        verticalAlignment: TextInput.AlignVCenter
                        selectByMouse: true
                        anchors.fill: parent
                        anchors.rightMargin: 3
                        anchors.leftMargin: 3
                        smooth: true
                        text: {
                            editorTextInput.text=settingFile.getEditor();
                            if(editorTextInput.text!="") {
                                externalEditor.enabled=true;
                            }
                            else {
                                externalEditor.enabled=false;
                            }
                        }
                        layer.enabled: true
                        font.pixelSize: 12
                        onFocusChanged: {
                                    if(focus){
                                        editorRectInput.border.color = "#569ffd"
                                    }else{
                                        editorRectInput.border.color = "lightgray"
                                    }
                                }
                    }
                }
                Button {
                    id: selectEditor
                    text: "..."
                    Layout.maximumWidth: 30
                    onClicked:{
                        editorFileDialog.open();
                    }
                }
            }

            ColumnLayout{
                id: mailLayout
                Layout.alignment: Qt.AlignLeft
                Layout.fillHeight: true
                Layout.fillWidth: true
                CheckBox {
                    id: checkBox1
                    Layout.alignment: Qt.AlignLeft
                    text: qsTr("Send Report to E-mail")
                    checked: false
                    onCheckedChanged: {
                    if(checked == false){
                        label1.visible = false;
                        label2.visible = false;
                        label3.visible = false;
                        textInput1.visible = false;
                        textInput2.visible = false;
                        textInput3.visible = false;
                        textInput1.text="";
                        textInput2.text="";
                        textInput3.text="";

                    }else{
                        label1.visible = true;
                        label2.visible = true;
                        label3.visible = true;
                        textInput1.visible = true;
                        textInput2.visible = true;
                        textInput3.visible = true;
                    }
                    }
                }
                RowLayout{
                  ColumnLayout{
                   Label {
                       id: label1
                       visible: false
                       text: qsTr("Username")
                   }
                   Label {
                       id: label2
                       visible: false
                       x: 17
                       y: 158
                       text: qsTr("E-mail")
                   }
                   Label {
                       id: label3
                       visible: false
                       x: 23
                       y: 190
                       text: qsTr("Password ")
                   }
                  }
                  ColumnLayout{
                TextField {

                    id: textInput1
                    visible: false
                    x: 78
                    y: 116
                    width: 117
                    height: 20
                    font.pixelSize: 12;
                    placeholderText: qsTr("username")

                }

               TextField {
                   id: textInput2
                   visible: false
                   x: 115
                   y: 156
                   width: 80
                   height: 20
                   placeholderText: qsTr("username@gmail.com")
                   font.pixelSize: 12
               }

                TextField {
                    id: textInput3
                    visible: false
                    x: 84
                    y: 190
                    width: 111
                    height: 20
                    echoMode: TextInput.Password
                    placeholderText: qsTr("password")
                    font.pixelSize: 12
                }
              }
             }
            }
            RowLayout {
                id: rowLayout3
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
                        if(checkBox1.checked == true){
                        theModel.setMailCredentials(textInput1.text,textInput3.text,textInput2.text);
                         }else{theModel.setMailCredentials("default","default","default");}
                        settingFile.setEditor(editorTextInput.text);
                        if(editorTextInput.text!="") {
                            externalEditor.enabled=true;
                        }
                        else {
                            externalEditor.enabled=false;
                        }
                        theModel.setRootDir(rootDir.text);
                        settingFile.setRootDir(rootDir.text);
                        if(theModel.IsFolderEmpty(rootDir.text)) {
                            showMenu.menuForSuite();
							addSuiteLayout.enabled=true;
                            centerRect.visible=false;
                            addSuiteLayout.visible=true;
                            testName.text="New Suite";
                            textEditSName.text="Main suite";
                            textEditSDiscr.text="Main suite description";
                            testRun.visible=false;
                            newTest.visible=false;
                            newSuite.visible=false;
                            testDelete.visible=false;
                            testSetting.visible=false;
                            restoreNew.visible=false;
                            saveNew.visible=false;
                            createNew.visible=true;
                            mainTree.enabled=false;
                            navigationBar.enabled=false;
                        }
                        else {
                            var res=theModel.Load(rootDir.text);
                            runTags.model=theModel.GetTags();
                            theModel.setCurrentTag(runTags.currentText);
                            if(res!="") {
                                messageDialog.text=res;
                                messageDialog.open()
                                return;
                            }
                        }
                        mainsetting.close();
                    }
                }

                Button {
                    id: cancelSetting
                    onClicked: {
                        mainsetting.close();
                        rootDir.text=settingFile.getRootDir();
                        editorTextInput.text=settingFile.getEditor();
                        if(editorTextInput.text!="") {
                            externalEditor.enabled=true;
                        }
                        else {
                            externalEditor.enabled=false;
                        }
                    }
                    text: qsTr("Cancel")
                }
            }
        }
    }
    MessageDialog {
        id: messageDialog
        width: 200;
        modality: Qt.WindowModal
        title: "Warning!"
        icon: StandardIcon.Warning
        onAccepted: {
            Qt.quit();
        }
    }
    MessageDialog {
        id: deleteConfirm
        width: 200;
        modality: Qt.WindowModal
        title: "Warning"
        text: "Are you sure?"
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Ok | StandardButton.Cancel
        onAccepted: {
            var res=theModel.Remove();
            if(res!="") {
                messageDialog.text=res;
                messageDialog.open()
                return;
            }
            runTags.model=theModel.GetTags();
            theModel.setCurrentTag(runTags.currentText);
            if(res!="") {
                messageDialog.text=res;
                messageDialog.open()
                return;
            }
            selectItem(theModel.getCurrentIndex());
            Qt.quit();
        }
        onRejected: {
            Qt.quit();
        }
    }

    Window{
        modality: Qt.WindowModal
        id: report_window_
        visible: false
        width: 800
        height: 480
        title: qsTr("Report")
            ListView {
            id: list_V
            x: 0
            y: 42
            width: 182; height: 438
            TableView{
                model: MLM
                id: t_view
                x: 0
                y: -8
                width: report_window_.width
                height: report_window_.height
                onClicked: {
                    DD.row_selected(t_view.currentRow)
                }
                onDoubleClicked: {
                    DD.callBrowser();
                   // var component = Qt.createComponent("SessionWindow.qml");
                   //win = component.createObject(root);
                   // win.show();
                }
            TableViewColumn {
                                role: "session_n"
                                title: "ID"
                            }

            TableViewColumn {
                                role: "session_s"
                                title: "Start"
                            }
            TableViewColumn {
                                role: "session_d"
                                title: "Durration"
                            }
            TableViewColumn {
                                role: "session_e"
                                title: "End"
                            }
            TableViewColumn {
                                role: "session_p"
                                title: "Status"
                            }
            }
        }

        Label{
            x: 0
            y: 11
            width: 33
            height: 25
            text: "Start"
        }
        TextField {
            id: textField1
            x: 34
            y: 10
            readOnly: true
            width: 130
            height: 25
            placeholderText: qsTr(new Date().toJSON().slice(0,10).replace(/-/g,'/'))
        }
        Calendar{
            id:calenda
            x: 6
            y: 42
            width: 257
            height: 232
            visible: false
            frameVisible: true
            onClicked: {
            calenda.visible = false
            DD.getDateQML = calenda.selectedDate
            textField1.text = DD.getDateQML
            }
        }

        Button{
            x: 170
            y: 11
            width: 38
            height: 25
            text:"<>"
        onClicked: {
        if(calenda.visible == true){
        calenda.visible =false
        }
        else{
        calenda.visible = true
        }
        }
        }

        Label{
            x: 230
            y: 11
            width: 27
            height: 25
            text:"End"
        }
        TextField {
            id: textField2
            x: 263
            y: 10
            readOnly: true
            width: 130
            height: 25
            placeholderText: qsTr(new Date().toJSON().slice(0,10).replace(/-/g,'/'))
        }
        Calendar{
            id:end_date
            x:272
            y: 42
            width: 257
            height: 232
            //anchors.left: parent.left
            //anchors.leftMargin: 0
            visible: false
            frameVisible: true
            onClicked: {
                end_date.visible = false;
                DD.get_EndDate = end_date.selectedDate
                textField2.text = DD.get_EndDate
            }
        }
        Button{
            x: 399
            y: 10
            width: 38
            height: 25
            text:"<>"
        onClicked: {
        if(end_date.visible == true){
        end_date.visible =false
        }
        else{
        end_date.visible = true
        }
        }
        }
        Button{
            x: 673
            y: 10
            width: 127
            height: 25

            text:"Show"
            anchors.right: parent.right
            anchors.rightMargin: 0
            onClicked: {
                list_ = DD.get_seesion_db(textField1.text,textField2.text);
            }
        }
    }
}
