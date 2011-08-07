import QtQuick 1.0
import com.nokia.symbian 1.0

Page {
    id: page

    anchors.top: parent.top
    anchors.bottom: parent.bottom

    signal goBack()

    signal sendTransaction(string address, string amount);

    function checkTransaction() {
        if (addressTextfield.text != "") {
            if (amountTextfield.errorHighlight == false) {
                sendTransaction(addressTextfield.text, amountTextfield.text);
                return;
            }
        }
        dialog.open();
    }

   Dialog {
        id: dialog

        title: Text {
            id: dialogTitle
            text: "Error"
            font { family: platformStyle.fontFamilyRegular; pixelSize: platformStyle.fontSizeLarge; }
            color: platformStyle.colorNormalLink
            anchors.fill: parent
            anchors.leftMargin: platformStyle.paddingLarge
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        buttons: ToolBar {
            id: buttons
            width: parent.width
            height: privateStyle.toolBarHeightLandscape + 2 * platformStyle.paddingSmall

            tools: Row {
                anchors.centerIn: parent
                spacing: platformStyle.paddingMedium

                ToolButton {
                    text: "Ok"
                    width: (buttons.width - 3 * platformStyle.paddingMedium) / 2
                    onClicked: dialog.accept()
                }
            }
        }

        content: Text {
            text: "Wrong address and/or amount information."
            font { bold: true; pixelSize: 16; }
            color: "white"
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
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
            id: paymentAddressText

            text: "Pay To"

            font.pointSize: 8
            color: "white"

            anchors.top: parent.top
            anchors.topMargin: 10

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
        }

        TextField {
            id: addressTextfield

            anchors.top: paymentAddressText.bottom
            anchors.topMargin: 10

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10

            placeholderText: "Enter the recipient's address here"
        }

        Button {
            id: addressPasteButton

            anchors.bottom: addressTextfield.top
            anchors.right: parent.right
            anchors.rightMargin: 10
            width: parent.width / 4

            text: "Paste"

            onClicked: pasteAddress();

            function pasteAddress() {
                addressTextfield.text = "";
                addressTextfield.paste();
            }
        }

        Text {
            id: amountText

            text: "Amount"

            font.pointSize: 8
            color: "white"

            anchors.top: addressTextfield.bottom
            anchors.topMargin: 10

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
        }

        TextField {
            id: amountTextfield

            anchors.top: amountText.bottom
            anchors.topMargin: 10

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10

            validator: DoubleValidator{bottom: 0; decimals: 8;}

            placeholderText: "Enter the amount here"
        }

        Button {
            id: sendButton

            text: "Send"

            anchors.bottom: parent.bottom

            anchors.left: parent.left

            width: parent.width / 2

            onClicked: checkTransaction();
        }

        Button {
            id: backButton

            text: "Back"

            anchors.bottom: parent.bottom
            anchors.left: sendButton.right

            width: parent.width / 2

            onClicked: goBack();

        }
    }
}
