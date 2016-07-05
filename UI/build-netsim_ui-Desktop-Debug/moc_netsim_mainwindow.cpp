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
    QByteArrayData data[18];
    char stringdata0[319];
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
QT_MOC_LITERAL(7, 117, 17), // "paint_recalculate"
QT_MOC_LITERAL(8, 135, 14), // "current_window"
QT_MOC_LITERAL(9, 150, 11), // "window_size"
QT_MOC_LITERAL(10, 162, 11), // "frame_count"
QT_MOC_LITERAL(11, 174, 33), // "on_spinDataLength_editingFini..."
QT_MOC_LITERAL(12, 208, 33), // "on_spinWindowSize_editingFini..."
QT_MOC_LITERAL(13, 242, 23), // "on_actionQuit_triggered"
QT_MOC_LITERAL(14, 266, 24), // "on_actionAbout_triggered"
QT_MOC_LITERAL(15, 291, 13), // "print_dbg_msg"
QT_MOC_LITERAL(16, 305, 11), // "const char*"
QT_MOC_LITERAL(17, 317, 1) // "x"

    },
    "Netsim_MainWindow\0on_btnQuit_pressed\0"
    "\0on_btnOnOff_pressed\0on_radioArqSw_pressed\0"
    "on_radioArqBn_pressed\0widget_repaint\0"
    "paint_recalculate\0current_window\0"
    "window_size\0frame_count\0"
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
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    3,   74,    2, 0x08 /* Private */,
      11,    0,   81,    2, 0x08 /* Private */,
      12,    0,   82,    2, 0x08 /* Private */,
      13,    0,   83,    2, 0x08 /* Private */,
      14,    0,   84,    2, 0x08 /* Private */,
      15,    1,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    8,    9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,

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
        case 5: _t->paint_recalculate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: _t->on_spinDataLength_editingFinished(); break;
        case 7: _t->on_spinWindowSize_editingFinished(); break;
        case 8: _t->on_actionQuit_triggered(); break;
        case 9: _t->on_actionAbout_triggered(); break;
        case 10: _t->print_dbg_msg((*reinterpret_cast< const char*(*)>(_a[1]))); break;
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
