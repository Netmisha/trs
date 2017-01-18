import QtQuick 2.0
import QtQuick.Controls 1.0

ApplicationWindow {
    id: idApp
    visible: true
    width: 640
    height: 480
    title: qsTr("TBox")

    MainForm {
        id: idForm
        anchors.fill: parent
    }
}
