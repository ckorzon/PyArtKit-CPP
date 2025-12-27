#ifndef COLOR_H
#define COLOR_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <memory>
#include "canvas.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    PyObject_HEAD
    std::unique_ptr<RgbColor> color;
} PyColorObject;

extern PyTypeObject PyColorType;

extern void init_PyColorType();

#define PyColor_Check(op) PyObject_TypeCheck(op, &PyColorType)

#ifdef __cplusplus
}
#endif

#endif