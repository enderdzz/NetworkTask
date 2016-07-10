/****************************************************************************
** Meta object code from reading C++ file 'simsender.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../netsim_ui/simsender.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'simsender.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SimSender_t {
    QByteArrayData data[9];
    char stringdata[113];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SimSender_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SimSender_t qt_meta_stringdata_SimSender = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 26),
QT_MOC_LITERAL(2, 37, 0),
QT_MOC_LITERAL(3, 38, 11),
QT_MOC_LITERAL(4, 50, 11),
QT_MOC_LITERAL(5, 62, 13),
QT_MOC_LITERAL(6, 76, 17),
QT_MOC_LITERAL(7, 94, 12),
QT_MOC_LITERAL(8, 107, 4)
    },
    "SimSender\0something_need_to_announce\0"
    "\0const char*\0send_status\0current_frame\0"
    "sendwindow_status\0current_left\0work\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SimSender[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06,
       4,    1,   37,    2, 0x06,
       6,    1,   40,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       8,    0,   43,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void SimSender::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SimSender *_t = static_cast<SimSender *>(_o);
        switch (_id) {
        case 0: _t->something_need_to_announce((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 1: _t->send_status((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sendwindow_status((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->work(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SimSender::*_t)(const char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SimSender::something_need_to_announce)) {
                *result = 0;
            }
        }
        {
            typedef void (SimSender::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SimSender::send_status)) {
                *result = 1;
            }
        }
        {
            typedef void (SimSender::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SimSender::sendwindow_status)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject SimSender::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SimSender.data,
      qt_meta_data_SimSender,  qt_static_metacall, 0, 0}
};


const QMetaObject *SimSender::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SimSender::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SimSender.stringdata))
        return static_cast<void*>(const_cast< SimSender*>(this));
    return QObject::qt_metacast(_clname);
}

int SimSender::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void SimSender::something_need_to_announce(const char * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SimSender::send_status(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SimSender::sendwindow_status(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
