
#ifndef PYCANVAS_H
#define PYCANVAS_H

#include "pyshapes.h"
#include "canvas.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    PyObject_HEAD
    std::unique_ptr<Canvas> canvas;
} PyCanvasObject;

extern void init_PyCanvasType();
extern PyTypeObject PyCanvasType;

#ifdef __cplusplus
}
#endif

#endif