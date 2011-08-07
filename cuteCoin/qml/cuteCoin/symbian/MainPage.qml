import QtQuick 1.0
import com.nokia.symbian 1.0

Page {
    id: page

    anchors.top: parent.top
    anchors.bottom: parent.bottom

    Flickable {
        id: flickable

        width: parent.width
        height: parent.height

        anchors.top: parent.top

        clip: true

        Text {
            id: cuteCoinTitle

            text: "cuteCoin"
            color: "white"

            font.pointSize: 14

            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: cuteCoinAuthor

            text: "by Matoking"
            color: "white"

            font.pointSize: 10

            anchors.top: cuteCoinTitle.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: cuteCoinVersion

            text: "v. 0.5"
            color: "white"

            font.pointSize: 10

            anchors.top: cuteCoinAuthor.bottom
            anchors.topMargin: 5

            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: blogButton

            text: "Matoking's Blog"

            anchors.bottom: gitHubButton.top
            anchors.bottomMargin: 10

            anchors.left: parent.left
            anchors.right: parent.right

            onClicked: Qt.openUrlExternally("http://matoking-blog.blogspot.com");
        }

        Button {
            id: gitHubButton

            text: "Github Page"

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20

            anchors.left: parent.left
            anchors.right: parent.right

            onClicked: Qt.openUrlExternally("https://github.com/Matoking/cuteCoin");
        }

    }
}
