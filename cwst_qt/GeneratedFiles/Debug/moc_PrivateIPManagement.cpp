/****************************************************************************
** Meta object code from reading C++ file 'PrivateIPManagement.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PrivateIPManagement.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PrivateIPManagement.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PrivateIPManagement_t {
    QByteArrayData data[7];
    char stringdata[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_PrivateIPManagement_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_PrivateIPManagement_t qt_meta_stringdata_PrivateIPManagement = {
    {
QT_MOC_LITERAL(0, 0, 19),
QT_MOC_LITERAL(1, 20, 16),
QT_MOC_LITERAL(2, 37, 0),
QT_MOC_LITERAL(3, 38, 3),
QT_MOC_LITERAL(4, 42, 8),
QT_MOC_LITERAL(5, 51, 12),
QT_MOC_LITERAL(6, 64, 11)
    },
    "PrivateIPManagement\0contextMenuEvent\0"
    "\0pos\0okButton\0CancelButton\0addIPbutton\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PrivateIPManagement[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x08,
       4,    0,   37,    2, 0x08,
       5,    0,   38,    2, 0x08,
       6,    0,   39,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PrivateIPManagement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PrivateIPManagement *_t = static_cast<PrivateIPManagement *>(_o);
        switch (_id) {
        case 0: _t->contextMenuEvent((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 1: _t->okButton(); break;
        case 2: _t->CancelButton(); break;
        case 3: _t->addIPbutton(); break;
        default: ;
        }
    }
}

const QMetaObject PrivateIPManagement::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PrivateIPManagement.data,
      qt_meta_data_PrivateIPManagement,  qt_static_metacall, 0, 0}
};


const QMetaObject *PrivateIPManagement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PrivateIPManagement::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PrivateIPManagement.stringdata))
        return static_cast<void*>(const_cast< PrivateIPManagement*>(this));
    return QDialog::qt_metacast(_clname);
}

int PrivateIPManagement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
