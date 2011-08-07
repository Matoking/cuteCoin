#include "MinerParse.h"

MinerParse::MinerParse()
{
}

QVariantMap MinerParse::parse(QString poolName, QVariantMap data)
{

    QVariantMap replyMap;

    if (poolName == "BTC Guild")
    {
        int sharesTotal = 0;
        QVariantMap workersMap;

        workersMap = data.value("workers").toMap();

        int workerNumber = 1;

        while (true)
        {
            QVariantMap workerMap;
            if (workersMap.value(QString("%1").arg(workerNumber)).isNull()) break;
            workerMap = workersMap.value(QString("%1").arg(workerNumber)).toMap();

            sharesTotal += workerMap.value("reset_shares").toInt();

            workerNumber++;
        }

        QVariantMap userMap;
        userMap = data.value("user").toMap();

        replyMap["SHARES"] = sharesTotal;
        replyMap["ESTIMATED_EARNINGS"] = userMap.value("estimated_rewards").toString();
        replyMap["UNCONFIRMED_EARNINGS"] = userMap.value("unconfirmed_rewards").toString();
        replyMap["CONFIRMED_EARNINGS"] = userMap.value("confirmed_rewards").toString();

    }

    else if (poolName == "Mt. Red")
    {
        replyMap["SHARES"] = data.value("rsolved").toString();
        replyMap["ESTIMATED_EARNINGS"] = "N/A";
        replyMap["UNCONFIRMED_EARNINGS"] = "N/A";
        replyMap["CONFIRMED_EARNINGS"] = data.value("balance").toString();
    }

    else if (poolName == "deepbit")
    {
        replyMap["SHARES"] = "N/A";
        replyMap["ESTIMATED_EARNINGS"] = "N/A";
        replyMap["UNCONFIRMED_EARNINGS"] = "N/A";
        replyMap["CONFIRMED_EARNINGS"] = data.value("confirmed_reward").toString();
    }

    else if (poolName == "slush's pool")
    {
        replyMap["SHARES"] = "N/A";
        replyMap["ESTIMATED_EARNINGS"] = data.value("estimated_reward").toString();
        replyMap["UNCONFIRMED_EARNINGS"] = data.value("unconfirmed_reward").toString();
        replyMap["CONFIRMED_EARNINGS"] = data.value("confirmed_reward").toString();
    }

    return replyMap;
}
