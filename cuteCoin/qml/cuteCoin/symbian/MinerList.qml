import QtQuick 1.0

ListView {

    model: minerData
    delegate: Text {
        text: name + "\n" + value
    }

    Text {
        id: plainText
        text: "EEO EsO"
        anchors.top: parent.top
        color: "white"
    }

    ListModel {
        id: minerData

        ListElement {
            name: "Balance"
            value: "0.01 BTC"
        }
        ListElement {
            name: "Confirmed earnings"
            value: "0.005352 BTC"
        }
        ListElement {
            name: "Unconfirmed earnings"
            value: "NONE"
        }
    }

}
