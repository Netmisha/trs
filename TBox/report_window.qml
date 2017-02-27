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
ApplicationWindow{
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
                var component = Qt.createComponent("SessionWindow.qml");
                win = component.createObject(root);
                win.show();
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
