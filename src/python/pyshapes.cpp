
#include "pyshapes.h"

// Shape

static int PyShape_init(PyShapeObject *self, PyObject *args, PyObject *kwargs) {
    PyErr_SetString(PyExc_RuntimeError, "Cannot instantiate abstract Shape class");
    return -1;
}

PyTypeObject PyShapeType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
};

void init_PyShapeType() {
    PyShapeType.tp_name = "pyartkitcpp.Shape";
    PyShapeType.tp_basicsize = sizeof(PyShapeObject);
    PyShapeType.tp_itemsize = 0;
    PyShapeType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    PyShapeType.tp_doc = "Abstract Shape class";
    PyShapeType.tp_init = (initproc)PyShape_init;
    PyShapeType.tp_new = PyType_GenericNew;
}

// Circle

static int PyCircle_init(PyCircleObject *self, PyObject *args, PyObject *kwargs) {
    static const char *kwlist[] = {"x", "y", "radius", NULL};
    long centerX, centerY, radius;

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

// ToDo: Add Polygon getters and setters

static PyGetSetDef PyCircle_getset[] = {
    {nullptr}
};

static PyObject* PyCircle_translate(PyCircleObject* self, PyObject* args, PyObject* kwargs) {
    static const char* kwlist[] = {"dx", "dy", nullptr};

    long dx, dy;

    if (!PyArg_ParseTupleAndKeywords(
            args,
            kwargs,
            "ll",
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

// Polygon

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

        long x = PyLong_AsLong(xObj);
        long y = PyLong_AsLong(yObj);

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

    long dx, dy;

    if (!PyArg_ParseTupleAndKeywords(
            args,
            kwargs,
            "ll",
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
