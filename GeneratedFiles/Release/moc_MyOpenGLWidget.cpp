/****************************************************************************
** Meta object code from reading C++ file 'MyOpenGLWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyOpenGLWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyOpenGLWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyOpenGLWidget_t {
    QByteArrayData data[10];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyOpenGLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyOpenGLWidget_t qt_meta_stringdata_MyOpenGLWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "MyOpenGLWidget"
QT_MOC_LITERAL(1, 15, 16), // "xRotationChanged"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 5), // "angle"
QT_MOC_LITERAL(4, 39, 16), // "yRotationChanged"
QT_MOC_LITERAL(5, 56, 16), // "zRotationChanged"
QT_MOC_LITERAL(6, 73, 8), // "setLight"
QT_MOC_LITERAL(7, 82, 14), // "setShowNormals"
QT_MOC_LITERAL(8, 97, 17), // "setNormalMapColor"
QT_MOC_LITERAL(9, 115, 16) // "onActionSnapshot"

    },
    "MyOpenGLWidget\0xRotationChanged\0\0angle\0"
    "yRotationChanged\0zRotationChanged\0"
    "setLight\0setShowNormals\0setNormalMapColor\0"
    "onActionSnapshot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyOpenGLWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,
       5,    1,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   58,    2, 0x0a /* Public */,
       7,    1,   61,    2, 0x0a /* Public */,
       8,    1,   64,    2, 0x0a /* Public */,
       9,    0,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,

       0        // eod
};

void MyOpenGLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyOpenGLWidget *_t = static_cast<MyOpenGLWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->xRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->yRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->zRotationChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setLight((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->setShowNormals((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setNormalMapColor((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->onActionSnapshot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyOpenGLWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyOpenGLWidget::xRotationChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyOpenGLWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyOpenGLWidget::yRotationChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MyOpenGLWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyOpenGLWidget::zRotationChanged)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyOpenGLWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_MyOpenGLWidget.data,
      qt_meta_data_MyOpenGLWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MyOpenGLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyOpenGLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyOpenGLWidget.stringdata0))
        return static_cast<void*>(this);
    return QGLWidget::qt_metacast(_clname);
}

int MyOpenGLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void MyOpenGLWidget::xRotationChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyOpenGLWidget::yRotationChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MyOpenGLWidget::zRotationChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
