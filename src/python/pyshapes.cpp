
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

// ToDo: Add circle getters and setters

static PyGetSetDef PyCircle_getset[] = {
    {nullptr}
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
}

// Polygon


