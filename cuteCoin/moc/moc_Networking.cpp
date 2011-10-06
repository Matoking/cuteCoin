/****************************************************************************
** Meta object code from reading C++ file 'Networking.h'
**
** Created: Sun 7. Aug 21:13:42 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Networking.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Networking.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Networking[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      26,   12,   11,   11, 0x05,
      78,   67,   11,   11, 0x05,
     116,  107,   11,   11, 0x05,
     155,  141,   11,   11, 0x05,
     193,  185,   11,   11, 0x05,
     244,  223,   11,   11, 0x05,
     279,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     297,   11,   11,   11, 0x0a,
     312,   11,   11,   11, 0x0a,
     330,   11,   11,   11, 0x0a,
     357,  348,   11,   11, 0x0a,
     379,   11,   11,   11, 0x0a,
     409,   11,   11,   11, 0x0a,
     445,   11,   11,   11, 0x0a,
     481,   11,   11,   11, 0x0a,
     532,  517,   11,   11, 0x0a,
     559,  107,   11,   11, 0x0a,
     585,   11,   11,   11, 0x0a,
     617,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Networking[] = {
    "Networking\0\0last,high,low\0"
    "tradeDataParsed(QString,QString,QString)\0"
    "parsedData\0minerDataParsed(QVariantMap)\0"
    "walletId\0walletIdCreated(QString)\0"
    "walletAddress\0walletAddressCreated(QString)\0"
    "balance\0walletBalanceUpdated(QString)\0"
    "message,message_code\0"
    "walletPaymentDone(QString,QString)\0"
    "updateCompleted()\0updateWallet()\0"
    "updateMinerData()\0updateTradeData()\0"
    "provider\0createWallet(QString)\0"
    "walletCreated(QNetworkReply*)\0"
    "walletAddressLoaded(QNetworkReply*)\0"
    "walletBalanceLoaded(QNetworkReply*)\0"
    "walletPaymentLoaded(QNetworkReply*)\0"
    "address,amount\0sendCoins(QString,QString)\0"
    "getWalletAddress(QString)\0"
    "minerDataLoaded(QNetworkReply*)\0"
    "tradeDataLoaded(QNetworkReply*)\0"
};

const QMetaObject Networking::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Networking,
      qt_meta_data_Networking, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Networking::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Networking::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Networking::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Networking))
        return static_cast<void*>(const_cast< Networking*>(this));
    return QObject::qt_metacast(_clname);
}

int Networking::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tradeDataParsed((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: minerDataParsed((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 2: walletIdCreated((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: walletAddressCreated((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: walletBalanceUpdated((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: walletPaymentDone((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: updateCompleted(); break;
        case 7: updateWallet(); break;
        case 8: updateMinerData(); break;
        case 9: updateTradeData(); break;
        case 10: createWallet((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: walletCreated((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 12: walletAddressLoaded((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 13: walletBalanceLoaded((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 14: walletPaymentLoaded((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 15: sendCoins((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 16: getWalletAddress((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: minerDataLoaded((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 18: tradeDataLoaded((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void Networking::tradeDataParsed(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Networking::minerDataParsed(QVariantMap _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Networking::walletIdCreated(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Networking::walletAddressCreated(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Networking::walletBalanceUpdated(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Networking::walletPaymentDone(QString _t1, QString _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Networking::updateCompleted()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}
QT_END_MOC_NAMESPACE
