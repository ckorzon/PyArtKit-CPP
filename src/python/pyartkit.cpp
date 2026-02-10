
#include "pycanvas.h"


static struct PyModuleDef pyartkitcpp_module = {
    PyModuleDef_HEAD_INIT,
    "pyartkitcpp",
    "Python bindings for ArtKit C++ library",
    -1,
    NULL
};

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

    // Initialize Shape and children

    init_PyShapeType();
    init_PyCircleType();
    init_PyPolygonType();

    PyCircleType.tp_base = &PyShapeType;
    PyPolygonType.tp_base = &PyShapeType;

    if (PyType_Ready(&PyShapeType) < 0) return nullptr;
    if (PyType_Ready(&PyCircleType) < 0) return nullptr;
    if (PyType_Ready(&PyPolygonType) < 0) return nullptr;

    Py_INCREF(&PyShapeType);
    Py_INCREF(&PyCircleType);
    Py_INCREF(&PyPolygonType);

    PyModule_AddObject(m, "Shape", (PyObject*)&PyShapeType);
    PyModule_AddObject(m, "Circle", (PyObject*)&PyCircleType);
    PyModule_AddObject(m, "Polygon", (PyObject*)&PyPolygonType);

    // Initialize Canvas
    init_PyCanvasType();
    if (PyType_Ready(&PyCanvasType) < 0) {
        return NULL;
    }
    Py_INCREF(&PyCanvasType);
    PyModule_AddObject(m, "Canvas", (PyObject*)&PyCanvasType);

    return m;
}
