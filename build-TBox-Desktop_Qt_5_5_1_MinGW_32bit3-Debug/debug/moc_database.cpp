/****************************************************************************
** Meta object code from reading C++ file 'database.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TBox/database.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'database.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DataBase_t {
    QByteArrayData data[23];
    char stringdata0[222];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataBase_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataBase_t qt_meta_stringdata_DataBase = {
    {
QT_MOC_LITERAL(0, 0, 8), // "DataBase"
QT_MOC_LITERAL(1, 9, 11), // "DateChanged"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 14), // "EndDateChanged"
QT_MOC_LITERAL(4, 37, 14), // "get_seesion_db"
QT_MOC_LITERAL(5, 52, 5), // "start"
QT_MOC_LITERAL(6, 58, 3), // "end"
QT_MOC_LITERAL(7, 62, 10), // "getDateQML"
QT_MOC_LITERAL(8, 73, 10), // "setDateQML"
QT_MOC_LITERAL(9, 84, 8), // "QString&"
QT_MOC_LITERAL(10, 93, 3), // "arg"
QT_MOC_LITERAL(11, 97, 11), // "get_EndDate"
QT_MOC_LITERAL(12, 109, 13), // "setEndDateQML"
QT_MOC_LITERAL(13, 123, 10), // "ParseDateS"
QT_MOC_LITERAL(14, 134, 4), // "data"
QT_MOC_LITERAL(15, 139, 10), // "ParseDateE"
QT_MOC_LITERAL(16, 150, 5), // "getID"
QT_MOC_LITERAL(17, 156, 3), // "ind"
QT_MOC_LITERAL(18, 160, 11), // "getTestName"
QT_MOC_LITERAL(19, 172, 10), // "getTestDay"
QT_MOC_LITERAL(20, 183, 12), // "getTestMonth"
QT_MOC_LITERAL(21, 196, 11), // "getTestYear"
QT_MOC_LITERAL(22, 208, 13) // "getTestPassed"

    },
    "DataBase\0DateChanged\0\0EndDateChanged\0"
    "get_seesion_db\0start\0end\0getDateQML\0"
    "setDateQML\0QString&\0arg\0get_EndDate\0"
    "setEndDateQML\0ParseDateS\0data\0ParseDateE\0"
    "getID\0ind\0getTestName\0getTestDay\0"
    "getTestMonth\0getTestYear\0getTestPassed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataBase[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       2,  128, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,
       3,    0,   90,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   91,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       7,    0,   96,    2, 0x02 /* Public */,
       8,    1,   97,    2, 0x02 /* Public */,
      11,    0,  100,    2, 0x02 /* Public */,
      12,    1,  101,    2, 0x02 /* Public */,
      13,    1,  104,    2, 0x02 /* Public */,
      15,    1,  107,    2, 0x02 /* Public */,
      16,    1,  110,    2, 0x02 /* Public */,
      18,    1,  113,    2, 0x02 /* Public */,
      19,    1,  116,    2, 0x02 /* Public */,
      20,    1,  119,    2, 0x02 /* Public */,
      21,    1,  122,    2, 0x02 /* Public */,
      22,    1,  125,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::QStringList, QMetaType::QString, QMetaType::QString,    5,    6,

 // methods: parameters
    QMetaType::QString,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::QString,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::QString, QMetaType::QString,   14,
    QMetaType::QString, QMetaType::QString,   14,
    QMetaType::QString, QMetaType::Int,   17,
    QMetaType::QString, QMetaType::Int,   17,
    QMetaType::QString, QMetaType::Int,   17,
    QMetaType::QString, QMetaType::Int,   17,
    QMetaType::QString, QMetaType::Int,   17,
    QMetaType::QString, QMetaType::Int,   17,

 // properties: name, type, flags
       7, QMetaType::QString, 0x00495003,
      11, QMetaType::QString, 0x00495003,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void DataBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DataBase *_t = static_cast<DataBase *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->DateChanged(); break;
        case 1: _t->EndDateChanged(); break;
        case 2: { QStringList _r = _t->get_seesion_db((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QStringList*>(_a[0]) = _r; }  break;
        case 3: { QString _r = _t->getDateQML();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 4: _t->setDateQML((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: { QString _r = _t->get_EndDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 6: _t->setEndDateQML((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: { QString _r = _t->ParseDateS((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 8: { QString _r = _t->ParseDateE((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 9: { QString _r = _t->getID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 10: { QString _r = _t->getTestName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 11: { QString _r = _t->getTestDay((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 12: { QString _r = _t->getTestMonth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 13: { QString _r = _t->getTestYear((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 14: { QString _r = _t->getTestPassed((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DataBase::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataBase::DateChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (DataBase::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DataBase::EndDateChanged)) {
                *result = 1;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        DataBase *_t = static_cast<DataBase *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->getDateQML(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->get_EndDate(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        DataBase *_t = static_cast<DataBase *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setDateQML(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setEndDateQML(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
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
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void DataBase::DateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void DataBase::EndDateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
