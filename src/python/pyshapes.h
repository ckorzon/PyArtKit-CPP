
#ifndef PYSHAPES_H
#define PYSHAPES_H

#include "pycolor.h"
#include "geometry.h"

#ifdef __cplusplus
extern "C" {
#endif

// SHAPE
typedef struct {
    PyObject_HEAD
    std::shared_ptr<Shape> shape;
} PyShapeObject;

extern PyTypeObject PyShapeType;
extern void init_PyShapeType();
#define PyShape_Check(op) PyObject_TypeCheck(op, &PyShapeType)


// CIRCLE

typedef struct {
    PyShapeObject base;
} PyCircleObject;

extern PyTypeObject PyCircleType;
extern void init_PyCircleType();
#define PyCircle_Check(op) PyObject_TypeCheck(op, &PyCircleType)


// POLYGON

typedef struct {
    PyShapeObject base;
} PyPolygonObject;

extern PyTypeObject PyPolygonType;
extern void init_PyPolygonType();
#define PyPolygon_Check(op) PyObject_TypeCheck(op, &PyPolygonType)


#ifdef __cplusplus
}
#endif

#endif
