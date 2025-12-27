
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

    init_PyCanvasType();
    if (PyType_Ready(&PyCanvasType) < 0) {
        return NULL;
    }
    Py_INCREF(&PyCanvasType);
    PyModule_AddObject(m, "Canvas", (PyObject*)&PyCanvasType);

    return m;
}
