/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../UnixRav3/RavQt/LogViewer/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[17];
    char stringdata0[310];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 17), // "OnClickedLeftKill"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 18), // "OnClickedLeftSetup"
QT_MOC_LITERAL(4, 49, 20), // "OnClickedLeftVDetail"
QT_MOC_LITERAL(5, 70, 22), // "OnClickedLeftScanEvent"
QT_MOC_LITERAL(6, 93, 23), // "OnClickedLeftNetDefence"
QT_MOC_LITERAL(7, 117, 22), // "OnClickedLeftIsolation"
QT_MOC_LITERAL(8, 140, 22), // "OnClickedLeftUrlAccess"
QT_MOC_LITERAL(9, 163, 19), // "OnClickedLeftIPRule"
QT_MOC_LITERAL(10, 183, 20), // "OnClickedLeftInstall"
QT_MOC_LITERAL(11, 204, 19), // "OnClickedLeftSysLog"
QT_MOC_LITERAL(12, 224, 10), // "setMinimum"
QT_MOC_LITERAL(13, 235, 22), // "OnActivatedSysTrayIcon"
QT_MOC_LITERAL(14, 258, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(15, 292, 6), // "reason"
QT_MOC_LITERAL(16, 299, 10) // "OnMaxState"

    },
    "MainWindow\0OnClickedLeftKill\0\0"
    "OnClickedLeftSetup\0OnClickedLeftVDetail\0"
    "OnClickedLeftScanEvent\0OnClickedLeftNetDefence\0"
    "OnClickedLeftIsolation\0OnClickedLeftUrlAccess\0"
    "OnClickedLeftIPRule\0OnClickedLeftInstall\0"
    "OnClickedLeftSysLog\0setMinimum\0"
    "OnActivatedSysTrayIcon\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason\0OnMaxState"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       6,    0,   83,    2, 0x0a /* Public */,
       7,    0,   84,    2, 0x0a /* Public */,
       8,    0,   85,    2, 0x0a /* Public */,
       9,    0,   86,    2, 0x0a /* Public */,
      10,    0,   87,    2, 0x0a /* Public */,
      11,    0,   88,    2, 0x0a /* Public */,
      12,    0,   89,    2, 0x0a /* Public */,
      13,    1,   90,    2, 0x0a /* Public */,
      16,    0,   93,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnClickedLeftKill(); break;
        case 1: _t->OnClickedLeftSetup(); break;
        case 2: _t->OnClickedLeftVDetail(); break;
        case 3: _t->OnClickedLeftScanEvent(); break;
        case 4: _t->OnClickedLeftNetDefence(); break;
        case 5: _t->OnClickedLeftIsolation(); break;
        case 6: _t->OnClickedLeftUrlAccess(); break;
        case 7: _t->OnClickedLeftIPRule(); break;
        case 8: _t->OnClickedLeftInstall(); break;
        case 9: _t->OnClickedLeftSysLog(); break;
        case 10: _t->setMinimum(); break;
        case 11: _t->OnActivatedSysTrayIcon((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 12: _t->OnMaxState(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    if (!strcmp(_clname, "Application"))
        return static_cast< Application*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
