/****************************************************************************
** Meta object code from reading C++ file 'aventura.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ATMLibrary/aventura.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'aventura.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSAventuraENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSAventuraENDCLASS = QtMocHelpers::stringData(
    "Aventura",
    "on_trimite_clicked",
    "",
    "performSearch",
    "searchText",
    "on_x_clicked",
    "on_adauga_clicked",
    "on_inapoi_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSAventuraENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[9];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[11];
    char stringdata5[13];
    char stringdata6[18];
    char stringdata7[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSAventuraENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSAventuraENDCLASS_t qt_meta_stringdata_CLASSAventuraENDCLASS = {
    {
        QT_MOC_LITERAL(0, 8),  // "Aventura"
        QT_MOC_LITERAL(9, 18),  // "on_trimite_clicked"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 13),  // "performSearch"
        QT_MOC_LITERAL(43, 10),  // "searchText"
        QT_MOC_LITERAL(54, 12),  // "on_x_clicked"
        QT_MOC_LITERAL(67, 17),  // "on_adauga_clicked"
        QT_MOC_LITERAL(85, 17)   // "on_inapoi_clicked"
    },
    "Aventura",
    "on_trimite_clicked",
    "",
    "performSearch",
    "searchText",
    "on_x_clicked",
    "on_adauga_clicked",
    "on_inapoi_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSAventuraENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x08,    1 /* Private */,
       3,    1,   45,    2, 0x08,    2 /* Private */,
       5,    0,   48,    2, 0x08,    4 /* Private */,
       6,    0,   49,    2, 0x08,    5 /* Private */,
       7,    0,   50,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Aventura::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSAventuraENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSAventuraENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSAventuraENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Aventura, std::true_type>,
        // method 'on_trimite_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'performSearch'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'on_x_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_adauga_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_inapoi_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Aventura::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Aventura *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_trimite_clicked(); break;
        case 1: _t->performSearch((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->on_x_clicked(); break;
        case 3: _t->on_adauga_clicked(); break;
        case 4: _t->on_inapoi_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *Aventura::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Aventura::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSAventuraENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Aventura::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP