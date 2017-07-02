/****************************************************************************
** Meta object code from reading C++ file 'scannerqt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../scannerqt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scannerqt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ScannerQt_t {
    QByteArrayData data[14];
    char stringdata0[204];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScannerQt_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScannerQt_t qt_meta_stringdata_ScannerQt = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ScannerQt"
QT_MOC_LITERAL(1, 10, 12), // "result_ready"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 11), // "result_type"
QT_MOC_LITERAL(4, 36, 6), // "result"
QT_MOC_LITERAL(5, 43, 15), // "paths_collected"
QT_MOC_LITERAL(6, 59, 17), // "unique_path_store"
QT_MOC_LITERAL(7, 77, 3), // "ups"
QT_MOC_LITERAL(8, 81, 20), // "on_load_sigs_clicked"
QT_MOC_LITERAL(9, 102, 21), // "on_scan_files_clicked"
QT_MOC_LITERAL(10, 124, 20), // "on_scan_data_clicked"
QT_MOC_LITERAL(11, 145, 20), // "on_stop_scan_clicked"
QT_MOC_LITERAL(12, 166, 18), // "on_result_received"
QT_MOC_LITERAL(13, 185, 18) // "on_paths_collected"

    },
    "ScannerQt\0result_ready\0\0result_type\0"
    "result\0paths_collected\0unique_path_store\0"
    "ups\0on_load_sigs_clicked\0on_scan_files_clicked\0"
    "on_scan_data_clicked\0on_stop_scan_clicked\0"
    "on_result_received\0on_paths_collected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScannerQt[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       5,    1,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,
      10,    0,   62,    2, 0x08 /* Private */,
      11,    0,   63,    2, 0x08 /* Private */,
      12,    1,   64,    2, 0x08 /* Private */,
      13,    1,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void ScannerQt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScannerQt *_t = static_cast<ScannerQt *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->result_ready((*reinterpret_cast< const result_type(*)>(_a[1]))); break;
        case 1: _t->paths_collected((*reinterpret_cast< const unique_path_store(*)>(_a[1]))); break;
        case 2: _t->on_load_sigs_clicked(); break;
        case 3: _t->on_scan_files_clicked(); break;
        case 4: _t->on_scan_data_clicked(); break;
        case 5: _t->on_stop_scan_clicked(); break;
        case 6: _t->on_result_received((*reinterpret_cast< const result_type(*)>(_a[1]))); break;
        case 7: _t->on_paths_collected((*reinterpret_cast< const unique_path_store(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ScannerQt::*_t)(const result_type & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScannerQt::result_ready)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ScannerQt::*_t)(const unique_path_store & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScannerQt::paths_collected)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ScannerQt::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ScannerQt.data,
      qt_meta_data_ScannerQt,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ScannerQt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScannerQt::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ScannerQt.stringdata0))
        return static_cast<void*>(const_cast< ScannerQt*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ScannerQt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ScannerQt::result_ready(const result_type & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ScannerQt::paths_collected(const unique_path_store & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
