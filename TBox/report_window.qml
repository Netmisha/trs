import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2
import QtQuick.Window 2.2
import QtQuick.Controls 1.1
import QtQml.Models 2.2
import QtQuick.Controls.Styles 1.0
import QtQuick.Controls.Private 1.0
import QtQml.Models 2.1
import QtQml 2.0 as QML
import QtQml 2.2
import QtQuick.Window 2.1
import QtWebKit 3.0
ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 480
    title: qsTr("Reports")
    property variant win;
    property  variant list_;
    property  variant db_list;
        ListView {
        id: list_V
        x: 0
        y: 42
        width: 182; height: 438
        TableView{
            //model: MLM
            id: t_view
            x: 0
            y: -8
            width: root.width
            height: root.height
            onClicked: {
                DD.row_selected(t_view.currentRow)
            }
            onDoubleClicked: {
                var component = Qt.createComponent("SessionWindow.qml")
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
