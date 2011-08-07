#include "Networking.h"

Networking::Networking(QObject *parent) :
    QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
    networkWalletManager = new QNetworkAccessManager(this);
    networkPaymentManager = new QNetworkAccessManager(this);

    updating = false;
}

void Networking::updateWallet()
{
    qDebug("Updating wallet balance...");

    updating = true;

    QString walletRequest;
    walletRequest = QString("https://www.instawallet.org/api/v1/w/%1/balance").arg(walletId);

    networkWalletManager->get(QNetworkRequest(QUrl(walletRequest)))->ignoreSslErrors();

    connect(networkWalletManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(walletBalanceLoaded(QNetworkReply*)));

    updateMinerData();
}

void Networking::sendCoins(QString address, QString amount)
{
    QString sendRequest;
    sendRequest = QString("https://www.instawallet.org/api/v1/w/%1/payment").arg(walletId);

    updating = true;

    QByteArray data;
    QUrl parameters;

    double convertedAmount;

    long long convertedLongAmount;

    QString stringAmount;

    convertedAmount = amount.toDouble();
    convertedLongAmount = convertedAmount * 1e8 + (convertedAmount < 0.0 ? -.5 : .5);

    stringAmount = QString("%1").arg(convertedLongAmount);

    qDebug("Amount converted to Satoshis: " + stringAmount.toAscii());

    parameters.addQueryItem("address", address);
    parameters.addQueryItem("amount", stringAmount);
    data.append(parameters.toString());
    data.remove(0, 1);

    networkPaymentManager->post(QNetworkRequest(QUrl(sendRequest)), data)->ignoreSslErrors();

    connect(networkPaymentManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(walletPaymentLoaded(QNetworkReply*)));
}

void Networking::createWallet(QString provider)
{
    qDebug("Creating a wallet...");

    updating = true;

    QString postRequest;
    QByteArray dummyData;
    postRequest = "https://www.instawallet.org/api/v1/new_wallet";

    if (provider == "Instawallet")
    {
        networkWalletManager->post(QNetworkRequest(QUrl(postRequest)), dummyData)->ignoreSslErrors();

        connect(networkWalletManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(walletCreated(QNetworkReply*)));
    }

}

void Networking::walletPaymentLoaded(QNetworkReply *reply)
{
    QByteArray replyBytes = reply->readAll();
    QString replyString = QString::fromUtf8(replyBytes);

    QVariantMap replyMap;
    bool parseSuccess;
    bool walletSuccess;

    parseSuccess = false;
    walletSuccess = false;

    replyMap = Json::parse(replyString, parseSuccess).toMap();

    if (parseSuccess == false)
    {
        qDebug("Failed to parse payment data!");
        qDebug("REPLY: " + replyString.toAscii());
        disconnect(networkPaymentManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(walletPaymentLoaded(QNetworkReply*)));
        walletPaymentDone("PARSE_FAIL", "FAIL");
        updating = false;
        return;
    }

    walletSuccess = replyMap.value("successful").toBool();

    if (walletSuccess == true)
    {
        qDebug("Wallet payment successful!");
        qDebug("REPLY: " + replyString.toAscii());

        walletPaymentDone(replyMap.value("message").toString(), "0");

        updating = false;

        disconnect(networkPaymentManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(walletPaymentLoaded(QNetworkReply*)));
        return;
    }

    if (walletSuccess == false)
    {
        qDebug("Wallet payment failed!");
        qDebug("REPLY: " + replyString.toAscii());

        walletPaymentDone(replyMap.value("message").toString(), replyMap.value("message_code").toString());

        updating = false;

        disconnect(networkPaymentManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(walletPaymentLoaded(QNetworkReply*)));
        return;
    }

    reply->deleteLater();

    disconnect(networkPaymentManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(walletPaymentLoaded(QNetworkReply*)));

}

void Networking::walletBalanceLoaded(QNetworkReply *reply)
{
    QByteArray replyBytes = reply->readAll();
    QString replyString = QString::fromUtf8(replyBytes);

    QVariantMap replyMap;
    bool parseSuccess;
    bool walletSuccess;

    replyMap = Json::parse(replyString, parseSuccess).toMap();

    if (!parseSuccess)
    {
        qDebug("Failed to parse wallet balance data!");
        qDebug("REPLY: " + replyString.toAscii());
        updating = false;
        disconnect(networkWalletManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(walletBalanceLoaded(QNetworkReply*)));
        return;
    }

    walletSuccess = replyMap.value("successful").toBool();

    if (walletSuccess == true)
    {
        QString balanceString;
        double balance;
        long long balanceLong;

        balanceLong = replyMap.value("balance").toLongLong();
        balance = balanceLong / 1e8;

        balanceString = QString("%1").arg(balance);
        qDebug("Balance converted to: " + balanceString.toAscii());
        qDebug("Wallet balance updated!");
        qDebug("REPLY: " + replyString.toAscii());

        walletBalanceUpdated(balanceString);
    }

    disconnect(networkWalletManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(walletBalanceLoaded(QNetworkReply*)));
}

void Networking::walletCreated(QNetworkReply *reply)
{
    QByteArray replyBytes = reply->readAll();
    QString replyString = QString::fromUtf8(replyBytes);
    qDebug("REPLY: " + replyString.toAscii());

    QVariantMap replyMap;

    bool parseSuccess;
    bool walletSuccess;

    replyMap = Json::parse(replyString, parseSuccess).toMap();

    if (!parseSuccess)
        {
            disconnect(networkWalletManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(walletCreated(QNetworkReply*)));
            qDebug("Failed to parse wallet data.");
            qDebug("REPLY: " + replyString.toAscii());
            return;
        }

    walletSuccess = replyMap.value("successful").toBool();

    if (walletSuccess == true)
    {
        disconnect(networkWalletManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(walletCreated(QNetworkReply*)));
        walletIdCreated(replyMap.value("wallet_id").toString());
        qDebug("Created a wallet successfully!");
        qDebug("REPLY: " + replyString.toAscii());
        getWalletAddress(replyMap.value("wallet_id").toString());
    }

}

void Networking::getWalletAddress(QString walletId)
{
    QString postRequest;
    postRequest = QString("https://www.instawallet.org/api/v1/w/%1/address").arg(walletId);
    networkWalletManager->get(QNetworkRequest(QUrl(postRequest)))->ignoreSslErrors();

    connect(networkWalletManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(walletAddressLoaded(QNetworkReply*)));
}

void Networking::walletAddressLoaded(QNetworkReply *reply)
{
    QByteArray replyBytes = reply->readAll();
    QString replyString = QString::fromUtf8(replyBytes);
    qDebug("REPLY: " + replyString.toAscii());

    QVariantMap replyMap;

    bool parseSuccess;
    bool walletSuccess;

    replyMap = Json::parse(replyString, parseSuccess).toMap();

    if (!parseSuccess)
        {
            disconnect(networkWalletManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(walletAddressLoaded(QNetworkReply*)));
            qDebug("Failed to parse wallet address data.");
            qDebug("REPLY: " + replyString.toAscii());
            updating = false;
            return;
        }

    walletSuccess = replyMap.value("successful").toBool();

    if (walletSuccess == true)
    {
        disconnect(networkWalletManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(walletAddressLoaded(QNetworkReply*)));
        walletAddressCreated(replyMap.value("address").toString());
        qDebug("Wallet address retrieved!");
        qDebug("REPLY: " + replyString.toAscii());
        updating = false;
        return;
    }
}

void Networking::updateMinerData()
{
    if (updateMinerStats == false)
    {
        updateTradeData();
        return;
    }

    if (miningPoolAPIKey.isNull() || miningPoolAPIKey.isEmpty() || miningPoolName.isEmpty())
    {
        updateTradeData();
        return;
    }

    QString requestUrl;

    if (miningPoolName == "BTC Guild") requestUrl = QString("http://www.btcguild.com/api.php?api_key=%1").arg(miningPoolAPIKey);
    else if (miningPoolName == "deepbit") requestUrl = QString("http://deepbit.net/api/%1").arg(miningPoolAPIKey);
    else if (miningPoolName == "slush's pool") requestUrl = QString("http://mining.bitcoin.cz/accounts/profile/json/%1").arg(miningPoolAPIKey);
    else if (miningPoolName == "Mt. Red") requestUrl = QString("https://mtred.com/api/user/key/%1").arg(miningPoolAPIKey);

    networkManager->get(QNetworkRequest(QUrl(requestUrl)))->ignoreSslErrors();

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(minerDataLoaded(QNetworkReply*)));

}

void Networking::updateTradeData()
{
    if (updateTradeStats == false)
    {
        updateCompleted();
        return;
    }


    networkManager->get(QNetworkRequest(QUrl("https://mtgox.com/api/0/data/ticker.php")))->ignoreSslErrors();
    qDebug("GET https://mtgox.com/api/0/data/ticker.php");

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(tradeDataLoaded(QNetworkReply*)));
}

void Networking::minerDataLoaded(QNetworkReply *reply)
{
    QByteArray replyBytes = reply->readAll();
    QString replyString = QString::fromUtf8(replyBytes);
    qDebug("REPLY: " + replyString.toAscii());

    QVariantMap replyMap;

    bool parseSuccess;
    replyMap = Json::parse(replyString, parseSuccess).toMap();

    if (!parseSuccess)
    {
        qDebug("Failed to parse miner data");
        disconnect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(minerDataLoaded(QNetworkReply*)));
        updateTradeData();
        return;
    }

    QVariantMap parsedMap;

    parsedMap = MinerParse::parse(miningPoolName, replyMap);

    minerDataParsed(parsedMap);

    disconnect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(minerDataLoaded(QNetworkReply*)));

    updateTradeData();


}

void Networking::tradeDataLoaded(QNetworkReply *reply)
{
    QByteArray replyBytes = reply->readAll();
    QString replyString = QString::fromUtf8(replyBytes);

    QString lastPrice;
    QString highPrice;
    QString lowPrice;

    qDebug("GET https://mtgox.com/api/0/data/ticker.php DONE!");

    bool parseSuccess;
    QVariantMap tradeData = Json::parse(replyString, parseSuccess).toMap();

    if (!parseSuccess) {
        qDebug("Failed to parse trade data");
        qDebug(QString("Returned : %1").arg(replyString).toAscii());
        return;
    }

    QVariantMap tickerData;
    tickerData = tradeData.value("ticker").toMap();

    lastPrice = tickerData.value("last").toString();
    highPrice = tickerData.value("high").toString();
    lowPrice = tickerData.value("low").toString();

    reply->deleteLater();

    disconnect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(tradeDataLoaded(QNetworkReply*)));

    tradeDataParsed(lastPrice, highPrice, lowPrice);

    updateCompleted();
}
