/****************************************************************************
** Meta object code from reading C++ file 'database.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtTRS/database.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'database.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DataBase_t {
    QByteArrayData data[9];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataBase_t qt_meta_stringdata_DataBase = {
    {
QT_MOC_LITERAL(0, 0, 8), // "DataBase"
QT_MOC_LITERAL(1, 9, 5), // "getID"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 3), // "ind"
QT_MOC_LITERAL(4, 20, 11), // "getTestName"
QT_MOC_LITERAL(5, 32, 10), // "getTestDay"
QT_MOC_LITERAL(6, 43, 12), // "getTestMonth"
QT_MOC_LITERAL(7, 56, 11), // "getTestYear"
QT_MOC_LITERAL(8, 68, 13) // "getTestPassed"

    },
    "DataBase\0getID\0\0ind\0getTestName\0"
    "getTestDay\0getTestMonth\0getTestYear\0"
    "getTestPassed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataBase[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x02 /* Public */,
       4,    1,   47,    2, 0x02 /* Public */,
       5,    1,   50,    2, 0x02 /* Public */,
       6,    1,   53,    2, 0x02 /* Public */,
       7,    1,   56,    2, 0x02 /* Public */,
       8,    1,   59,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::QString, QMetaType::Int,    3,
    QMetaType::QString, QMetaType::Int,    3,
    QMetaType::QString, QMetaType::Int,    3,
    QMetaType::QString, QMetaType::Int,    3,
    QMetaType::QString, QMetaType::Int,    3,
    QMetaType::QString, QMetaType::Int,    3,

       0        // eod
};

void DataBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DataBase *_t = static_cast<DataBase *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QString _r = _t->getID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: { QString _r = _t->getTestName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: { QString _r = _t->getTestDay((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 3: { QString _r = _t->getTestMonth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 4: { QString _r = _t->getTestYear((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 5: { QString _r = _t->getTestPassed((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject DataBase::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DataBase.data,
      qt_meta_data_DataBase,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DataBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataBase::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DataBase.stringdata0))
        return static_cast<void*>(const_cast< DataBase*>(this));
    return QObject::qt_metacast(_clname);
}

int DataBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
