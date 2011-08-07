#ifndef MINERPARSE_H
#define MINERPARSE_H

#include <QVariantMap>
#include <QString>

#include <QDebug>

class MinerParse
{
public:
    MinerParse();

    static QVariantMap parse(QString poolName, QVariantMap data);
};

#endif // MINERPARSE_H
