/****************************************************************************
** Meta object code from reading C++ file 'netsim_mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../netsim_ui/netsim_mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'netsim_mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Netsim_MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[291];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Netsim_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Netsim_MainWindow_t qt_meta_stringdata_Netsim_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 17), // "Netsim_MainWindow"
QT_MOC_LITERAL(1, 18, 18), // "on_btnQuit_pressed"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 19), // "on_btnOnOff_pressed"
QT_MOC_LITERAL(4, 58, 21), // "on_radioArqSw_pressed"
QT_MOC_LITERAL(5, 80, 21), // "on_radioArqBn_pressed"
QT_MOC_LITERAL(6, 102, 14), // "widget_repaint"
QT_MOC_LITERAL(7, 117, 10), // "frame_send"
QT_MOC_LITERAL(8, 128, 17), // "paint_recalculate"
QT_MOC_LITERAL(9, 146, 33), // "on_spinDataLength_editingFini..."
QT_MOC_LITERAL(10, 180, 33), // "on_spinWindowSize_editingFini..."
QT_MOC_LITERAL(11, 214, 23), // "on_actionQuit_triggered"
QT_MOC_LITERAL(12, 238, 24), // "on_actionAbout_triggered"
QT_MOC_LITERAL(13, 263, 13), // "print_dbg_msg"
QT_MOC_LITERAL(14, 277, 11), // "const char*"
QT_MOC_LITERAL(15, 289, 1) // "x"

    },
    "Netsim_MainWindow\0on_btnQuit_pressed\0"
    "\0on_btnOnOff_pressed\0on_radioArqSw_pressed\0"
    "on_radioArqBn_pressed\0widget_repaint\0"
    "frame_send\0paint_recalculate\0"
    "on_spinDataLength_editingFinished\0"
    "on_spinWindowSize_editingFinished\0"
    "on_actionQuit_triggered\0"
    "on_actionAbout_triggered\0print_dbg_msg\0"
    "const char*\0x"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Netsim_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    1,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,

       0        // eod
};

void Netsim_MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Netsim_MainWindow *_t = static_cast<Netsim_MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnQuit_pressed(); break;
        case 1: _t->on_btnOnOff_pressed(); break;
        case 2: { int _r = _t->on_radioArqSw_pressed();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->on_radioArqBn_pressed();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: _t->widget_repaint(); break;
        case 5: _t->frame_send(); break;
        case 6: _t->paint_recalculate(); break;
        case 7: _t->on_spinDataLength_editingFinished(); break;
        case 8: _t->on_spinWindowSize_editingFinished(); break;
        case 9: _t->on_actionQuit_triggered(); break;
        case 10: _t->on_actionAbout_triggered(); break;
        case 11: _t->print_dbg_msg((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Netsim_MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Netsim_MainWindow.data,
      qt_meta_data_Netsim_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Netsim_MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Netsim_MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Netsim_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< Netsim_MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Netsim_MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
