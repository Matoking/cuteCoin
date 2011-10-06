import QtQuick 1.0
import com.nokia.symbian 1.0

Page {
    id: page

    signal createWalletClicked();

    property bool walletBeingCreated: false

    function createWallet() {
        if (walletBeingCreated == true) return;
        walletBeingCreated = true;
        createWalletClicked();
    }

    anchors.top: parent.top

    Text {
        id: walletEmptyText
        text: "Wallet hasn't been created yet."
        color: "white"
        horizontalAlignment: Text.AlignHCenter
        anchors.centerIn: parent
    }

    Button {
        id: createWalletButton
        text: "Create an eWallet"
        height: 50

        anchors.top: walletEmptyText.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.right: parent.right

        onClicked: createWallet();
    }
}
