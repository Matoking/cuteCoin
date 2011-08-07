/****************************************************************************
** Meta object code from reading C++ file 'Base.h'
**
** Created: Sun 7. Aug 18:36:58 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Base.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Base.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Base[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x0a,
      22,    5,    5,    5, 0x0a,
      41,    5,    5,    5, 0x0a,
     136,   56,    5,    5, 0x0a,
     185,    5,    5,    5, 0x0a,
     202,    5,    5,    5, 0x0a,
     216,    5,    5,    5, 0x0a,
     228,    5,    5,    5, 0x0a,
     243,    5,    5,    5, 0x0a,
     272,  257,    5,    5, 0x0a,
     303,  293,    5,    5, 0x0a,
     342,  327,    5,    5, 0x0a,
     385,  371,    5,    5, 0x0a,
     436,  426,    5,    5, 0x0a,
     473,  465,    5,    5, 0x0a,
     502,  465,    5,    5, 0x0a,
     549,  528,    5,    5, 0x0a,
     601,  586,    5,    5, 0x0a,
     628,    5,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Base[] = {
    "Base\0\0checkSettings()\0openSettingsView()\0"
    "loadSettings()\0"
    "perRefresh,refInterval,miningPoolName,miningAPIKey,updMiningStats,updT"
    "radeStats\0"
    "saveSettings(bool,int,QString,QString,bool,bool)\0"
    "reloadSettings()\0timerUpdate()\0"
    "updateAll()\0createWallet()\0checkWallet()\0"
    "bitcoinAddress\0copyAddress(QString)\0"
    "wallet_Id\0updateWalletId(QString)\0"
    "wallet_address\0updateWalletAddress(QString)\0"
    "last,high,low\0updateTradeData(QString,QString,QString)\0"
    "minerData\0updateMinerData(QVariantMap)\0"
    "balance\0updateWalletBalance(QString)\0"
    "setWalletBalance(QString)\0"
    "message,message_code\0"
    "updateWalletPayment(QString,QString)\0"
    "address,amount\0sendCoins(QString,QString)\0"
    "updateDone()\0"
};

const QMetaObject Base::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Base,
      qt_meta_data_Base, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Base::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Base::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Base::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Base))
        return static_cast<void*>(const_cast< Base*>(this));
    return QWidget::qt_metacast(_clname);
}

int Base::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: checkSettings(); break;
        case 1: openSettingsView(); break;
        case 2: loadSettings(); break;
        case 3: saveSettings((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 4: reloadSettings(); break;
        case 5: timerUpdate(); break;
        case 6: updateAll(); break;
        case 7: createWallet(); break;
        case 8: checkWallet(); break;
        case 9: copyAddress((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: updateWalletId((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: updateWalletAddress((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: updateTradeData((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 13: updateMinerData((*reinterpret_cast< QVariantMap(*)>(_a[1]))); break;
        case 14: updateWalletBalance((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 15: setWalletBalance((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: updateWalletPayment((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 17: sendCoins((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 18: updateDone(); break;
        default: ;
        }
        _id -= 19;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
