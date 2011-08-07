import QtQuick 1.0
import com.nokia.symbian 1.0

Page {
    id: page

    anchors.top: parent.top
    anchors.bottom: parent.bottom

    property bool perRefresh: true
    property int refInterval: 5

    property bool updMiningStats: true
    property bool updTradeStats: true

    property string miningPool: "N/A"
    property string miningPoolAPIKey: "N/A"

    signal settingsSaved(bool s_perRefresh, int s_refInterval, string s_miningPool, string s_miningPoolAPIKey,
                         bool s_updMiningStats, bool s_updTradeStats);

    function saveSettings() { settingsSaved(perRefresh, refInterval, miningPool, miningPoolAPIKey, updMiningStats, updTradeStats); }

    function setSettings() {
        generalListModel.setProperty(0, "selected", perRefresh);
        generalListModel.setProperty(1, "selected", updMiningStats);
        generalListModel.setProperty(2, "selected", updTradeStats);

        intervalSlider.value = refInterval;

        if (miningPool == "slush's pool") { miningPoolDialog.selectedIndex = 0; }
        else if (miningPool == "deepbit") { miningPoolDialog.selectedIndex = 1; }
        else if (miningPool == "BTC Guild") { miningPoolDialog.selectedIndex = 2; }
        else if (miningPool == "Mt. Red") { miningPoolDialog.selectedIndex = 3; }

        if (miningPoolAPIKey != "N/A") { miningPoolTextfield.text = miningPoolAPIKey; }

        return;
    }

    function setLoadedSettings(l_perRefresh, l_refInterval, l_miningPool, l_miningPoolAPIKey, l_updMiningStats, l_updTradeStats) {
        perRefresh = l_perRefresh;
        refInterval = l_refInterval;
        miningPool = l_miningPool;
        miningPoolAPIKey = l_miningPoolAPIKey;
        updMiningStats = l_updMiningStats;
        updTradeStats = l_updTradeStats;
        setSettings();
        return;
    }

    function changeSettings() {
        miningPool = miningPoolDialogItem.title;
        miningPoolAPIKey = miningPoolTextfield.text;
    }

    function settingChanged(variable, value) {
        if (variable == "perRefresh") perRefresh = value;
        if (variable == "refInterval") refInterval = value;
        if (variable == "updMiningStats") updMiningStats = value;
        if (variable == "updTradeStats") updTradeStats = value;
        else { return; }
    }

    Flickable {
        id: flickable

        width: parent.width
        height: parent.height

        anchors.top: parent.top

        clip: true

        contentHeight: 600

        ListHeading {
            id: generalHeading

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top

            ListItemText {
                text: " General Settings"
                anchors.fill: generalHeading
                role: "Title"
            }
        }

        ListView {
            id: generalListView
            anchors.top: generalHeading.bottom
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right

            clip: true
            interactive: false

            model: generalListModel
            delegate: generalListDelegate

        }

        ListModel {
            id: generalListModel

            function setChecked(index, dict, variable) {
                if (index === 0 && variable == "general") settingChanged("perRefresh", dict);
                if (index === 1 && variable == "general") settingChanged("updMiningStats", dict);
                if (index === 2 && variable == "general") settingChanged("updTradeStats", dict);
                else { return; }
            }

            ListElement {
                name: "Refresh periodically"
                role: "Title"
                selected: true
            }

            ListElement {
                name: "Update mining pool statistics"
                role: "Title"
                selected: true
            }

            ListElement {
                name: "Update Bitcoin exchange prices"
                role: "Title"
                selected: true
            }
        }

        Text {
            id :intervalSliderText

            y: 250

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right

            text: "Refresh interval (min)"
            color: "white"
            font.pointSize: 7.5
        }

        Slider {
            id: intervalSlider

            anchors.top: intervalSliderText.bottom
            anchors.left: parent.left
            anchors.right: parent.right

            stepSize: 1
            minimumValue: 1
            value: 5
            maximumValue: 60
            valueIndicatorVisible: true

            onValueChanged: valueChanged(value);

            function valueChanged(newValue) { settingChanged("refInterval", newValue); }
        }

        ListHeading {
            id: miningPoolHeading

            anchors.left: parent.left
            anchors.right: parent.right

            anchors.top: intervalSlider.bottom
            anchors.topMargin: 10

            ListItemText {
                text: " Mining Pool Settings"
                anchors.fill: miningPoolHeading
                role: "Title"
            }
        }

        Text {
            id :miningPoolNameText

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right

            anchors.top: miningPoolHeading.bottom
            anchors.topMargin: 10

            text: "Mining pool"
            color: "white"
            font.pointSize: 7.5
        }

        SelectionListItem {
            id: miningPoolDialogItem

            anchors.top: miningPoolNameText.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.right: parent.right

            title: miningPoolDialog.selectedIndex >= 0
                   ? miningPoolDialog.model.get(miningPoolDialog.selectedIndex).name
                   : "Please select"

            onClicked: miningPoolDialog.open()

            SelectionDialog {
                id: miningPoolDialog
                titleText: "Select a mining pool"
                selectedIndex: -1
                model: ListModel {
                    ListElement { name: "slush's pool" }
                    ListElement { name: "deepbit" }
                    ListElement { name: "BTC Guild" }
                    ListElement { name: "Mt. Red" }
                }
            }
        }

        Text {
            id: miningPoolAPIText

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right

            anchors.top: miningPoolDialogItem.bottom
            anchors.topMargin: 10

            text: "Mining pool API key"
            color: "white"
            font.pointSize: 7.5

            TextField {
                id: miningPoolTextfield

                anchors.top: miningPoolAPIText.bottom
                anchors.topMargin: 10

                anchors.left: parent.left
                anchors.right: parent.right
                anchors.rightMargin: 10

                placeholderText: "Enter API key here"
            }

            Button {
                id: miningPoolPasteButton

                anchors.bottom: miningPoolTextfield.top
                anchors.right: miningPoolTextfield.right
                width: parent.width / 4

                text: "Paste"

                onClicked: pasteApiKey();

                function pasteApiKey() {
                    miningPoolTextfield.text = "";
                    miningPoolTextfield.paste();
                }
            }
        }

    }

    Component {
        id: generalListDelegate

        ListItem {
            id: generalListItem

            // The texts to display
            Column {
                anchors {
                    left:  generalListItem.paddingItem.left
                    top: generalListItem.paddingItem.top
                    bottom: generalListItem.paddingItem.bottom
                    right: generalCheckbox.left
                }

                ListItemText {
                    mode: generalListItem.mode
                    role: "Title"
                    text: name // Title text is from the 'name' property in the model item (ListElement)
                    width: parent.width
                }
            }

            // The checkbox to display
            CheckBox {
                id: generalCheckbox
                checked: selected  // Checked state is from the 'selected' property in the model item
                anchors { right: generalListItem.paddingItem.right; verticalCenter: generalListItem.verticalCenter }
                onClicked: generalListModel.setChecked(index, generalCheckbox.checked, "general");
            }
        }
    }
}
