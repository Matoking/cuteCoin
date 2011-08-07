import QtQuick 1.0
import com.nokia.symbian 1.0

Page {
    id: page

    anchors.top: parent.top
    anchors.bottom: parent.bottom

    property int selection: 1

    function updateMinerData(shares, confirmed, unconfirmed, estimated) {
        selection = 1;
        if (shares != "N/A") {
            updateValue(selection, "Shares (round)", shares)
            selection++;
        }
        if (confirmed != "N/A") {
            updateValue(selection, "Confirmed earnings", confirmed + " BTC")
            selection++;
        }
        if (unconfirmed != "N/A") {
            updateValue(selection, "Unconfirmed earnings", unconfirmed + " BTC")
            selection++;
        }
        if (estimated != "N/A") {
            updateValue(selection, "Estimated earnings", estimated + " BTC")
            selection++;
        }
    }

    function updateValue(id, title, value) {
        if (id == 1) {
            minerTitle01.text = title;
            minerText01.text = value;

            flickable.contentHeight = minerText01.y + minerText01.height + 10;

            minerTitle02.text = "";
            minerText02.text = "";

            minerTitle03.text = "";
            minerText03.text = "";

            minerTitle04.text = "";
            minerText04.text = "";
        }

        if (id == 2) {
            minerTitle02.text = title;
            minerText02.text = value;

            flickable.contentHeight = minerText02.y + minerText02.height + 10;

            minerTitle03.text = "";
            minerText03.text = "";

            minerTitle04.text = "";
            minerText04.text = "";
        }
        if (id == 3) {
            minerTitle03.text = title;
            minerText03.text = value;

            flickable.contentHeight = minerText03.y + minerText03.height + 10;

            minerTitle04.text = "";
            minerText04.text = "";
        }
        if (id == 4) {
            minerTitle04.text = title;
            minerText04.text = value;

            flickable.contentHeight = minerText04.y + minerText04.height + 10;
        }
    }

    Flickable {
        id: flickable

        width: parent.width
        height: parent.height

        anchors.top: parent.top
        anchors.bottom: parent.bottom

        clip: true

        Text {
            id: minerTitle01

            anchors.top: parent.top
            anchors.topMargin: 10

            anchors.left: parent.left
            anchors.leftMargin: 10

            anchors.right: parent.right

            color: "white"
            font.pointSize: 10
            text: "Title N:O 1"
        }

        Text {
            id: minerText01

            anchors.top: minerTitle01.bottom

            anchors.left: minerTitle01.left
            anchors.right: parent.right

            color: "white"
            text: "N/A"
            font.pointSize: 8

        }

        Text {
            id: minerTitle02

            anchors.top: minerText01.bottom
            anchors.topMargin: 10

            anchors.left: parent.left
            anchors.leftMargin: 10

            anchors.right: parent.right

            color: "white"
            font.pointSize: 10
            text: "Title N:O 1"
        }

        Text {
            id: minerText02

            anchors.top: minerTitle02.bottom

            anchors.left: minerTitle02.left
            anchors.right: parent.right

            color: "white"
            text: "N/A"
            font.pointSize: 8

        }

        Text {
            id: minerTitle03

            anchors.top: minerText02.bottom
            anchors.topMargin: 10

            anchors.left: parent.left
            anchors.leftMargin: 10

            anchors.right: parent.right

            color: "white"
            font.pointSize: 10
            text: "Title N:O 1"
        }

        Text {
            id: minerText03

            anchors.top: minerTitle03.bottom

            anchors.left: minerTitle03.left
            anchors.right: parent.right

            color: "white"
            text: "N/A"
            font.pointSize: 8

        }

        Text {
            id: minerTitle04

            anchors.top: minerText03.bottom
            anchors.topMargin: 10

            anchors.left: parent.left
            anchors.leftMargin: 10

            anchors.right: parent.right

            color: "white"
            font.pointSize: 10
            text: "Title N:O 1"
        }

        Text {
            id: minerText04

            anchors.top: minerTitle04.bottom

            anchors.left: minerTitle04.left
            anchors.right: parent.right

            color: "white"
            text: "N/A"
            font.pointSize: 8

        }

    }

}
