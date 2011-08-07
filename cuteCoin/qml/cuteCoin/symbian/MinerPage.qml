import QtQuick 1.0
import com.nokia.symbian 1.0

Page {
    id: page

    anchors.top: parent.top
    anchors.bottom: parent.bottom

    signal settingsClicked();

    function showMinerStats(bool) {
        if (bool == true) { pageStack.push(minerPageDetails); }
        if (bool == false) { pageStack.push(minerPageEmpty); }
    }

    function updateMinerData(shares, confirmed, unconfirmed, estimated) {
        minerPageDetails.updateMinerData(shares, confirmed, unconfirmed, estimated);
        pageStack.push(minerPageDetails);
    }

    PageStack {
        id: pageStack

        anchors.fill: parent

        MinerPageEmpty {
            id: minerPageEmpty

            anchors.fill: parent

            onSettingsButtonClicked:  settingsClicked();

        }

        MinerPageDetails {
            id: minerPageDetails

            anchors.top: parent.top
            anchors.bottom: parent.bottom
        }

    }

    Component.onCompleted: pageStack.push(minerPageEmpty);

}
