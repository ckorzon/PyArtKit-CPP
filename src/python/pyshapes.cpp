
#include "pyshapes.h"
#include <stdexcept>

// * ---------- SHAPE ---------- * //

static int PyShape_init(PyShapeObject *self, PyObject *args, PyObject *kwargs) {
    PyErr_SetString(PyExc_RuntimeError, "Cannot instantiate abstract Shape class");
    return -1;
}

PyTypeObject PyShapeType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
};

static void PyShape_dealloc(PyShapeObject* self) {
    self->shape.reset();
    Py_TYPE(self)->tp_free((PyObject*)self);
}

void init_PyShapeType() {
    PyShapeType.tp_name = "pyartkitcpp.Shape";
    PyShapeType.tp_basicsize = sizeof(PyShapeObject);
    PyShapeType.tp_itemsize = 0;
    PyShapeType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    PyShapeType.tp_doc = "Abstract Shape class";
    PyShapeType.tp_init = (initproc)PyShape_init;
    PyShapeType.tp_new = PyType_GenericNew;
    PyShapeType.tp_dealloc = (destructor)PyShape_dealloc;
}

// * ---------- CIRCLE ---------- * //

static int PyCircle_init(PyCircleObject *self, PyObject *args, PyObject *kwargs) {
    static const char *kwlist[] = {"x", "y", "radius", NULL};
    int centerX, centerY, radius;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iii", const_cast<char **>(kwlist),
                                     &centerX, &centerY, &radius)) {
        return -1;
    }

    try {
        self->base.shape = std::make_shared<Circle>(centerX, centerY, radius);
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to create Circle object");
        return -1;
    }

    return 0;
}

// ToDo: Add Circle getters and setters

static PyGetSetDef PyCircle_getset[] = {
    {nullptr}
};

static PyObject* PyCircle_translate(PyCircleObject* self, PyObject* args, PyObject* kwargs) {
    static const char* kwlist[] = {"dx", "dy", nullptr};

    int dx, dy;

    if (!PyArg_ParseTupleAndKeywords(
            args,
            kwargs,
            "ii",
            const_cast<char**>(kwlist),
            &dx, &dy))
    {
        return nullptr;
    }

    self->base.shape->translate(dx, dy);
    Py_RETURN_NONE;
};

static PyMethodDef PyCircle_methods[] = {
    {"translate", (PyCFunction)PyCircle_translate, METH_VARARGS | METH_KEYWORDS, "Translate the circle using dx and dy"},
    {NULL}
};

PyTypeObject PyCircleType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
};

void init_PyCircleType() {
    PyCircleType.tp_name = "pyartkitcpp.Circle";
    PyCircleType.tp_basicsize = sizeof(PyCircleObject);
    PyCircleType.tp_flags = Py_TPFLAGS_DEFAULT;
    PyCircleType.tp_init = (initproc)PyCircle_init;
    PyCircleType.tp_new = PyType_GenericNew;
    PyCircleType.tp_getset = PyCircle_getset;
    PyCircleType.tp_methods = PyCircle_methods;
}

// * ---------- POLYGON ---------- * //

static int PyPolygon_init(PyPolygonObject* self, PyObject* args, PyObject* kwargs) {
    static const char* kwlist[] = {"vertices", nullptr};

    PyObject* verticesObj = nullptr;

    if (!PyArg_ParseTupleAndKeywords(
            args,
            kwargs,
            "O",
            const_cast<char**>(kwlist),
            &verticesObj))
    {
        return -1;
    }

    // Ensure the provided vertices object is a valid ordered list
    if (!PyList_Check(verticesObj)) {
        PyErr_SetString(PyExc_TypeError, "vertices must be a list of (x, y) tuples");
        return -1;
    }

    Py_ssize_t count = PyList_Size(verticesObj);
    if (count < 3) {
        PyErr_SetString(PyExc_ValueError, "Polygon requires at least 3 vertices");
        return -1;
    }

    // Create the C++ Polygon
    auto polygon = std::make_shared<Polygon>();

    for (Py_ssize_t i = 0; i < count; ++i) {
        // * Borrowed Reference
        PyObject* item = PyList_GetItem(verticesObj, i);

        // Validate that each item is a tuple of (x, y)
        if (!PyTuple_Check(item) || PyTuple_Size(item) != 2) {
            PyErr_Format(
                PyExc_TypeError,
                "vertex at index %zd is not a (x, y) tuple",
                i
            );
            return -1;
        }

        // * Borrowed Reference
        PyObject* xObj = PyTuple_GetItem(item, 0);
        PyObject* yObj = PyTuple_GetItem(item, 1);

        int x = (int) PyLong_AsLong(xObj);
        int y = (int) PyLong_AsLong(yObj);

        if (PyErr_Occurred()) {
            PyErr_Format(
                PyExc_TypeError,
                "vertex at index %zd contains non-integer values",
                i
            );
            return -1;
        }

        polygon->addVertex(Vertex(x, y));
    }

    // Store as Shape (polymorphic)
    self->base.shape = polygon;
    return 0;
}

// ToDo: Add Polygon getters and setters

static PyGetSetDef PyPolygon_getset[] = {
    {nullptr}
};

static PyObject* PyPolygon_translate(PyPolygonObject* self, PyObject* args, PyObject* kwargs) {
    static const char* kwlist[] = {"dx", "dy", nullptr};

    int dx, dy;

    if (!PyArg_ParseTupleAndKeywords(
            args,
            kwargs,
            "ii",
            const_cast<char**>(kwlist),
            &dx, &dy))
    {
        return nullptr;
    }

    self->base.shape->translate(dx, dy);
    Py_RETURN_NONE;
};

static PyMethodDef PyPolygon_methods[] = {
    {"translate", (PyCFunction)PyPolygon_translate, METH_VARARGS | METH_KEYWORDS, "Translate the polygon using dx and dy"},
    {NULL}
};

PyTypeObject PyPolygonType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
};

void init_PyPolygonType() {
    PyPolygonType.tp_name = "pyartkitcpp.Polygon";
    PyPolygonType.tp_basicsize = sizeof(PyPolygonObject);
    PyPolygonType.tp_flags = Py_TPFLAGS_DEFAULT;
    PyPolygonType.tp_init = (initproc)PyPolygon_init;
    PyPolygonType.tp_new = PyType_GenericNew;
    PyPolygonType.tp_getset = PyPolygon_getset;
    PyPolygonType.tp_methods = PyPolygon_methods;
}

// * ---------- ELLIPSE ---------- * //


static int PyEllipse_init(PyEllipseObject *self, PyObject *args, PyObject *kwargs) {
    static const char *kwlist[] = {"x", "y", "x_radius", "y_radius", NULL};
    int centerX, centerY, xRadius, yRadius;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiii", const_cast<char **>(kwlist),
                                     &centerX, &centerY, &xRadius, &yRadius)) {
        return -1;
    }

    try {
        self->base.shape = std::make_shared<Ellipse>(centerX, centerY, xRadius, yRadius);
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to create Ellipse object");
        return -1;
    }

    return 0;
}

// ToDo: Add Ellipse getters and setters

static PyGetSetDef PyEllipse_getset[] = {
    {nullptr}
};

static PyObject* PyEllipse_translate(PyEllipseObject* self, PyObject* args, PyObject* kwargs) {
    static const char* kwlist[] = {"dx", "dy", nullptr};

    int dx, dy;

    if (!PyArg_ParseTupleAndKeywords(
            args,
            kwargs,
            "ii",
            const_cast<char**>(kwlist),
            &dx, &dy))
    {
        return nullptr;
    }

    self->base.shape->translate(dx, dy);
    Py_RETURN_NONE;
};

static PyMethodDef PyEllipse_methods[] = {
    {"translate", (PyCFunction)PyEllipse_translate, METH_VARARGS | METH_KEYWORDS, "Translate the ellipse using dx and dy"},
    {NULL}
};

PyTypeObject PyEllipseType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
};

void init_PyEllipseType() {
    PyEllipseType.tp_name = "pyartkitcpp.Ellipse";
    PyEllipseType.tp_basicsize = sizeof(PyEllipseObject);
    PyEllipseType.tp_flags = Py_TPFLAGS_DEFAULT;
    PyEllipseType.tp_init = (initproc)PyEllipse_init;
    PyEllipseType.tp_new = PyType_GenericNew;
    PyEllipseType.tp_getset = PyEllipse_getset;
    PyEllipseType.tp_methods = PyEllipse_methods;
}

// * ---------- HALF CIRCLE ---------- * //

static int PyHalfCircle_init(PyHalfCircleObject *self, PyObject *args, PyObject *kwargs) {
    static const char *kwlist[] = {"x", "y", "radius", "normal_vector", NULL};
    int centerX, centerY, radius;
    PyObject* normalVectorObj = nullptr;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiiO", const_cast<char **>(kwlist),
                                     &centerX, &centerY, &radius, &normalVectorObj)) {
        return -1;
    }

    // Validate normal_vector is a tuple of two integers
    if (!PyTuple_Check(normalVectorObj) || PyTuple_Size(normalVectorObj) != 2) {
        PyErr_SetString(PyExc_TypeError, "normal_vector must be a tuple of two integers");
        return -1;
    }

    int normalX = (int) PyLong_AsLong(PyTuple_GetItem(normalVectorObj, 0));
    int normalY = (int) PyLong_AsLong(PyTuple_GetItem(normalVectorObj, 1));

    if (PyErr_Occurred()) {
        PyErr_SetString(PyExc_TypeError, "normal_vector must contain only integers");
        return -1;
    }

    try {
        self->base.shape = std::make_shared<HalfCircle>(centerX, centerY, radius, std::make_pair(normalX, normalY));
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to create HalfCircle object");
        return -1;
    }

    return 0;
}

// ToDo: Add HalfCircle getters and setters

static PyGetSetDef PyHalfCircle_getset[] = {
    {nullptr}
};

static PyObject* PyHalfCircle_translate(PyHalfCircleObject* self, PyObject* args, PyObject* kwargs) {
    static const char* kwlist[] = {"dx", "dy", nullptr};

    int dx, dy;

    if (!PyArg_ParseTupleAndKeywords(
            args,
            kwargs,
            "ii",
            const_cast<char**>(kwlist),
            &dx, &dy))
    {
        return nullptr;
    }

    self->base.shape->translate(dx, dy);
    Py_RETURN_NONE;
};

static PyMethodDef PyHalfCircle_methods[] = {
    {"translate", (PyCFunction)PyHalfCircle_translate, METH_VARARGS | METH_KEYWORDS, "Translate the half-circle using dx and dy"},
    {NULL}
};

PyTypeObject PyHalfCircleType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
};

void init_PyHalfCircleType() {
    PyHalfCircleType.tp_name = "pyartkitcpp.HalfCircle";
    PyHalfCircleType.tp_basicsize = sizeof(PyHalfCircleObject);
    PyHalfCircleType.tp_flags = Py_TPFLAGS_DEFAULT;
    PyHalfCircleType.tp_init = (initproc)PyHalfCircle_init;
    PyHalfCircleType.tp_new = PyType_GenericNew;
    PyHalfCircleType.tp_getset = PyHalfCircle_getset;
    PyHalfCircleType.tp_methods = PyHalfCircle_methods;
}


// * ---------- MODULE INITIALIZATION ---------- * //

void initShapes(PyObject* pymod) {
    init_PyShapeType();
    init_PyCircleType();
    init_PyPolygonType();
    init_PyEllipseType();
    init_PyHalfCircleType();
    PyCircleType.tp_base = &PyShapeType;
    PyPolygonType.tp_base = &PyShapeType;
    PyEllipseType.tp_base = &PyShapeType;
    PyHalfCircleType.tp_base = &PyShapeType;

    if (PyType_Ready(&PyShapeType) < 0) {
        throw std::runtime_error("Failed to initialize Shape type");
    }
    if (PyType_Ready(&PyCircleType) < 0) {
        throw std::runtime_error("Failed to initialize Circle type");
    }
    if (PyType_Ready(&PyPolygonType) < 0) {
        throw std::runtime_error("Failed to initialize Polygon type");
    }
    if (PyType_Ready(&PyEllipseType) < 0) {
        throw std::runtime_error("Failed to initialize Ellipse type");
    }
    if (PyType_Ready(&PyHalfCircleType) < 0) {
        throw std::runtime_error("Failed to initialize HalfCircle type");
    }

    Py_INCREF(&PyShapeType);
    Py_INCREF(&PyCircleType);
    Py_INCREF(&PyPolygonType);
    Py_INCREF(&PyEllipseType);
    Py_INCREF(&PyHalfCircleType);

    PyModule_AddObject(pymod, "Shape", (PyObject*)&PyShapeType);
    PyModule_AddObject(pymod, "Circle", (PyObject*)&PyCircleType);
    PyModule_AddObject(pymod, "Polygon", (PyObject*)&PyPolygonType);
    PyModule_AddObject(pymod, "Ellipse", (PyObject*)&PyEllipseType);
    PyModule_AddObject(pymod, "HalfCircle", (PyObject*)&PyHalfCircleType);
}
