/****************************************************************************
** Meta object code from reading C++ file 'updatewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../qt_projects/Healthy_eating/updatewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'updatewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UpdateWindow_t {
    QByteArrayData data[19];
    char stringdata0[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UpdateWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UpdateWindow_t qt_meta_stringdata_UpdateWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "UpdateWindow"
QT_MOC_LITERAL(1, 13, 10), // "GetMainWin"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 1), // "x"
QT_MOC_LITERAL(4, 27, 1), // "y"
QT_MOC_LITERAL(5, 29, 1), // "w"
QT_MOC_LITERAL(6, 31, 1), // "h"
QT_MOC_LITERAL(7, 33, 9), // "ChangeWin"
QT_MOC_LITERAL(8, 43, 7), // "AddDish"
QT_MOC_LITERAL(9, 51, 10), // "UpdateDish"
QT_MOC_LITERAL(10, 62, 10), // "DeleteDish"
QT_MOC_LITERAL(11, 73, 20), // "AddDishCompatibility"
QT_MOC_LITERAL(12, 94, 23), // "UpdateDishCompatibility"
QT_MOC_LITERAL(13, 118, 23), // "DeleteDishCompatibility"
QT_MOC_LITERAL(14, 142, 10), // "CreateMenu"
QT_MOC_LITERAL(15, 153, 7), // "SetMenu"
QT_MOC_LITERAL(16, 161, 14), // "UpdateComLists"
QT_MOC_LITERAL(17, 176, 11), // "QModelIndex"
QT_MOC_LITERAL(18, 188, 5) // "index"

    },
    "UpdateWindow\0GetMainWin\0\0x\0y\0w\0h\0"
    "ChangeWin\0AddDish\0UpdateDish\0DeleteDish\0"
    "AddDishCompatibility\0UpdateDishCompatibility\0"
    "DeleteDishCompatibility\0CreateMenu\0"
    "SetMenu\0UpdateComLists\0QModelIndex\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UpdateWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   78,    2, 0x08 /* Private */,
       8,    0,   79,    2, 0x08 /* Private */,
       9,    0,   80,    2, 0x08 /* Private */,
      10,    0,   81,    2, 0x08 /* Private */,
      11,    0,   82,    2, 0x08 /* Private */,
      12,    0,   83,    2, 0x08 /* Private */,
      13,    0,   84,    2, 0x08 /* Private */,
      14,    0,   85,    2, 0x08 /* Private */,
      15,    0,   86,    2, 0x08 /* Private */,
      16,    1,   87,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,    6,

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
    QMetaType::Void, 0x80000000 | 17,   18,

       0        // eod
};

void UpdateWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UpdateWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->GetMainWin((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 1: _t->ChangeWin(); break;
        case 2: _t->AddDish(); break;
        case 3: _t->UpdateDish(); break;
        case 4: _t->DeleteDish(); break;
        case 5: _t->AddDishCompatibility(); break;
        case 6: _t->UpdateDishCompatibility(); break;
        case 7: _t->DeleteDishCompatibility(); break;
        case 8: _t->CreateMenu(); break;
        case 9: _t->SetMenu(); break;
        case 10: _t->UpdateComLists((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UpdateWindow::*)(int , int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UpdateWindow::GetMainWin)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UpdateWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_UpdateWindow.data,
    qt_meta_data_UpdateWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UpdateWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UpdateWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UpdateWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int UpdateWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void UpdateWindow::GetMainWin(int _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
