/****************************************************************************
** Meta object code from reading C++ file 'cwst_qt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../cwst_qt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cwst_qt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_cwst_qt_t {
    QByteArrayData data[16];
    char stringdata[202];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_cwst_qt_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_cwst_qt_t qt_meta_stringdata_cwst_qt = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 16),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 3),
QT_MOC_LITERAL(4, 30, 4),
QT_MOC_LITERAL(5, 35, 19),
QT_MOC_LITERAL(6, 55, 3),
QT_MOC_LITERAL(7, 59, 18),
QT_MOC_LITERAL(8, 78, 15),
QT_MOC_LITERAL(9, 94, 20),
QT_MOC_LITERAL(10, 115, 7),
QT_MOC_LITERAL(11, 123, 12),
QT_MOC_LITERAL(12, 136, 18),
QT_MOC_LITERAL(13, 155, 11),
QT_MOC_LITERAL(14, 167, 18),
QT_MOC_LITERAL(15, 186, 14)
    },
    "cwst_qt\0contextMenuEvent\0\0pos\0Exit\0"
    "PrivateSlotsChanged\0max\0PublicSlotsChanged\0"
    "MaxLevelChanged\0MaxLevelCheckChanged\0"
    "checked\0showBansForm\0showPrivateIpsForm\0"
    "maxPchanged\0usepubfirstchanged\0"
    "alwaysDaylight\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cwst_qt[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x08,
       4,    0,   72,    2, 0x08,
       5,    1,   73,    2, 0x08,
       7,    1,   76,    2, 0x08,
       8,    1,   79,    2, 0x08,
       9,    1,   82,    2, 0x08,
      11,    0,   85,    2, 0x08,
      12,    0,   86,    2, 0x08,
      13,    1,   87,    2, 0x08,
      14,    1,   90,    2, 0x08,
      15,    1,   93,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,

       0        // eod
};

void cwst_qt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        cwst_qt *_t = static_cast<cwst_qt *>(_o);
        switch (_id) {
        case 0: _t->contextMenuEvent((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: _t->Exit(); break;
        case 2: _t->PrivateSlotsChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->PublicSlotsChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->MaxLevelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->MaxLevelCheckChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->showBansForm(); break;
        case 7: _t->showPrivateIpsForm(); break;
        case 8: _t->maxPchanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->usepubfirstchanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->alwaysDaylight((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject cwst_qt::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_cwst_qt.data,
      qt_meta_data_cwst_qt,  qt_static_metacall, 0, 0}
};


const QMetaObject *cwst_qt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cwst_qt::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_cwst_qt.stringdata))
        return static_cast<void*>(const_cast< cwst_qt*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int cwst_qt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
    return _id;
}
QT_END_MOC_NAMESPACE
