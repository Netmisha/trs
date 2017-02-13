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
import QtQuick.Dialogs 1.0
ApplicationWindow{
    modality: Qt.WindowModal
    id: se
    visible: true
    width: 640
    height: 480
    title: qsTr("Session window")
    property variant win_C;
    property  string st;
    FileDialog {
        id:fileDialog
        visible: false
        title: "Select folder";
        folder: shortcuts.home;
        selectFolder: true
        onAccepted: {
           DD.getExportPath(fileDialog.folder);
        }
    }
    ColumnLayout{
        id: columnLayout
        x: 0
        y: 0
        width: se.width
        height: se.height
        spacing: 2
    Rectangle {
        id: content
        width: se.width
        height: se.height
        color: "white"
        Layout.alignment: Qt.AlignCenter
        Layout.preferredHeight: se.height
        Layout.preferredWidth:se.width
        WebView {
            id: webView
            anchors.fill: parent
            url: "file:///"+DD.getTableSessionPath();
        }
    }

        Button{
            anchors.top: columnLayout.top;
            anchors.right: columnLayout.right;
            anchors.margins: 10;
            width: 130
            height: 120
            id:export_button
        text: "Export"
        onClicked: {
            fileDialog.visible = true;
            DD.test();
        }
        }

   }

}
