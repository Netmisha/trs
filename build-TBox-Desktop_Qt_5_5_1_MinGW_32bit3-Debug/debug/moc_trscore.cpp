/****************************************************************************
** Meta object code from reading C++ file 'trscore.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TBox/trscore.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trscore.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TRSCore_t {
    QByteArrayData data[33];
    char stringdata0[306];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TRSCore_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TRSCore_t qt_meta_stringdata_TRSCore = {
    {
QT_MOC_LITERAL(0, 0, 7), // "TRSCore"
QT_MOC_LITERAL(1, 8, 8), // "StartApp"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 8), // "CloseApp"
QT_MOC_LITERAL(4, 27, 8), // "SetOnTop"
QT_MOC_LITERAL(5, 36, 5), // "Sleep"
QT_MOC_LITERAL(6, 42, 14), // "GetScreenWidth"
QT_MOC_LITERAL(7, 57, 15), // "GetScreenHeight"
QT_MOC_LITERAL(8, 73, 14), // "WindowMinimize"
QT_MOC_LITERAL(9, 88, 14), // "WindowMaximize"
QT_MOC_LITERAL(10, 103, 13), // "WindowRestore"
QT_MOC_LITERAL(11, 117, 7), // "KeyDown"
QT_MOC_LITERAL(12, 125, 4), // "dkey"
QT_MOC_LITERAL(13, 130, 5), // "KeyUp"
QT_MOC_LITERAL(14, 136, 8), // "KeyPress"
QT_MOC_LITERAL(15, 145, 11), // "SetMousePos"
QT_MOC_LITERAL(16, 157, 1), // "x"
QT_MOC_LITERAL(17, 159, 1), // "y"
QT_MOC_LITERAL(18, 161, 9), // "MouseMove"
QT_MOC_LITERAL(19, 171, 5), // "pause"
QT_MOC_LITERAL(20, 177, 9), // "MouseDown"
QT_MOC_LITERAL(21, 187, 6), // "button"
QT_MOC_LITERAL(22, 194, 7), // "MouseUp"
QT_MOC_LITERAL(23, 202, 10), // "MouseClick"
QT_MOC_LITERAL(24, 213, 14), // "MouseWheelDown"
QT_MOC_LITERAL(25, 228, 12), // "MouseWheelUp"
QT_MOC_LITERAL(26, 241, 14), // "MouseWheelLeft"
QT_MOC_LITERAL(27, 256, 15), // "MouseWheelRight"
QT_MOC_LITERAL(28, 272, 11), // "PrintScreen"
QT_MOC_LITERAL(29, 284, 4), // "file"
QT_MOC_LITERAL(30, 289, 12), // "PrintScreenA"
QT_MOC_LITERAL(31, 302, 1), // "w"
QT_MOC_LITERAL(32, 304, 1) // "h"

    },
    "TRSCore\0StartApp\0\0CloseApp\0SetOnTop\0"
    "Sleep\0GetScreenWidth\0GetScreenHeight\0"
    "WindowMinimize\0WindowMaximize\0"
    "WindowRestore\0KeyDown\0dkey\0KeyUp\0"
    "KeyPress\0SetMousePos\0x\0y\0MouseMove\0"
    "pause\0MouseDown\0button\0MouseUp\0"
    "MouseClick\0MouseWheelDown\0MouseWheelUp\0"
    "MouseWheelLeft\0MouseWheelRight\0"
    "PrintScreen\0file\0PrintScreenA\0w\0h"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TRSCore[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  129,    2, 0x0a /* Public */,
       3,    0,  132,    2, 0x0a /* Public */,
       4,    1,  133,    2, 0x0a /* Public */,
       5,    1,  136,    2, 0x0a /* Public */,
       6,    0,  139,    2, 0x0a /* Public */,
       7,    0,  140,    2, 0x0a /* Public */,
       8,    0,  141,    2, 0x0a /* Public */,
       9,    0,  142,    2, 0x0a /* Public */,
      10,    0,  143,    2, 0x0a /* Public */,
      11,    1,  144,    2, 0x0a /* Public */,
      13,    1,  147,    2, 0x0a /* Public */,
      14,    1,  150,    2, 0x0a /* Public */,
      15,    2,  153,    2, 0x0a /* Public */,
      18,    3,  158,    2, 0x0a /* Public */,
      20,    1,  165,    2, 0x0a /* Public */,
      22,    1,  168,    2, 0x0a /* Public */,
      23,    1,  171,    2, 0x0a /* Public */,
      24,    0,  174,    2, 0x0a /* Public */,
      25,    0,  175,    2, 0x0a /* Public */,
      26,    0,  176,    2, 0x0a /* Public */,
      27,    0,  177,    2, 0x0a /* Public */,
      28,    1,  178,    2, 0x0a /* Public */,
      30,    5,  181,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   16,   17,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   16,   17,   19,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::QString,   16,   17,   31,   32,   29,

       0        // eod
};

void TRSCore::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TRSCore *_t = static_cast<TRSCore *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->StartApp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->CloseApp(); break;
        case 2: _t->SetOnTop((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->Sleep((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: { int _r = _t->GetScreenWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 5: { int _r = _t->GetScreenHeight();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 6: _t->WindowMinimize(); break;
        case 7: _t->WindowMaximize(); break;
        case 8: _t->WindowRestore(); break;
        case 9: _t->KeyDown((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->KeyUp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->KeyPress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->SetMousePos((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->MouseMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 14: _t->MouseDown((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->MouseUp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->MouseClick((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->MouseWheelDown(); break;
        case 18: _t->MouseWheelUp(); break;
        case 19: _t->MouseWheelLeft(); break;
        case 20: _t->MouseWheelRight(); break;
        case 21: _t->PrintScreen((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: _t->PrintScreenA((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        default: ;
        }
    }
}

const QMetaObject TRSCore::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TRSCore.data,
      qt_meta_data_TRSCore,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TRSCore::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TRSCore::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TRSCore.stringdata0))
        return static_cast<void*>(const_cast< TRSCore*>(this));
    return QObject::qt_metacast(_clname);
}

int TRSCore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 23;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
