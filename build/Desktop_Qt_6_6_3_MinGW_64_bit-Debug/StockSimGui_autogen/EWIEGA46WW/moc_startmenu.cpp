/****************************************************************************
** Meta object code from reading C++ file 'startmenu.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../startmenu.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'startmenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.3. It"
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
struct qt_meta_stringdata_CLASSStartMenuENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSStartMenuENDCLASS = QtMocHelpers::stringData(
    "StartMenu",
    "balanceChanged",
    "",
    "newBalance",
    "allocatedFundsChanged",
    "amount",
    "freeFundsChanged",
    "updateRefreshButton",
    "showDetails",
    "instrumentName",
    "refreshDataAndReloadTable",
    "updateBalanceDisplays"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSStartMenuENDCLASS_t {
    uint offsetsAndSizes[24];
    char stringdata0[10];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[11];
    char stringdata4[22];
    char stringdata5[7];
    char stringdata6[17];
    char stringdata7[20];
    char stringdata8[12];
    char stringdata9[15];
    char stringdata10[26];
    char stringdata11[22];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSStartMenuENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSStartMenuENDCLASS_t qt_meta_stringdata_CLASSStartMenuENDCLASS = {
    {
        QT_MOC_LITERAL(0, 9),  // "StartMenu"
        QT_MOC_LITERAL(10, 14),  // "balanceChanged"
        QT_MOC_LITERAL(25, 0),  // ""
        QT_MOC_LITERAL(26, 10),  // "newBalance"
        QT_MOC_LITERAL(37, 21),  // "allocatedFundsChanged"
        QT_MOC_LITERAL(59, 6),  // "amount"
        QT_MOC_LITERAL(66, 16),  // "freeFundsChanged"
        QT_MOC_LITERAL(83, 19),  // "updateRefreshButton"
        QT_MOC_LITERAL(103, 11),  // "showDetails"
        QT_MOC_LITERAL(115, 14),  // "instrumentName"
        QT_MOC_LITERAL(130, 25),  // "refreshDataAndReloadTable"
        QT_MOC_LITERAL(156, 21)   // "updateBalanceDisplays"
    },
    "StartMenu",
    "balanceChanged",
    "",
    "newBalance",
    "allocatedFundsChanged",
    "amount",
    "freeFundsChanged",
    "updateRefreshButton",
    "showDetails",
    "instrumentName",
    "refreshDataAndReloadTable",
    "updateBalanceDisplays"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSStartMenuENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   56,    2, 0x06,    1 /* Public */,
       4,    1,   59,    2, 0x06,    3 /* Public */,
       6,    1,   62,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,   65,    2, 0x0a,    7 /* Public */,
       8,    1,   66,    2, 0x0a,    8 /* Public */,
      10,    0,   69,    2, 0x0a,   10 /* Public */,
      11,    0,   70,    2, 0x0a,   11 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject StartMenu::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSStartMenuENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSStartMenuENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSStartMenuENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<StartMenu, std::true_type>,
        // method 'balanceChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'allocatedFundsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'freeFundsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<double, std::false_type>,
        // method 'updateRefreshButton'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showDetails'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'refreshDataAndReloadTable'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateBalanceDisplays'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void StartMenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StartMenu *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->balanceChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 1: _t->allocatedFundsChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 2: _t->freeFundsChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 3: _t->updateRefreshButton(); break;
        case 4: _t->showDetails((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->refreshDataAndReloadTable(); break;
        case 6: _t->updateBalanceDisplays(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (StartMenu::*)(double );
            if (_t _q_method = &StartMenu::balanceChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (StartMenu::*)(double );
            if (_t _q_method = &StartMenu::allocatedFundsChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (StartMenu::*)(double );
            if (_t _q_method = &StartMenu::freeFundsChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *StartMenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StartMenu::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSStartMenuENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int StartMenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void StartMenu::balanceChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StartMenu::allocatedFundsChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void StartMenu::freeFundsChanged(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
