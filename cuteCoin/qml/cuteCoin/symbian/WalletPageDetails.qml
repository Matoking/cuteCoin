import QtQuick 1.0
import com.nokia.symbian 1.0

Page {
    id: page

    anchors.top: parent.top
    anchors.bottom: parent.bottom

    signal copyAddress(string address);
    signal openSend();

    function updateWallet(address, balance) {
        bitcoinAddressText.text = address;
        balanceText.text = balance + " BTC";
    }

    Flickable {
        id: flickable

        width: parent.width
        height: parent.height

        anchors.top: parent.top

        clip: true

        Text {
            id: bitcoinAddressText

            text: "Bitcoin Address HERE"

            font.pointSize: 6
            color: "white"

            horizontalAlignment: Text.AlignHCenter

            anchors.top: parent.top
            anchors.topMargin: 10

            anchors.left: parent.left
            anchors.right: parent.right
        }

        Text {
            id: balanceTitle

            text: "Wallet Balance"
            color: "white"

            font.pointSize: 10

            horizontalAlignment: Text.AlignHCenter

            anchors.top: bitcoinAddressText.bottom
            anchors.topMargin: 20

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
        }

        Text {
            id: balanceText

            text:  "0 BTC"
            color: "white"

            horizontalAlignment: Text.AlignHCenter

            anchors.top: balanceTitle.bottom
            anchors.topMargin: 10

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
        }

        Button {
            id: sendButton

            text: "Send Coins"

            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10

            anchors.left: parent.left
            anchors.right: parent.right

            onClicked: openSend();
        }

        Button {
            id: copyAddressButton

            text: "Copy Bitcoin address"

            anchors.bottom: sendButton.top
            anchors.bottomMargin: 10

            anchors.left: parent.left
            anchors.right: parent.right

            onClicked: copyAddress(bitcoinAddressText.text);
        }
    }
}
