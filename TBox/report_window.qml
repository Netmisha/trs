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
        x: 503
        y: 451
        width: 112
        height: 29
        text:"Export"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0
        onClicked: {}
    }

    TabView {
        id: tabView1
        anchors.bottomMargin: 30
        anchors.fill: parent

        Tab {
            title: "List"
            Rectangle{
            //MyTreeModel {
            //    id: theModel
            //}
            TreeView {
                anchors.fill: parent
                model: DD
                id: tree_V
                itemDelegate: Rectangle {
                           color: ( styleData.row % 2 == 0 ) ? "white" : "lightblue"
                           height: 20

                           Text {
                               anchors.verticalCenter: parent.verticalCenter
                               text: styleData.value === undefined ? "" : styleData.value
                           }
                       }
                onClicked: {
                        console.log("clicked", tree_V.currentIndex)
                    }
                TableViewColumn {
                    role: "name_role"
                    title: "Name"
                }


            }
            }

        }


        Tab {
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left

            title: "Custom"




        }


    }



}
