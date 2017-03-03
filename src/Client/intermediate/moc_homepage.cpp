/****************************************************************************
** Meta object code from reading C++ file 'homepage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/homepage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'homepage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_homepage_t {
    QByteArrayData data[9];
    char stringdata0[188];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_homepage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_homepage_t qt_meta_stringdata_homepage = {
    {
QT_MOC_LITERAL(0, 0, 8), // "homepage"
QT_MOC_LITERAL(1, 9, 28), // "on_actionNewFolder_triggered"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 25), // "on_ActionUpload_triggered"
QT_MOC_LITERAL(4, 65, 25), // "on_actionDelete_triggered"
QT_MOC_LITERAL(5, 91, 23), // "on_actionSync_triggered"
QT_MOC_LITERAL(6, 115, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(7, 137, 24), // "on_actionShare_triggered"
QT_MOC_LITERAL(8, 162, 25) // "on_actionLogout_triggered"

    },
    "homepage\0on_actionNewFolder_triggered\0"
    "\0on_ActionUpload_triggered\0"
    "on_actionDelete_triggered\0"
    "on_actionSync_triggered\0on_pushButton_clicked\0"
    "on_actionShare_triggered\0"
    "on_actionLogout_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_homepage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void homepage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        homepage *_t = static_cast<homepage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionNewFolder_triggered(); break;
        case 1: _t->on_ActionUpload_triggered(); break;
        case 2: _t->on_actionDelete_triggered(); break;
        case 3: _t->on_actionSync_triggered(); break;
        case 4: _t->on_pushButton_clicked(); break;
        case 5: _t->on_actionShare_triggered(); break;
        case 6: _t->on_actionLogout_triggered(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject homepage::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_homepage.data,
      qt_meta_data_homepage,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *homepage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *homepage::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_homepage.stringdata0))
        return static_cast<void*>(const_cast< homepage*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int homepage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
