#ifndef BASE_H
#define BASE_H

#include <QWidget>
#include <QMetaObject>
#include <QtDeclarative>
#include <QSettings>
#include <QTimer>
#include <QClipboard>

#include <qmlapplicationviewer.h>
#include <Networking.h>

class Base : public QWidget
{
    Q_OBJECT
public:
    explicit Base(QWidget *parent = 0);

    QmlApplicationViewer viewer;

    QSettings *settings;

    QTimer *generalTimer;

    bool periodicalRefresh;
    int refreshInterval;

    QString miningPoolName;
    QString miningPoolAPIKey;

    QString walletId;
    QString walletAddress;

    QClipboard *clipboard;

    Networking *networking;

signals:

public slots:
    void checkSettings();
    void openSettingsView();

    void loadSettings();
    void saveSettings(bool perRefresh, int refInterval, QString miningPoolName, QString miningAPIKey, bool updMiningStats, bool updTradeStats);
    void reloadSettings();

    void timerUpdate();
    void updateAll();

    void createWallet();
    void checkWallet();

    void copyAddress(QString bitcoinAddress);

    void updateWalletId(QString wallet_Id);
    void updateWalletAddress(QString wallet_address);

    void updateTradeData(QString last, QString high, QString low);
    void updateMinerData(QVariantMap minerData);
    void updateWalletBalance(QString balance);

    void setWalletBalance(QString balance);

    void updateWalletPayment(QString message, QString message_code);

    void sendCoins(QString address, QString amount);

    void updateDone();

};

#endif // BASE_H
