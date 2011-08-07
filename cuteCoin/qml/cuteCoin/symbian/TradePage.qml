import QtQuick 1.0
import com.nokia.symbian 1.0

Page {
    id: page

    anchors.top: parent.top
    anchors.bottom: parent.bottom

    function updateContent(lsPrice, hPrice, lPrice) {
        lastPriceText.text = "$ " + lsPrice;
        highPriceText.text = "$ " + hPrice;
        lowPriceText.text = "$ " + lPrice;
    }

    Flickable {
        id: flickable

        width: parent.width
        height: parent.height

        contentHeight: lowPriceText.y + lowPriceText.height + 10;

        clip: true

        Button {
            id: mtGoxButton

            anchors.top: parent.top
            anchors.left: parent.left
            width: parent.width / 2
            text: "Mt. Gox"

            onClicked: Qt.openUrlExternally("https://mtgox.com");
        }

        Button {
            id: tradehillButton

            anchors.top: parent.top
            anchors.right: parent.right
            width: parent.width / 2
            text: "Tradehill"

            onClicked: Qt.openUrlExternally("https://www.tradehill.com");
        }

        Text {
            id: lastPriceTitle

            anchors.top: mtGoxButton.bottom
            anchors.topMargin: 10

            anchors.left: parent.left
            anchors.leftMargin: 10

            anchors.right: parent.right

            color: "white"
            font.pointSize: 10
            text: "Last Price"
        }

        Text {
            id: lastPriceText

            anchors.top: lastPriceTitle.bottom

            anchors.left: lastPriceTitle.left
            anchors.right: parent.right

            color: "white"
            text: "N/A"
            font.pointSize: 8

        }

        // HIGH PRICE
        Text {
            id: highPriceTitle

            anchors.top: lastPriceText.bottom
            anchors.topMargin: 10

            anchors.left: lastPriceText.left

            anchors.right: parent.right

            color: "white"
            font.pointSize: 10
            text: "Highest Price"
        }

        Text {
            id: highPriceText

            anchors.top: highPriceTitle.bottom

            anchors.left: highPriceTitle.left
            anchors.right: parent.right

            color: "white"
            text: "N/A"
            font.pointSize: 8

        }

        // LOW PRICE
        Text {
            id: lowPriceTitle

            anchors.top: highPriceText.bottom
            anchors.topMargin: 10

            anchors.left: highPriceText.left

            anchors.right: parent.right

            color: "white"
            font.pointSize: 10
            text: "Lowest Price"
        }

        Text {
            id: lowPriceText

            anchors.top: lowPriceTitle.bottom

            anchors.left: lowPriceTitle.left
            anchors.right: parent.right

            color: "white"
            text: "N/A"
            font.pointSize: 8

        }

    }


}
