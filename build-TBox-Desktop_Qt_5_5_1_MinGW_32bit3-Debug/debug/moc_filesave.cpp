/****************************************************************************
** Meta object code from reading C++ file 'filesave.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TBox/filesave.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filesave.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FileSaveDialog_t {
    QByteArrayData data[18];
    char stringdata0[176];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileSaveDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileSaveDialog_t qt_meta_stringdata_FileSaveDialog = {
    {
QT_MOC_LITERAL(0, 0, 14), // "FileSaveDialog"
QT_MOC_LITERAL(1, 15, 14), // "fileUrlChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 15), // "filenameChanged"
QT_MOC_LITERAL(4, 47, 12), // "titleChanged"
QT_MOC_LITERAL(5, 60, 18), // "nameFiltersChanged"
QT_MOC_LITERAL(6, 79, 8), // "accepted"
QT_MOC_LITERAL(7, 88, 8), // "rejected"
QT_MOC_LITERAL(8, 97, 12), // "validChanged"
QT_MOC_LITERAL(9, 110, 6), // "accept"
QT_MOC_LITERAL(10, 117, 6), // "reject"
QT_MOC_LITERAL(11, 124, 4), // "open"
QT_MOC_LITERAL(12, 129, 5), // "close"
QT_MOC_LITERAL(13, 135, 5), // "valid"
QT_MOC_LITERAL(14, 141, 7), // "fileUrl"
QT_MOC_LITERAL(15, 149, 8), // "filename"
QT_MOC_LITERAL(16, 158, 5), // "title"
QT_MOC_LITERAL(17, 164, 11) // "nameFilters"

    },
    "FileSaveDialog\0fileUrlChanged\0\0"
    "filenameChanged\0titleChanged\0"
    "nameFiltersChanged\0accepted\0rejected\0"
    "validChanged\0accept\0reject\0open\0close\0"
    "valid\0fileUrl\0filename\0title\0nameFilters"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileSaveDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       5,   80, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    0,   71,    2, 0x06 /* Public */,
       5,    0,   72,    2, 0x06 /* Public */,
       6,    0,   73,    2, 0x06 /* Public */,
       7,    0,   74,    2, 0x06 /* Public */,
       8,    0,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   76,    2, 0x09 /* Protected */,
      10,    0,   77,    2, 0x09 /* Protected */,

 // methods: name, argc, parameters, tag, flags
      11,    0,   78,    2, 0x02 /* Public */,
      12,    0,   79,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      13, QMetaType::Bool, 0x00495001,
      14, QMetaType::QUrl, 0x00495001,
      15, QMetaType::QString, 0x00495103,
      16, QMetaType::QString, 0x00495103,
      17, QMetaType::QStringList, 0x00495103,

 // properties: notify_signal_id
       6,
       0,
       1,
       2,
       3,

       0        // eod
};

void FileSaveDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FileSaveDialog *_t = static_cast<FileSaveDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->fileUrlChanged(); break;
        case 1: _t->filenameChanged(); break;
        case 2: _t->titleChanged(); break;
        case 3: _t->nameFiltersChanged(); break;
        case 4: _t->accepted(); break;
        case 5: _t->rejected(); break;
        case 6: _t->validChanged(); break;
        case 7: _t->accept(); break;
        case 8: _t->reject(); break;
        case 9: _t->open(); break;
        case 10: _t->close(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FileSaveDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FileSaveDialog::fileUrlChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (FileSaveDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FileSaveDialog::filenameChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (FileSaveDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FileSaveDialog::titleChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (FileSaveDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FileSaveDialog::nameFiltersChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (FileSaveDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FileSaveDialog::accepted)) {
                *result = 4;
            }
        }
        {
            typedef void (FileSaveDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FileSaveDialog::rejected)) {
                *result = 5;
            }
        }
        {
            typedef void (FileSaveDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FileSaveDialog::validChanged)) {
                *result = 6;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        FileSaveDialog *_t = static_cast<FileSaveDialog *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->valid(); break;
        case 1: *reinterpret_cast< QUrl*>(_v) = _t->fileUrl(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->filename(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->title(); break;
        case 4: *reinterpret_cast< QStringList*>(_v) = _t->nameFilters(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        FileSaveDialog *_t = static_cast<FileSaveDialog *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 2: _t->setFilename(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setTitle(*reinterpret_cast< QString*>(_v)); break;
        case 4: _t->setNameFilters(*reinterpret_cast< QStringList*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_a);
}

const QMetaObject FileSaveDialog::staticMetaObject = {
    { &QQuickItem::staticMetaObject, qt_meta_stringdata_FileSaveDialog.data,
      qt_meta_data_FileSaveDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FileSaveDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileSaveDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FileSaveDialog.stringdata0))
        return static_cast<void*>(const_cast< FileSaveDialog*>(this));
    return QQuickItem::qt_metacast(_clname);
}

int FileSaveDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void FileSaveDialog::fileUrlChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void FileSaveDialog::filenameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void FileSaveDialog::titleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void FileSaveDialog::nameFiltersChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void FileSaveDialog::accepted()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void FileSaveDialog::rejected()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void FileSaveDialog::validChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
