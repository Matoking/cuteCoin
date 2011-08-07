import QtQuick 1.0
import com.nokia.symbian 1.0

Page {
    anchors.top: parent.top

    signal settingsButtonClicked

    Text {
        id: minerEmptyText
        text: "Mining pool hasn't been set or updated yet."
        width: parent.width
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
        anchors.centerIn: parent
    }

    Button {
        id: openSettings
        text: "Open Settings"
        height: 50

        anchors.top: minerEmptyText.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.right: parent.right

        onClicked: settingsButtonClicked();
    }
}
