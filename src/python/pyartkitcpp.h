
#ifndef PYARTKITCPP_H
#define PYARTKITCPP_H

#include "pycanvas.h"

#ifdef __cplusplus
extern "C" {
#endif

static struct PyModuleDef pyartkitcpp_module = {
    PyModuleDef_HEAD_INIT,
    "pyartkitcpp",
    "Python bindings for ArtKit C++ library",
    -1,
    NULL
};

PyMODINIT_FUNC PyInit_pyartkitcpp(void); 

#ifdef __cplusplus
}
#endif

#endif
