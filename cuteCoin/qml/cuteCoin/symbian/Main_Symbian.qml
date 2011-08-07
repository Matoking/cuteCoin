import QtQuick 1.0
import com.nokia.symbian 1.0

Window {
    id: mainWindow
    width: screen.displayWidth
    height: screen.displayHeight

    property int layer: 1

    function loadSettings(l_perRefresh, l_refInterval, l_miningPool, l_miningPoolAPIKey,
                          l_updMiningStats, l_updTradeData) { viewSettings.setLoadedSettings(l_perRefresh,
                                                                                             l_refInterval, l_miningPool,
                                                                                             l_miningPoolAPIKey, l_updMiningStats,
                                                                                             l_updTradeData); }

    StatusBar {
        id: statusBar
        anchors.top: mainWindow.top
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
            id: dialogContent
            text: "Error occured. Try again later."
            font { bold: true; pixelSize: 16; }
            color: "white"
            anchors.fill: parent
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    InfoPopup {
        id: infoBanner
    }

    Menu {
        id: mainMenu
        anchors.top: toolBar.top

        content: MenuLayout {

            MenuItem {
                id: updateNow
                text: "Update now"
                onClicked: base.updateAll();
            }

            MenuItem {
                id: settings
                text: "Settings"
                onClicked: showSettings();
            }
        }
    }

    TabBarLayout {
        id: tabBar
        anchors.top: statusBar.bottom
        width: mainWindow.width

        TabButton {
            id: mainTabButton
            text: "Main"
            onClicked: pageStack.push(mainPage);
        }

        TabButton {
            id: walletTabButton
            text: "Wallet"
            onClicked: pageStack.push(walletPage);
        }

        TabButton {
            id: miningTabButton;
            text: "Mining"
            onClicked: pageStack.push(minerPage);
        }

        TabButton {
            id: tradeTabButton;
            text: "Trade"
            onClicked: pageStack.push(tradePage);
        }

    }

    PageStack {
        id: windowStack
        anchors.top: statusBar.bottom
        anchors.bottom: toolBar.top

        Settings {
            id: viewSettings

            anchors.top: parent.top
            anchors.bottom: parent.bottom

            onSettingsSaved: base.saveSettings(perRefresh, refInterval, miningPool, miningPoolAPIKey, updMiningStats, updTradeStats);
        }
    }

    PageStack {
        id: pageStack
        anchors.top: tabBar.bottom
        anchors.bottom: toolBar.top

        MainPage {
            id: mainPage
            anchors.top: pageStack.top
            anchors.bottom: parent.bottom
        }

        WalletPage {
            id: walletPage
            anchors.top: pageStack.top
            anchors.bottom: parent.bottom

            onCreateWalletClicked: base.createWallet();
            onCopiedAddress: base.copyAddress(btcaddress);
            onSendTransaction: base.sendCoins(address, amount);
        }

        MinerPage {
            id: minerPage
            anchors.top: pageStack.top
            anchors.bottom: parent.bottom

            onSettingsClicked: showSettings();
        }

        TradePage {
            id: tradePage
            anchors.top: pageStack.top
            anchors.bottom: parent.bottom
        }
    }

    ToolBar {
        id: toolBar
        anchors.bottom: mainWindow.bottom

        tools: ToolBarLayout {

            ToolButton {
                iconSource: "toolbar-back"
                onClicked: back();
            }

            ToolButton {
                iconSource: "toolbar-menu"
                onClicked: mainMenu.open();
            }
        }
    }

    Component.onCompleted: {
        pageStack.push(mainPage);
    }

    function updateWallet(address, balance) { walletPage.updateWallet(address, balance); }

    function updateMinerData(shares, confirmed, unconfirmed, estimated) {
        minerPage.updateMinerData(shares, confirmed, unconfirmed, estimated);
    }

    function updateTradeData(last, high, low) { tradePage.updateContent(last, high, low); }
    function showUpdatePopup() { infoBanner.showPopup("ready", "Information updated!"); }

    function showMinerStats(bool) { minerPage.showMinerStats(bool); }

    function showSettings() {
        layer = 2;

        tabBar.enabled = false;
        tabBar.visible = false;
        pageStack.enabled = false;
        pageStack.visible = false;

        windowStack.push(viewSettings);
        windowStack.enabled = true;
        windowStack.visible = true;
    }

    function hideView() {
        layer = 1;

        tabBar.enabled = true;
        tabBar.visible = true;
        pageStack.enabled = true;
        pageStack.visible = true;

        windowStack.clear();
        windowStack.enabled = false;
    }

    function showPaymentError(errorText) {
        dialogContent.text = errorText;
        dialogTitle.text = "Error";
        walletPage.openSendMenu();
        dialog.open();
    }

    function showPaymentSuccess(successText) {
        dialogContent.text = successText;
        dialogTitle.text = "Success";
        walletPage.closeSendMenu();
        dialog.open();
    }

    function back() {
        if (layer == 2) {
            hideView();
            viewSettings.changeSettings();
            viewSettings.saveSettings();
            return;
        }
        else if (layer == 1) Qt.quit();

    }

}
