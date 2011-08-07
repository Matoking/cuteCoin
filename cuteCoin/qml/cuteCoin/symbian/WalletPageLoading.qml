import QtQuick 1.0
import com.nokia.symbian 1.0

Page {
    id: page

    anchors.top: parent.top
    anchors.bottom: parent.bottom

    function setTask(task) {
        loadText.text = task;
    }

    BusyIndicator {
        id: busyIndicator

        anchors.centerIn: parent

        running: true

        height: 100
        width: 100
    }

    Text {
        id: loadText

        text: "Creating an eWallet..."
        color: "white"

        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 8

        anchors.left: parent.left
        anchors.right: parent.right

        anchors.bottom: busyIndicator.top
        anchors.bottomMargin: 20
    }
}
