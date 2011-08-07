#ifndef NETWORKING_H
#define NETWORKING_H

#include <QObject>
#include <QtNetwork>
#include <QByteArray>
#include <QString>

#include <json.h>
#include <MinerParse.h>

class Networking : public QObject
{
    Q_OBJECT
public:
    explicit Networking(QObject *parent = 0);

    QNetworkAccessManager *networkManager;
    QNetworkAccessManager *networkWalletManager;
    QNetworkAccessManager *networkPaymentManager;

    bool updateMinerStats;
    bool updateTradeStats;

    QString miningPoolAPIKey;
    QString miningPoolName;

    bool updating;

    QString walletId;

signals:
    void tradeDataParsed(QString last, QString high, QString low);
    void minerDataParsed(QVariantMap parsedData);

    void walletIdCreated(QString walletId);
    void walletAddressCreated(QString walletAddress);
    void walletBalanceUpdated(QString balance);
    void walletPaymentDone(QString message, QString message_code);

    void updateCompleted();

public slots:
    void updateWallet();
    void updateMinerData();
    void updateTradeData();

    void createWallet(QString provider);
    void walletCreated(QNetworkReply*);
    void walletAddressLoaded(QNetworkReply*);
    void walletBalanceLoaded(QNetworkReply*);
    void walletPaymentLoaded(QNetworkReply*);

    void sendCoins(QString address, QString amount);

    void getWalletAddress(QString walletId);

    void minerDataLoaded(QNetworkReply*);
    void tradeDataLoaded(QNetworkReply*);

};

#endif // NETWORKING_H
