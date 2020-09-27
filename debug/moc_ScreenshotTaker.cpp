/****************************************************************************
** Meta object code from reading C++ file 'ScreenshotTaker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/ScreenshotTaker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScreenshotTaker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ScreenshotTaker_t {
    QByteArrayData data[9];
    char stringdata0[118];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScreenshotTaker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScreenshotTaker_t qt_meta_stringdata_ScreenshotTaker = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ScreenshotTaker"
QT_MOC_LITERAL(1, 16, 30), // "signalIsWaitingForInputChanged"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 8), // "takeBase"
QT_MOC_LITERAL(4, 57, 10), // "takeSample"
QT_MOC_LITERAL(5, 68, 17), // "focusAreaReceived"
QT_MOC_LITERAL(6, 86, 6), // "point1"
QT_MOC_LITERAL(7, 93, 6), // "point2"
QT_MOC_LITERAL(8, 100, 17) // "IsWaitingForInput"

    },
    "ScreenshotTaker\0signalIsWaitingForInputChanged\0"
    "\0takeBase\0takeSample\0focusAreaReceived\0"
    "point1\0point2\0IsWaitingForInput"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScreenshotTaker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       1,   42, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   35,    2, 0x0a /* Public */,
       4,    0,   36,    2, 0x0a /* Public */,
       5,    2,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint, QMetaType::QPoint,    6,    7,

 // properties: name, type, flags
       8, QMetaType::Bool, 0x00495103,

 // properties: notify_signal_id
       0,

       0        // eod
};

void ScreenshotTaker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScreenshotTaker *_t = static_cast<ScreenshotTaker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalIsWaitingForInputChanged(); break;
        case 1: _t->takeBase(); break;
        case 2: _t->takeSample(); break;
        case 3: _t->focusAreaReceived((*reinterpret_cast< const QPoint(*)>(_a[1])),(*reinterpret_cast< const QPoint(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ScreenshotTaker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScreenshotTaker::signalIsWaitingForInputChanged)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        ScreenshotTaker *_t = static_cast<ScreenshotTaker *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->getIsWaitingForInput(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        ScreenshotTaker *_t = static_cast<ScreenshotTaker *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setIsWaitingForInput(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject ScreenshotTaker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ScreenshotTaker.data,
      qt_meta_data_ScreenshotTaker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ScreenshotTaker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScreenshotTaker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ScreenshotTaker.stringdata0))
        return static_cast<void*>(const_cast< ScreenshotTaker*>(this));
    return QObject::qt_metacast(_clname);
}

int ScreenshotTaker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ScreenshotTaker::signalIsWaitingForInputChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
