/****************************************************************************
** Meta object code from reading C++ file 'RenderQt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QtMight/RenderQt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RenderQt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RenderQt_t {
    QByteArrayData data[8];
    char stringdata[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RenderQt_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RenderQt_t qt_meta_stringdata_RenderQt = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 12),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 9),
QT_MOC_LITERAL(4, 33, 3),
QT_MOC_LITERAL(5, 37, 9),
QT_MOC_LITERAL(6, 47, 13),
QT_MOC_LITERAL(7, 61, 6)
    },
    "RenderQt\0SetBattleMap\0\0BattleMap\0map\0"
    "SetSubmap\0NavigableGrid\0submap"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RenderQt[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a /* Public */,
       5,    1,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void RenderQt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RenderQt *_t = static_cast<RenderQt *>(_o);
        switch (_id) {
        case 0: _t->SetBattleMap((*reinterpret_cast< BattleMap(*)>(_a[1]))); break;
        case 1: _t->SetSubmap((*reinterpret_cast< NavigableGrid(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject RenderQt::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_RenderQt.data,
      qt_meta_data_RenderQt,  qt_static_metacall, 0, 0}
};


const QMetaObject *RenderQt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RenderQt::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RenderQt.stringdata))
        return static_cast<void*>(const_cast< RenderQt*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int RenderQt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
