import QtQuick 1.0
import com.nokia.symbian 1.0

Page {
    id: page

    signal createWalletClicked();

    signal copiedAddress(string btcaddress);

    signal sendTransaction(string address, string amount);

    anchors.top: parent.top

    property bool sending: false

    function createWalletLoad() {
        createWalletClicked();
        pageStack.push(walletPageLoading);
        walletPageLoading.setTask("Creating an eWallet...");
    }

    function updateWallet(address, balance) {
        walletPageDetails.updateWallet(address, balance);
        if (sending == false) { pageStack.push(walletPageDetails); }
    }

    function openSendMenu() {
        sending = true;
        pageStack.push(walletPageSend);
    }

    function closeSendMenu() {
        sending = false;
        pageStack.push(walletPageDetails);
    }

    function sendCoins(address, amount) {
        pageStack.push(walletPageLoading);
        walletPageLoading.setTask("Sending Bitcoins...");
        sendTransaction(address, amount);
    }

    PageStack {
    id: pageStack

        WalletPageEmpty {
            id: walletPageEmpty

            anchors.fill: parent

            onCreateWalletClicked: createWalletLoad();

        }

        WalletPageLoading {
            id: walletPageLoading

            anchors.fill: parent
        }

        WalletPageDetails {
            id: walletPageDetails

            anchors.top: parent.top
            anchors.bottom: parent.bottom

            onCopyAddress: copiedAddress(address);
            onOpenSend: openSendMenu();
        }

        WalletPageSend {
            id: walletPageSend

            anchors.top: parent.top
            anchors.bottom: parent.bottom

            onGoBack: closeSendMenu();
            onSendTransaction: sendCoins(address, amount);
        }
    }

    Component.onCompleted: pageStack.push(walletPageEmpty);
}
