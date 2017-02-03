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
    Window{
        id: report_window_
        visible: false
        width: 800
        height: 480
        title: qsTr("Reports")
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
                    var component = Qt.createComponent("SessionWindow.qml");
                    win = component.createObject(root);
                    win.show();
                }
            TableViewColumn {
                                role: "session_n"
                                title: "Session"
                            }

            TableViewColumn {
                                role: "session_s"
                                title: "Session start"
                            }
            TableViewColumn {
                                role: "session_d"
                                title: "Session durration"
                            }
            TableViewColumn {
                                role: "session_e"
                                title: "Session end"
                            }
            TableViewColumn {
                                role: "session_p"
                                title: "Session passed"
                            }
            }
        }
        Button{
            x: 673
            y: 0
            width: 127
            height: 33
            text:"Show"
            onClicked: {
            list_ = DD.get_seesion_db(textField1.text,textField2.text);
            }
        }
        Button{
            x: 401
            y: 0
            width: 38
            height: 33
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
        TextField {
            id: textField1
            x: 39
            y: 0
            readOnly: true
            width: 130
            height: 33
             placeholderText: "Set start date"
        }
        Button{
            x: 168
            y: 0
            width: 38
            height: 33
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
            x: 0
            y: 3
            width: 33
            height: 28
            text: "Start"
        }
        Label{
            x: 238
            y: 5
            width: 27
            height: 23
            text:"End"
        }
        TextField {
            id: textField2
            x: 271
            y: 0
            readOnly: true
            width: 130
            height: 33
            placeholderText: "Set end date"
        }
        Calendar{
            id:end_date
            x: 278
            y: 34
            width: 257
            height: 232
            visible: false
            frameVisible: true
            onClicked: {
                DD.get_EndDate = end_date.selectedDate
                textField2.text = DD.get_EndDate
            }
        }
        Calendar{
            id:calenda
            x: 8
            y: 34
            width: 257
            height: 232
            visible: false
            frameVisible: true
            onClicked: {
            DD.getDateQML = calenda.selectedDate
            textField1.text = DD.getDateQML
            }
        }
    }
    id: root
    anchors.fill: parent
    function checkRootDir() {
        if(rootDir.text==""){
            selectFolderDialog.setFromSetting(false);
            selectFolderDialog.show();
        }
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
        jsCodeEdit.text = theModel.FindTest(index);
        lineRect.visible=false;
        lineRect.width=0;
        if(theModel.GetType()=="test") {
            showMenu.menuForTest();
            lineRect.visible=true;
            lineRect.width=Math.max(jsCodeEdit.lineCount.toString().length, (lineColumn.height/lineColumn.rowHeight).toFixed(0).toString().length)*jsCodeEdit.font.pixelSize;
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
    Item {
        id: showMenu
        function menuForSuite() {
            testToolBar.visible=true;
            newTest.visible=true;
            newSuite.visible=true;
            centerRect.visible=false;
            testEdit.visible=false;
        }
        function menuForTest() {
            testToolBar.visible=true;
            newTest.visible=false;
            newSuite.visible=false;
            centerRect.visible=true;
            testEdit.visible=true;
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
                    onClicked: {
                        consoleText.text="";
                        theModel.Run();
                    }
                    iconSource: "icons/icons/Run.png"
                }
                ToolButton {
                    id: reportsButton
                    iconSource: "icons/icons/report.png"
                    onClicked: report_window_.show();
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
                       headerVisible: false
                       itemDelegate: Rectangle {
                          id : recid
                          color: "transparent"
                          height: 20
                          Text {
                              anchors.verticalCenter: parent.verticalCenter
                              text: styleData.value
                          }
                       }
                       rowDelegate: Rectangle {
                           color: styleData.selected?"#3399ff":"transparent"
                           height: 20
                       }
                       onClicked: {
                           root.showItem(index);
                       }
                       onDoubleClicked: {
                           root.showItem(index);
                           if(mainTree.isExpanded(index)) {
                                mainTree.collapse(index);
                           }
                           else {
                                mainTree.expand(index);
                           }
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
                                            /*ComboBox{
                                                id: fontComboBox
                                                width: 50
                                                currentIndex: 4
                                                visible: false
                                                model: ["8","9","10","11","12","14","16","18","20","22","24","26","28","36","48","72"]
                                                onCurrentIndexChanged: {
                                                    jsCodeEdit.font.pixelSize=parseInt(fontComboBox.currentText);
                                                    lineRect.width=Math.max(jsCodeEdit.lineCount.toString().length, (lineColumn.height/lineColumn.rowHeight).toFixed(0).toString().length)*jsCodeEdit.font.pixelSize;
                                                }
                                            }*/
                                            ToolButton {
                                                id: testStatus
                                                onClicked: {
                                                    if(theModel.Get("disable")=="true"){
                                                        testStatus.iconSource="icons/icons/turnon.png";
                                                        theModel.Set("disable","false");
                                                    }
                                                    else if(theModel.Get("disable")=="false"){
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
                                                    centerRect.visible=false;
                                                    addTestLayout.visible=true;
                                                    testName.text="New Test";
                                                    testRun.visible=false;
                                                    newTest.visible=false;
                                                    newSuite.visible=false;
                                                    testDelete.visible=false;
                                                    testSetting.visible=false;
                                                    restoreNew.visible=true;
                                                    saveNew.visible=true;
                                                    mainTree.enabled=false;
                                                    navigationBar.enabled=false;
                                                }
                                            }
                                            ToolButton {
                                                id: newSuite
                                                iconSource: "icons/icons/newsuite.png"
                                                onClicked: {
                                                    centerRect.visible=false;
                                                    addSuiteLayout.visible=true;
                                                    testName.text="New Suite";
                                                    testRun.visible=false;
                                                    newTest.visible=false;
                                                    newSuite.visible=false;
                                                    testDelete.visible=false;
                                                    testSetting.visible=false;
                                                    restoreNew.visible=true;
                                                    saveNew.visible=true;
                                                    mainTree.enabled=false;
                                                    navigationBar.enabled=false;
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
                                                onClicked:{
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
                                                    navigationBar.enabled=false;
                                                    //fontComboBox.visible=true;
                                                }
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
                                                    saveJS.visible=false;
                                                    jsCodeRect.color="#f6f6f6";
                                                    cancelJS.visible=false;
                                                    mainTree.enabled=true;
                                                    navigationBar.enabled=true;
                                                    //fontComboBox.visible=false;

                                                }
                                                iconSource: "icons/icons/restore.png"
                                            }
                                            ToolButton {
                                                id: saveJS
                                                visible: false;
                                                onClicked: {
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
                                                    //fontComboBox.visible=false;
                                                }
                                                iconSource: "icons/icons/jssave.png"
                                            }
                                            ToolButton {
                                                id: testSetting
                                                iconSource: "icons/icons/testsetting.png"
                                                onClicked:{
                                                    if(theModel.GetType() == "test") {
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
                                                        mainTree.enabled=false;
                                                        navigationBar.enabled=false;
                                                    }
                                                    else if(theModel.GetType()=="suite") {
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
                                                        navigationBar.enabled=false;
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
                                                        newTest.visible=true;
                                                        newSuite.visible=true;
                                                    }
                                                    else if(testName.text== "New Suite") {
                                                        textEditSName.text="";
                                                        textEditSDiscr.text="";
                                                        textEditSRepeat.text="1";
                                                        addSuiteLayout.visible=false;
                                                        newTest.visible=true;
                                                        newSuite.visible=true;
                                                    }
                                                    else {
                                                        if(theModel.GetType()=="test") {
                                                            textEditTName.text="";
                                                            textEditTDiscr.text="";
                                                            textEditTExe.text="";
                                                            textEditTTag.text="";
                                                            textEditTRepeat.text="1";
                                                            addTestLayout.visible=false;
                                                            testEdit.visible=true;
                                                        }
                                                        else {
                                                            textEditSName.text="";
                                                            textEditSDiscr.text="";
                                                            textEditSRepeat.text="1";
                                                            addSuiteLayout.visible=false;
                                                            newTest.visible=true;
                                                            newSuite.visible=true;
                                                        }
                                                    }
                                                    centerRect.visible=true;
                                                    testName.text=theModel.Get("name");
                                                    testRun.visible=true;
                                                    testDelete.visible=true;
                                                    testSetting.visible=true;
                                                    restoreNew.visible=false;
                                                    saveNew.visible=false;
                                                    mainTree.enabled=true;
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
                                                        var res=theModel.AddNewTest(textEditTName.text,textEditTDiscr.text, textEditTExe.text, textEditTTag.text, textEditTRepeat.text, dis);
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
                                                        newTest.visible=true;
                                                        newSuite.visible=true;
                                                    }
                                                    else if(testName.text== "New Suite") {
                                                        var dis=testStatus.iconSource.toString().indexOf("turnon")!=-1?"false":"true";
                                                        var res=theModel.AddNewSuite(textEditSName.text,textEditSDiscr.text, textEditSRepeat.text, dis);
                                                        if(res!="") {
                                                            messageDialog.text=res;
                                                            messageDialog.open()
                                                            return;
                                                        }
                                                        textEditSName.text="";
                                                        textEditSDiscr.text="";
                                                        textEditSRepeat.text="1";
                                                        addSuiteLayout.visible=false;
                                                        newTest.visible=true;
                                                        newSuite.visible=true;
                                                    }
                                                    else {
                                                        var dis=testStatus.iconSource.toString().indexOf("turnon")!=-1?"false":"true";
                                                        if(theModel.GetType()=="test") {
                                                            if(textEditTName.text!="" && textEditTExe.text!="") {
                                                                theModel.Set("name", textEditTName.text);
                                                                theModel.Set("description", textEditTDiscr.text);
                                                                theModel.Set("tag", textEditTTag.text);
                                                                theModel.Set("execution", textEditTExe.text);
                                                                theModel.Set("repeat", textEditTRepeat.text==""?"1":textEditTRepeat.text);
                                                                theModel.Set("disable", dis);
                                                                addTestLayout.visible=false;
                                                                testEdit.visible=true;
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
                                                                addSuiteLayout.visible=false;
                                                            }
                                                            else {
                                                                messageDialog.text="Fill all fields correctly!";
                                                                messageDialog.open()
                                                                return;
                                                            }
                                                        }
                                                    }
                                                    runTags.model=theModel.GetTags();
                                                    centerRect.visible=true;
                                                    testName.text=theModel.Get("name");
                                                    testRun.visible=true;
                                                    testDelete.visible=true;
                                                    testSetting.visible=true;
                                                    restoreNew.visible=false;
                                                    saveNew.visible=false;
                                                    mainTree.enabled=true;
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
                                                property int rowHeight: jsCodeEdit.font.pixelSize+2
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
                                            font.pixelSize: 14
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
                                            TextEdit {
                                                id: consoleText
                                                anchors.horizontalCenter: parent.horizontalCenter
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
                        theModel.setRootDir(rootDir.text);
                        settingFile.setRootDir(rootDir.text);
                        if(theModel.IsFolderEmpty(rootDir.text)) {
                            showMenu.menuForSuite();
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
                        mainsetting.close();
                    }
                }

                Button {
                    id: cancelSetting
                    onClicked: {
                        mainsetting.close();
                        rootDir.text=settingFile.getRootDir();
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
            res=theModel.Load(settingFile.getRootDir());
            runTags.model=theModel.GetTags();
            theModel.setCurrentTag(runTags.currentText);
            if(res!="") {
                messageDialog.text=res;
                messageDialog.open()
                return;
            }
            Qt.quit();
        }
        onRejected: {
            Qt.quit();
        }
    }

}
