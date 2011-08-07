#include "Base.h"
#include <QtGui/QApplication>

Base::Base(QWidget *parent) :
    QWidget(parent)
{
    QCoreApplication::setApplicationName(QString("cuteCoin"));
    QCoreApplication::setOrganizationName(QString("Matoking"));
    settings = new QSettings(this);

    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/cuteCoin/symbian/Main_Symbian.qml"));
    viewer.showExpanded();

    // Make this object visible to the main_symbian.qml
    viewer.rootContext()->setContextProperty("base", this);

    clipboard = QApplication::clipboard();

    networking = new Networking(this);

    connect(networking, SIGNAL(tradeDataParsed(QString,QString,QString)),
                               this, SLOT(updateTradeData(QString, QString, QString)));
    connect(networking, SIGNAL(minerDataParsed(QVariantMap)), this, SLOT(updateMinerData(QVariantMap)));
    connect(networking, SIGNAL(updateCompleted()), this, SLOT(updateDone()));

    connect(networking, SIGNAL(walletIdCreated(QString)), this, SLOT(updateWalletId(QString)));
    connect(networking, SIGNAL(walletAddressCreated(QString)), this, SLOT(updateWalletAddress(QString)));
    connect(networking, SIGNAL(walletBalanceUpdated(QString)), this, SLOT(updateWalletBalance(QString)));
    connect(networking, SIGNAL(walletPaymentDone(QString, QString)), this, SLOT(updateWalletPayment(QString, QString)));

    generalTimer = new QTimer(this);
    connect(generalTimer, SIGNAL(timeout()), this, SLOT(timerUpdate()));

    checkSettings();
    loadSettings();

    checkWallet();

}

void Base::copyAddress(QString bitcoinAddress)
{
    clipboard->setText(bitcoinAddress);
    return;
}

void Base::timerUpdate()
{
    if (periodicalRefresh == true) updateAll();
}

void Base::updateAll()
{
    qDebug("Refreshing...");
    networking->updateWallet();
}

void Base::checkWallet()
{
    if (walletId != "N/A")
    {
        //QMetaObject::invokeMethod(viewer.rootObject(), "updateWallet", Q_ARG(QVariant, settings->value("wallet/wallet_01/address").toString()),
        //                          Q_ARG(QVariant, settings->value("wallet/wallet_01/lastBalance")));
        setWalletBalance(settings->value("wallet/wallet_01/lastBalance").toString());
        return;
    }
}

void Base::setWalletBalance(QString balance)
{
    qDebug("Wallet balance updated: " + balance.toAscii());
    QMetaObject::invokeMethod(viewer.rootObject(), "updateWallet", Q_ARG(QVariant, settings->value("wallet/wallet_01/address").toString()),
                              Q_ARG(QVariant, balance));
}

void Base::updateWalletBalance(QString balance)
{
    settings->setValue("wallet/wallet_01/lastBalance", balance);
    setWalletBalance(balance);
    return;
}

void Base::sendCoins(QString address, QString amount)
{
    networking->sendCoins(address, amount);
    return;
}

void Base::updateWalletPayment(QString message, QString message_code)
{
    if (message == "PARSE_FAIL")
    {
        QMetaObject::invokeMethod(viewer.rootObject(), "showPaymentError",
                                  Q_ARG(QVariant, QString("Failed to parse payment response data!")));
        return;
    }
    else if (message_code != "0")
    {
        QMetaObject::invokeMethod(viewer.rootObject(), "showPaymentError",
                                  Q_ARG(QVariant, QString(message)));
        return;
    }
    else if (message_code == "0")
    {
        QMetaObject::invokeMethod(viewer.rootObject(), "showPaymentSuccess",
                                  Q_ARG(QVariant, QString(message)));
        reloadSettings();
        return;
    }
}

void Base::createWallet()
{
    networking->createWallet("Instawallet");
}

void Base::updateWalletId(QString wallet_Id)
{
    walletId = wallet_Id;
}

void Base::updateWalletAddress(QString wallet_address)
{
    walletAddress = wallet_address;

    if (walletId.isNull() || walletId == "N/A")
    {
        qDebug("Wallet creation failed!");
    }
    else {
        qDebug("Wallet id : " + walletId.toAscii() + " - Wallet address : " + walletAddress.toAscii());
        settings->setValue("wallet/wallet_01/ID", walletId);
        settings->setValue("wallet/wallet_01/provider", "Instawallet");
        settings->setValue("wallet/wallet_01/address", walletAddress);

        reloadSettings();
        checkWallet();
    }
}

void Base::updateMinerData(QVariantMap minerData)
{
    if (minerData.value("SHARES").isNull()) return;

    QMetaObject::invokeMethod(viewer.rootObject(), "updateMinerData",
                              Q_ARG(QVariant, minerData.value("SHARES").toString()),
                              Q_ARG(QVariant, minerData.value("CONFIRMED_EARNINGS").toString()),
                              Q_ARG(QVariant, minerData.value("UNCONFIRMED_EARNINGS").toString()),
                              Q_ARG(QVariant, minerData.value("ESTIMATED_EARNINGS").toString()));
    return;
}

void Base::updateTradeData(QString last, QString high, QString low)
{
    QMetaObject::invokeMethod(viewer.rootObject(), "updateTradeData",
                              Q_ARG(QVariant, last), Q_ARG(QVariant, high), Q_ARG(QVariant, low));
    return;
}

void Base::updateDone() {
    networking->updating = false;
    QMetaObject::invokeMethod(viewer.rootObject(), "showUpdatePopup");
    return;
}
void Base::openSettingsView() {
    QMetaObject::invokeMethod(viewer.rootObject(), "showSettings");
    return;
}

void Base::saveSettings(bool perRefresh, int refInterval, QString miningPoolName, QString miningAPIKey, bool updMiningStats, bool updTradeStats)
{
    settings->setValue("generalSettings/periodicalRefresh", perRefresh);
    settings->setValue("generalSettings/refreshInterval", refInterval);
    settings->setValue("miningPool/poolName", miningPoolName);
    settings->setValue("miningPool/apiKey", miningAPIKey);
    settings->setValue("generalSettings/updateMiningStats", updMiningStats);
    settings->setValue("generalSettings/updateTradeStats", updTradeStats);
    settings->sync();
    qDebug("Settings saved");

    reloadSettings();

    return;
}

void Base::reloadSettings()
{
    periodicalRefresh = settings->value("generalSettings/periodicalRefresh").toBool();
    refreshInterval = settings->value("generalSettings/refreshInterval").toInt();

    int interval = refreshInterval * 60 * 1000;
    generalTimer->start(interval);

    miningPoolName = settings->value("miningPool/poolName").toString();
    miningPoolAPIKey = settings->value("miningPool/apiKey").toString();

    networking->miningPoolName = settings->value("miningPool/poolName").toString();
    networking->miningPoolAPIKey = settings->value("miningPool/apiKey").toString();

    networking->updateMinerStats = settings->value("generalSettings/updateMiningStats").toBool();
    networking->updateTradeStats = settings->value("generalSettings/updateTradeStats").toBool();

    walletId = settings->value("wallet/wallet_01/ID").toString();
    walletAddress = settings->value("wallet/wallet_01_address").toString();

    networking->walletId = walletId;

}

void Base::loadSettings()
{
    QMetaObject::invokeMethod(viewer.rootObject(), "loadSettings",
                              Q_ARG(QVariant, settings->value("generalSettings/periodicalRefresh")),
                              Q_ARG(QVariant, settings->value("generalSettings/refreshInterval")),
                              Q_ARG(QVariant, settings->value("miningPool/poolName")),
                              Q_ARG(QVariant, settings->value("miningPool/apiKey")),
                              Q_ARG(QVariant, settings->value("generalSettings/updateMiningStats")),
                              Q_ARG(QVariant, settings->value("generalSettings/updateTradeStats")));

    reloadSettings();
}

void Base::checkSettings()
{
    if (settings->contains("main/settingsFileCreated") == false)
    {
        qDebug("Settings file created.");
        settings->setValue("main/settingsFileCreated", true);
        settings->setValue("main/version", "0.5");

        settings->setValue("generalSettings/periodicalRefresh", true);
        settings->setValue("generalSettings/refreshInterval", 5);
        settings->setValue("generalSettings/updateMiningStats", true);
        settings->setValue("generalSettings/updateTradeStats", true);

        settings->setValue("wallet/wallet_01/ID", "N/A");
        settings->setValue("wallet/wallet_01/provider", "N/A");
        settings->setValue("wallet/wallet_01/address", "N/A");
        settings->setValue("wallet/wallet_01/lastBalance", "0");

        settings->setValue("miningPool/apiKey", "N/A");
        settings->setValue("miningPool/poolName", "N/A");

        settings->sync();
    }
}
