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
    id: se
    visible: true
    width: 640
    height: 480
    title: qsTr("Session window")
    property variant win_C;
    property  string st;

    ColumnLayout{
        x: 0
        y: 0
        width: parent.width
        height: parent.height
        spacing: 2

    Rectangle {
        id: content
        width: 800
        height: 600
        color: "white"
        Layout.alignment: Qt.AlignCenter
        Layout.preferredHeight: se.height
        Layout.preferredWidth:se.width
        WebView {
            id: webView
            anchors.fill: parent
            url: "file:///D:/TRS/TBox/T.html"
        }
    }

    Rectangle {
        id: rectangle1
        Button{
        Layout.alignment: Qt.AlignBottom
        Layout.preferredWidth: 70
        Layout.preferredHeight: 30
        id:export_button
        x: 527
        y: 445
        text: "Export"
        onClicked: {
           DD.test();
        }
        }
    }
   }

}
