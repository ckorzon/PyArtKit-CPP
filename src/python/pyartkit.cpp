
#include "pyartkitcpp.h"

PyMODINIT_FUNC PyInit_pyartkitcpp(void) {
    PyObject* m = PyModule_Create(&pyartkitcpp_module);
    if (m == NULL) {
        return NULL;
    }

    init_PyColorType();
    if (PyType_Ready(&PyColorType) < 0) {
        return NULL;
    }
    Py_INCREF(&PyColorType);
    PyModule_AddObject(m, "Color", (PyObject*)&PyColorType);

    // Initialize Shape and children types
    try {
        initShapes(m);
    } catch (const std::exception& e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return NULL;
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "An unknown error occurred while initializing shape types");
        return NULL;
    }

    // Initialize ColorScheme and children types
    try {
        initColorSchemes(m);
    } catch (const std::exception& e) {
        PyErr_SetString(PyExc_RuntimeError, e.what());
        return NULL;
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "An unknown error occurred while initializing color scheme types");
        return NULL;
    }

    // Initialize Canvas
    init_PyCanvasType();
    if (PyType_Ready(&PyCanvasType) < 0) {
        return NULL;
    }
    Py_INCREF(&PyCanvasType);
    PyModule_AddObject(m, "Canvas", (PyObject*)&PyCanvasType);

    return m;
}
