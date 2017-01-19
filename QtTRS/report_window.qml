import QtQuick 2.4
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQml.Models 2.1
import QtQml 2.0 as QML
import QtQml 2.2
//import models 1.0
ApplicationWindow {

    id: applicationWindow1
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Button{
        id: exportButton
        x: 528
        y: 451
        width: 112
        height: 29
        text:"Export"
        onClicked: {}
    }

    TabView {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.rightMargin: 0
        anchors.bottomMargin: 29
        anchors.leftMargin: 0
        anchors.topMargin: 0

        Tab {
            title: "List"
            Rectangle{
            //MyTreeModel {
            //    id: theModel
            //}
            TreeView {
                anchors.fill: parent
                model: DD
                itemDelegate: Rectangle {
                           color: ( styleData.row % 2 == 0 ) ? "white" : "lightblue"
                           height: 20

                           Text {
                               anchors.verticalCenter: parent.verticalCenter
                               text: styleData.value === undefined ? "" : styleData.value // The branches don't have a description_role so styleData.value will be undefined
                           }
                       }

                TableViewColumn {
                    role: "name_role"
                    title: "Name"
                }
                TableViewColumn {
                    role: "description_role"
                    title: "Description"
                }
            }
            }

        }


        Tab {

            title: "Custom"




        }


    }


}
