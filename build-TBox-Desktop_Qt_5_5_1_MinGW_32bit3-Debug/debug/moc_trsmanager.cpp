/****************************************************************************
** Meta object code from reading C++ file 'trsmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TBox/trsmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trsmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TRSManager_t {
    QByteArrayData data[5];
    char stringdata0[33];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TRSManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TRSManager_t qt_meta_stringdata_TRSManager = {
    {
QT_MOC_LITERAL(0, 0, 10), // "TRSManager"
QT_MOC_LITERAL(1, 11, 7), // "RunNext"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 8), // "writeMSG"
QT_MOC_LITERAL(4, 29, 3) // "Run"

    },
    "TRSManager\0RunNext\0\0writeMSG\0Run"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TRSManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    1,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    3,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,

       0        // eod
};

void TRSManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TRSManager *_t = static_cast<TRSManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->RunNext(); break;
        case 1: _t->writeMSG((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->Run((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TRSManager::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TRSManager::RunNext)) {
                *result = 0;
            }
        }
        {
            typedef void (TRSManager::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TRSManager::writeMSG)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject TRSManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TRSManager.data,
      qt_meta_data_TRSManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TRSManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TRSManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TRSManager.stringdata0))
        return static_cast<void*>(const_cast< TRSManager*>(this));
    return QObject::qt_metacast(_clname);
}

int TRSManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void TRSManager::RunNext()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void TRSManager::writeMSG(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
