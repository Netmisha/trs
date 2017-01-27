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
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Session window")
    Rectangle {
        id: content
        width: 800
        height: 600
        color: "black"

        WebView {
            id: webView
            anchors.fill: parent
            url: "file:///D:/TRS/TBox/T.html"
        }
    }
}
