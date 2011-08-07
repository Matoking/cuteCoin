import QtQuick 1.0
import com.nokia.symbian 1.0

Window {

    Text {
        id: title
        text: "cuteCoin"
        color: "white"
        font.pointSize: 20
        anchors.top: parent.top
    }

    Text {
        text: "Made by Matoking"
        color: "white"
        font.pointSize: 15
        anchors.top: title.bottom
    }
}
