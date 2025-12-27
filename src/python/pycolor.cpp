#include "pycolor.h"

static uint8_t getColorAspectFromLong(unsigned long valueLong) {
    if (valueLong < 0 || valueLong > 255) {
        PyErr_SetString(PyExc_ValueError, "rgb value must be in range [0, 255]");
        throw -1;
    }

    return static_cast<uint8_t>(valueLong);
}

static int PyColor_init(PyColorObject *self, PyObject *args, PyObject *kwargs) {
    static const char *kwlist[] = {"red", "green", "blue", NULL};
    unsigned long red, green, blue;
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iii", const_cast<char **>(kwlist), &red, &green, &blue)) {
        return -1;
    }

    try {
        uint8_t colorRed = getColorAspectFromLong(red);
        uint8_t colorGreen = getColorAspectFromLong(green);
        uint8_t colorBlue = getColorAspectFromLong(blue);
        self->color = std::make_unique<RgbColor>(colorRed, colorGreen, colorBlue);
    } catch (int e) {
        return -1;
    }

    return 0;
}


static void PyColor_dealloc(PyColorObject *self) {
    self->color.reset();
    Py_TYPE(self)->tp_free((PyObject *)self);
}


static PyObject* PyColor_getRed(PyColorObject *self, void *closure) {
    if (!self->color) {
        PyErr_SetString(PyExc_RuntimeError, "Color object is not initialized");
        return nullptr;
    }
    return PyLong_FromUnsignedLong(self->color->red);
}

static PyObject* PyColor_getGreen(PyColorObject *self, void *closure) {
    if (!self->color) {
        PyErr_SetString(PyExc_RuntimeError, "Color object is not initialized");
        return nullptr;
    }
    return PyLong_FromUnsignedLong(self->color->green);
}

static PyObject* PyColor_getBlue(PyColorObject *self, void *closure) {
    if (!self->color) {
        PyErr_SetString(PyExc_RuntimeError, "Color object is not initialized");
        return nullptr;
    }
    return PyLong_FromUnsignedLong(self->color->blue);
}

static uint8_t getColorAspectFromPyObject(PyObject *value) {
    if (value == nullptr || !value) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete rgb attribute");
        throw -1;
    }

    unsigned long valueLong = PyLong_AsUnsignedLong(value);
    if (valueLong == (uint8_t)-1 && PyErr_Occurred()) {
        throw -1;
    }

    return getColorAspectFromLong(valueLong);
}

static int PyColor_setRed(PyColorObject *self, PyObject *value, void *closure) {
    if (!self->color) {
        PyErr_SetString(PyExc_RuntimeError, "Color object is not initialized");
        return -1;
    }

    try {
        self->color->red = getColorAspectFromPyObject(value);
    } catch (int e) {
        return -1;
    }

    return 0;
}

static int PyColor_setGreen(PyColorObject *self, PyObject *value, void *closure) {
    if (!self->color) {
        PyErr_SetString(PyExc_RuntimeError, "Color object is not initialized");
        return -1;
    }

    try {
        self->color->green = getColorAspectFromPyObject(value);
    } catch (int e) {
        return -1;
    }

    return 0;
}

static int PyColor_setBlue(PyColorObject *self, PyObject *value, void *closure) {
    if (!self->color) {
        PyErr_SetString(PyExc_RuntimeError, "Color object is not initialized");
        return -1;
    }

    try {
        self->color->blue = getColorAspectFromPyObject(value);
    } catch (int e) {
        return -1;
    }

    return 0;
}


static PyGetSetDef PyColor_getset[] = {
    {"red", (getter)PyColor_getRed, (setter)PyColor_setRed, "Red color component (0-255)", nullptr},
    {"green", (getter)PyColor_getGreen, (setter)PyColor_setGreen, "Green color component (0-255)", nullptr},
    {"blue", (getter)PyColor_getBlue, (setter)PyColor_setBlue, "Blue color component (0-255)", nullptr},
    {nullptr}
};


PyTypeObject PyColorType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
};

// Todo: Call this function during module initialization
void init_PyColorType() {
    PyColorType.tp_name = "pyartkitcpp.Color";
    PyColorType.tp_basicsize = sizeof(PyColorObject);
    PyColorType.tp_itemsize = 0;
    PyColorType.tp_dealloc = (destructor)PyColor_dealloc;
    PyColorType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    PyColorType.tp_doc = "RGB Color object";
    PyColorType.tp_init = (initproc)PyColor_init;
    PyColorType.tp_new = PyType_GenericNew;
    PyColorType.tp_getset = PyColor_getset;
}

