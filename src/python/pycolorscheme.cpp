
#include "pycolorscheme.h"
#include <stdexcept>

// * ---------- PyColorScheme ---------- * //

static int PyColorScheme_init(PyColorSchemeObject *self, PyObject *args, PyObject *kwargs) {
    PyErr_SetString(PyExc_RuntimeError, "Cannot instantiate abstract ColorScheme class");
    return -1;
}

PyTypeObject PyColorSchemeType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
};

static void PyColorScheme_dealloc(PyColorSchemeObject* self) {
    self->scheme.reset();
    Py_TYPE(self)->tp_free((PyObject*)self);
}

void init_PyColorSchemeType() {
    PyColorSchemeType.tp_name = "pyartkitcpp.ColorScheme";
    PyColorSchemeType.tp_basicsize = sizeof(PyColorSchemeObject);
    PyColorSchemeType.tp_itemsize = 0;
    PyColorSchemeType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    PyColorSchemeType.tp_doc = "Abstract ColorScheme class";
    PyColorSchemeType.tp_init = (initproc)PyColorScheme_init;
    PyColorSchemeType.tp_new = PyType_GenericNew;
    PyColorSchemeType.tp_dealloc = (destructor)PyColorScheme_dealloc;
}


// * ---------- PyStaticColorScheme ---------- * //

static int PyStaticColorScheme_init(PyStaticColorSchemeObject *self, PyObject *args, PyObject *kwargs) {
    static const char *kwlist[] = {"color", NULL};
    PyObject *colorObj = nullptr;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O", const_cast<char **>(kwlist), &colorObj)) {
        return -1;
    }

    if (!PyColor_Check(colorObj)) {
        PyErr_SetString(PyExc_TypeError, "color must be a Color object");
        return -1;
    }

    try {
        self->base.scheme = std::make_shared<StaticColorScheme>(*reinterpret_cast<PyColorObject *>(colorObj)->color.get());
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to create StaticColorScheme object");
        return -1;
    }

    return 0;
}

static PyObject* PyStaticColorScheme_setColor(PyStaticColorSchemeObject* self, PyObject* args, PyObject* kwargs) {
    static const char* kwlist[] = {"color", nullptr};
    PyObject* colorObj = nullptr;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O", const_cast<char**>(kwlist), &colorObj)) {
        return nullptr;
    }

    if (!PyColor_Check(colorObj)) {
        PyErr_SetString(PyExc_TypeError, "color must be a Color object");
        return nullptr;
    }

    try {
        self->base.scheme = std::make_shared<StaticColorScheme>(*reinterpret_cast<PyColorObject*>(colorObj)->color.get());
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to update StaticColorScheme color");
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyMethodDef PyStaticColorScheme_methods[] = {
    {"set_color", (PyCFunction)PyStaticColorScheme_setColor, METH_VARARGS | METH_KEYWORDS, "Set the color for the static color scheme"},
    {nullptr}
};

PyTypeObject PyStaticColorSchemeType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
};

void init_PyStaticColorSchemeType() {
    PyStaticColorSchemeType.tp_name = "pyartkitcpp.StaticColorScheme";
    PyStaticColorSchemeType.tp_basicsize = sizeof(PyStaticColorSchemeObject);
    PyStaticColorSchemeType.tp_itemsize = 0;
    PyStaticColorSchemeType.tp_flags = Py_TPFLAGS_DEFAULT;
    PyStaticColorSchemeType.tp_doc = "Static color scheme with a single color";
    PyStaticColorSchemeType.tp_init = (initproc)PyStaticColorScheme_init;
    PyStaticColorSchemeType.tp_new = PyType_GenericNew;
    PyStaticColorSchemeType.tp_methods = PyStaticColorScheme_methods;
}

// * ---------- PyHorizontalGradientColorScheme ---------- * //

static int PyHorizontalGradientColorScheme_init(PyHorizontalGradientColorSchemeObject *self, PyObject *args, PyObject *kwargs) {
    static const char *kwlist[] = {"left_color", "right_color", "left_bound", "right_bound", NULL};
    PyObject *leftColorObj = nullptr, *rightColorObj = nullptr;
    int leftBound, rightBound;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OOii", const_cast<char **>(kwlist),
                                     &leftColorObj, &rightColorObj, &leftBound, &rightBound)) {
        return -1;
    }

    if (!PyColor_Check(leftColorObj) || !PyColor_Check(rightColorObj)) {
        PyErr_SetString(PyExc_TypeError, "left_color and right_color must be Color objects");
        return -1;
    }

    try {
        self->base.scheme = std::make_shared<HorizontalGradientColorScheme>(
            leftBound,
            rightBound,
            *reinterpret_cast<PyColorObject *>(leftColorObj)->color.get(),
            *reinterpret_cast<PyColorObject *>(rightColorObj)->color.get()
        );
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to create HorizontalGradientColorScheme object");
        return -1;
    }

    return 0;
}

static PyObject* PyHorizontalGradientColorScheme_setLeftColor(PyHorizontalGradientColorSchemeObject* self, PyObject* args, PyObject* kwargs) {
    static const char* kwlist[] = {"color", nullptr};
    PyObject* colorObj = nullptr;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O", const_cast<char**>(kwlist), &colorObj)) {
        return nullptr;
    }

    if (!PyColor_Check(colorObj)) {
        PyErr_SetString(PyExc_TypeError, "color must be a Color object");
        return nullptr;
    }

    try {
        auto currentScheme = std::dynamic_pointer_cast<HorizontalGradientColorScheme>(self->base.scheme);
        if (!currentScheme) {
            PyErr_SetString(PyExc_RuntimeError, "Current color scheme is not a HorizontalGradientColorScheme");
            return nullptr;
        }
        currentScheme->setLeftColor(*reinterpret_cast<PyColorObject*>(colorObj)->color.get());
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to update HorizontalGradientColorScheme left color");
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* PyHorizontalGradientColorScheme_setRightColor(PyHorizontalGradientColorSchemeObject* self, PyObject* args, PyObject* kwargs) {
    static const char* kwlist[] = {"color", nullptr};
    PyObject* colorObj = nullptr;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O", const_cast<char**>(kwlist), &colorObj)) {
        return nullptr;
    }

    if (!PyColor_Check(colorObj)) {
        PyErr_SetString(PyExc_TypeError, "color must be a Color object");
        return nullptr;
    }

    try {
        auto currentScheme = std::dynamic_pointer_cast<HorizontalGradientColorScheme>(self->base.scheme);
        if (!currentScheme) {
            PyErr_SetString(PyExc_RuntimeError, "Current color scheme is not a HorizontalGradientColorScheme");
            return nullptr;
        }
        currentScheme->setRightColor(*reinterpret_cast<PyColorObject*>(colorObj)->color.get());
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to update HorizontalGradientColorScheme right color");
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* PyHorizontalGradientColorScheme_setLeftBound(PyHorizontalGradientColorSchemeObject* self, PyObject* args, PyObject* kwargs) {
    static const char* kwlist[] = {"bound", nullptr};
    int bound;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i", const_cast<char**>(kwlist), &bound)) {
        return nullptr;
    }

    try {
        auto currentScheme = std::dynamic_pointer_cast<HorizontalGradientColorScheme>(self->base.scheme);
        if (!currentScheme) {
            PyErr_SetString(PyExc_RuntimeError, "Current color scheme is not a HorizontalGradientColorScheme");
            return nullptr;
        }
        currentScheme->setBounds(bound, currentScheme->getRightBound());
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to update HorizontalGradientColorScheme left bound");
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* PyHorizontalGradientColorScheme_setRightBound(PyHorizontalGradientColorSchemeObject* self, PyObject* args, PyObject* kwargs) {
    static const char* kwlist[] = {"bound", nullptr};
    int bound;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i", const_cast<char**>(kwlist), &bound)) {
        return nullptr;
    }

    try {
        auto currentScheme = std::dynamic_pointer_cast<HorizontalGradientColorScheme>(self->base.scheme);
        if (!currentScheme) {
            PyErr_SetString(PyExc_RuntimeError, "Current color scheme is not a HorizontalGradientColorScheme");
            return nullptr;
        }
        currentScheme->setBounds(currentScheme->getLeftBound(), bound);
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to update HorizontalGradientColorScheme right bound");
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyMethodDef PyHorizontalGradientColorScheme_methods[] = {
    {"set_left_color", (PyCFunction)PyHorizontalGradientColorScheme_setLeftColor, METH_VARARGS | METH_KEYWORDS, "Set the left color for the horizontal gradient color scheme"},
    {"set_right_color", (PyCFunction)PyHorizontalGradientColorScheme_setRightColor, METH_VARARGS | METH_KEYWORDS, "Set the right color for the horizontal gradient color scheme"},
    {"set_left_bound", (PyCFunction)PyHorizontalGradientColorScheme_setLeftBound, METH_VARARGS | METH_KEYWORDS, "Set the left bound for the horizontal gradient color scheme"},
    {"set_right_bound", (PyCFunction)PyHorizontalGradientColorScheme_setRightBound, METH_VARARGS | METH_KEYWORDS, "Set the right bound for the horizontal gradient color scheme"},
    {nullptr}
};

PyTypeObject PyHorizontalGradientColorSchemeType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
};

void init_PyHorizontalGradientColorSchemeType() {
    PyHorizontalGradientColorSchemeType.tp_name = "pyartkitcpp.HorizontalGradientColorScheme";
    PyHorizontalGradientColorSchemeType.tp_basicsize = sizeof(PyHorizontalGradientColorSchemeObject);
    PyHorizontalGradientColorSchemeType.tp_itemsize = 0;
    PyHorizontalGradientColorSchemeType.tp_flags = Py_TPFLAGS_DEFAULT;
    PyHorizontalGradientColorSchemeType.tp_doc = "Horizontal gradient color scheme with left and right colors and bounds";
    PyHorizontalGradientColorSchemeType.tp_init = (initproc)PyHorizontalGradientColorScheme_init;
    PyHorizontalGradientColorSchemeType.tp_new = PyType_GenericNew;
    PyHorizontalGradientColorSchemeType.tp_methods = PyHorizontalGradientColorScheme_methods;
}

// * ---------- PyVerticalGradientColorScheme ---------- * //

static int PyVerticalGradientColorScheme_init(PyVerticalGradientColorSchemeObject *self, PyObject *args, PyObject *kwargs) {
    static const char *kwlist[] = {"top_color", "bottom_color", "top_bound", "bottom_bound", NULL};
    PyObject *topColorObj = nullptr, *bottomColorObj = nullptr;
    int topBound, bottomBound;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OOii", const_cast<char **>(kwlist),
                                     &topColorObj, &bottomColorObj, &topBound, &bottomBound)) {
        return -1;
    }

    if (!PyColor_Check(topColorObj) || !PyColor_Check(bottomColorObj)) {
        PyErr_SetString(PyExc_TypeError, "top_color and bottom_color must be Color objects");
        return -1;
    }

    try {
        self->base.scheme = std::make_shared<VerticalGradientColorScheme>(
            topBound,
            bottomBound,
            *reinterpret_cast<PyColorObject *>(topColorObj)->color.get(),
            *reinterpret_cast<PyColorObject *>(bottomColorObj)->color.get()
        );
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to create VerticalGradientColorScheme object");
        return -1;
    }

    return 0;
}

static PyObject* PyVerticalGradientColorScheme_setTopColor(PyVerticalGradientColorSchemeObject* self, PyObject* args, PyObject* kwargs) {
    static const char* kwlist[] = {"color", nullptr};
    PyObject* colorObj = nullptr;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O", const_cast<char**>(kwlist), &colorObj)) {
        return nullptr;
    }

    if (!PyColor_Check(colorObj)) {
        PyErr_SetString(PyExc_TypeError, "color must be a Color object");
        return nullptr;
    }

    try {
        auto currentScheme = std::dynamic_pointer_cast<VerticalGradientColorScheme>(self->base.scheme);
        if (!currentScheme) {
            PyErr_SetString(PyExc_RuntimeError, "Current color scheme is not a VerticalGradientColorScheme");
            return nullptr;
        }
        currentScheme->setTopColor(*reinterpret_cast<PyColorObject*>(colorObj)->color.get());
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to update VerticalGradientColorScheme top color");
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* PyVerticalGradientColorScheme_setBottomColor(PyVerticalGradientColorSchemeObject* self, PyObject* args, PyObject* kwargs) {
    static const char* kwlist[] = {"color", nullptr};
    PyObject* colorObj = nullptr;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O", const_cast<char**>(kwlist), &colorObj)) {
        return nullptr;
    }

    if (!PyColor_Check(colorObj)) {
        PyErr_SetString(PyExc_TypeError, "color must be a Color object");
        return nullptr;
    }

    try {
        auto currentScheme = std::dynamic_pointer_cast<VerticalGradientColorScheme>(self->base.scheme);
        if (!currentScheme) {
            PyErr_SetString(PyExc_RuntimeError, "Current color scheme is not a VerticalGradientColorScheme");
            return nullptr;
        }
        currentScheme->setBottomColor(*reinterpret_cast<PyColorObject*>(colorObj)->color.get());
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to update VerticalGradientColorScheme bottom color");
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* PyVerticalGradientColorScheme_setTopBound(PyVerticalGradientColorSchemeObject* self, PyObject* args, PyObject* kwargs) {
    static const char* kwlist[] = {"bound", nullptr};
    int bound;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i", const_cast<char**>(kwlist), &bound)) {
        return nullptr;
    }

    try {
        auto currentScheme = std::dynamic_pointer_cast<VerticalGradientColorScheme>(self->base.scheme);
        if (!currentScheme) {
            PyErr_SetString(PyExc_RuntimeError, "Current color scheme is not a VerticalGradientColorScheme");
            return nullptr;
        }
        currentScheme->setBounds(bound, currentScheme->getBottomBound());
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to update VerticalGradientColorScheme top bound");
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* PyVerticalGradientColorScheme_setBottomBound(PyVerticalGradientColorSchemeObject* self, PyObject* args, PyObject* kwargs) {
    static const char* kwlist[] = {"bound", nullptr};
    int bound;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i", const_cast<char**>(kwlist), &bound)) {
        return nullptr;
    }

    try {
        auto currentScheme = std::dynamic_pointer_cast<VerticalGradientColorScheme>(self->base.scheme);
        if (!currentScheme) {
            PyErr_SetString(PyExc_RuntimeError, "Current color scheme is not a VerticalGradientColorScheme");
            return nullptr;
        }
        currentScheme->setBounds(currentScheme->getTopBound(), bound);
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to update VerticalGradientColorScheme bottom bound");
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyMethodDef PyVerticalGradientColorScheme_methods[] = {
    {"set_top_color", (PyCFunction)PyVerticalGradientColorScheme_setTopColor, METH_VARARGS | METH_KEYWORDS, "Set the top color for the vertical gradient color scheme"},
    {"set_bottom_color", (PyCFunction)PyVerticalGradientColorScheme_setBottomColor, METH_VARARGS | METH_KEYWORDS, "Set the bottom color for the vertical gradient color scheme"},
    {"set_top_bound", (PyCFunction)PyVerticalGradientColorScheme_setTopBound, METH_VARARGS | METH_KEYWORDS, "Set the top bound for the vertical gradient color scheme"},
    {"set_bottom_bound", (PyCFunction)PyVerticalGradientColorScheme_setBottomBound, METH_VARARGS | METH_KEYWORDS, "Set the bottom bound for the vertical gradient color scheme"},
    {nullptr}
};

PyTypeObject PyVerticalGradientColorSchemeType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
};

void init_PyVerticalGradientColorSchemeType() {
    PyVerticalGradientColorSchemeType.tp_name = "pyartkitcpp.VerticalGradientColorScheme";
    PyVerticalGradientColorSchemeType.tp_basicsize = sizeof(PyVerticalGradientColorSchemeObject);
    PyVerticalGradientColorSchemeType.tp_itemsize = 0;
    PyVerticalGradientColorSchemeType.tp_flags = Py_TPFLAGS_DEFAULT;
    PyVerticalGradientColorSchemeType.tp_doc = "Vertical gradient color scheme with top and bottom colors and bounds";
    PyVerticalGradientColorSchemeType.tp_init = (initproc)PyVerticalGradientColorScheme_init;
    PyVerticalGradientColorSchemeType.tp_new = PyType_GenericNew;
    PyVerticalGradientColorSchemeType.tp_methods = PyVerticalGradientColorScheme_methods;
}

// * ---------- PyRadialGradientColorScheme ---------- * //

static int PyRadialGradientColorScheme_init(PyRadialGradientColorSchemeObject *self, PyObject *args, PyObject *kwargs) {
    static const char* kwlist[] = {"center_color", "edge_color", "center_x", "center_y", "radius", NULL};
    PyObject *centerColorObj = nullptr, *edgeColorObj = nullptr;
    int centerX, centerY, radius;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OOiii", const_cast<char**>(kwlist),
                                     &centerColorObj, &edgeColorObj, &centerX, &centerY, &radius)) {
        return -1;
    }

    if (!PyColor_Check(centerColorObj) || !PyColor_Check(edgeColorObj)) {
        PyErr_SetString(PyExc_TypeError, "center_color and edge_color must be Color objects");
        return -1;
    }

    try {
        self->base.scheme = std::make_shared<RadialGradientColorScheme>(
            centerX,
            centerY,
            radius,
            *reinterpret_cast<PyColorObject *>(centerColorObj)->color.get(),
            *reinterpret_cast<PyColorObject *>(edgeColorObj)->color.get()
        );
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to create RadialGradientColorScheme object");
        return -1;
    }

    return 0;
}

static PyObject* PyRadialGradientColorScheme_setCenterColor(PyRadialGradientColorSchemeObject* self, PyObject* args, PyObject* kwargs) {
    static const char* kwlist[] = {"color", nullptr};
    PyObject* colorObj = nullptr;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O", const_cast<char**>(kwlist), &colorObj)) {
        return nullptr;
    }

    if (!PyColor_Check(colorObj)) {
        PyErr_SetString(PyExc_TypeError, "color must be a Color object");
        return nullptr;
    }
    try {
        auto currentScheme = std::dynamic_pointer_cast<RadialGradientColorScheme>(self->base.scheme);
        if (!currentScheme) {
            PyErr_SetString(PyExc_RuntimeError, "Current color scheme is not a RadialGradientColorScheme");
            return nullptr;
        }
        currentScheme->setCenterColor(*reinterpret_cast<PyColorObject*>(colorObj)->color.get());
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to update RadialGradientColorScheme center color");
        return nullptr;
    }
    
    Py_RETURN_NONE;
}

static PyObject* PyRadialGradientColorScheme_setEdgeColor(PyRadialGradientColorSchemeObject* self, PyObject* args, PyObject* kwargs) {
    static const char* kwlist[] = {"color", nullptr};
    PyObject* colorObj = nullptr;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O", const_cast<char**>(kwlist), &colorObj)) {
        return nullptr;
    }

    if (!PyColor_Check(colorObj)) {
        PyErr_SetString(PyExc_TypeError, "color must be a Color object");
        return nullptr;
    }
    try {
        auto currentScheme = std::dynamic_pointer_cast<RadialGradientColorScheme>(self->base.scheme);
        if (!currentScheme) {
            PyErr_SetString(PyExc_RuntimeError, "Current color scheme is not a RadialGradientColorScheme");
            return nullptr;
        }
        currentScheme->setEdgeColor(*reinterpret_cast<PyColorObject*>(colorObj)->color.get());
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to update RadialGradientColorScheme edge color");
        return nullptr;
    }
    
    Py_RETURN_NONE;
}

static PyObject* PyRadialGradientColorScheme_setCenter(PyRadialGradientColorSchemeObject* self, PyObject* args, PyObject* kwargs) {
    static const char* kwlist[] = {"center_x", "center_y", nullptr};
    int centerX, centerY;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii", const_cast<char**>(kwlist), &centerX, &centerY)) {
        return nullptr;
    }

    try {
        auto currentScheme = std::dynamic_pointer_cast<RadialGradientColorScheme>(self->base.scheme);
        if (!currentScheme) {
            PyErr_SetString(PyExc_RuntimeError, "Current color scheme is not a RadialGradientColorScheme");
            return nullptr;
        }
        currentScheme->setCenter(centerX, centerY);
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to update RadialGradientColorScheme center");
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyObject* PyRadialGradientColorScheme_setRadius(PyRadialGradientColorSchemeObject* self, PyObject* args, PyObject* kwargs) {
    static const char* kwlist[] = {"radius", nullptr};
    int radius;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "i", const_cast<char**>(kwlist), &radius)) {
        return nullptr;
    }

    try {
        auto currentScheme = std::dynamic_pointer_cast<RadialGradientColorScheme>(self->base.scheme);
        if (!currentScheme) {
            PyErr_SetString(PyExc_RuntimeError, "Current color scheme is not a RadialGradientColorScheme");
            return nullptr;
        }
        currentScheme->setRadius(radius);
    } catch (...) {
        PyErr_SetString(PyExc_RuntimeError, "Failed to update RadialGradientColorScheme radius");
        return nullptr;
    }

    Py_RETURN_NONE;
}

static PyMethodDef PyRadialGradientColorScheme_methods[] = {
    {"set_center_color", (PyCFunction)PyRadialGradientColorScheme_setCenterColor, METH_VARARGS | METH_KEYWORDS, "Set the center color for the radial gradient color scheme"},
    {"set_edge_color", (PyCFunction)PyRadialGradientColorScheme_setEdgeColor, METH_VARARGS | METH_KEYWORDS, "Set the edge color for the radial gradient color scheme"},
    {"set_center", (PyCFunction)PyRadialGradientColorScheme_setCenter, METH_VARARGS | METH_KEYWORDS, "Set the center coordinates for the radial gradient color scheme"},
    {"set_radius", (PyCFunction)PyRadialGradientColorScheme_setRadius, METH_VARARGS | METH_KEYWORDS, "Set the radius for the radial gradient color scheme"},
    {nullptr}
};

PyTypeObject PyRadialGradientColorSchemeType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
};

void init_PyRadialGradientColorSchemeType() {
    PyRadialGradientColorSchemeType.tp_name = "pyartkitcpp.RadialGradientColorScheme";
    PyRadialGradientColorSchemeType.tp_basicsize = sizeof(PyRadialGradientColorSchemeObject);
    PyRadialGradientColorSchemeType.tp_itemsize = 0;
    PyRadialGradientColorSchemeType.tp_flags = Py_TPFLAGS_DEFAULT;
    PyRadialGradientColorSchemeType.tp_doc = "Radial gradient color scheme with center and edge colors, center coordinates, and radius";
    PyRadialGradientColorSchemeType.tp_init = (initproc)PyRadialGradientColorScheme_init;
    PyRadialGradientColorSchemeType.tp_new = PyType_GenericNew;
    PyRadialGradientColorSchemeType.tp_methods = PyRadialGradientColorScheme_methods;
}


// * ---------- PyModule initColorSchemes ---------- * //

void initColorSchemes(PyObject* pymod) {
    init_PyColorSchemeType();
    init_PyStaticColorSchemeType();
    init_PyHorizontalGradientColorSchemeType();
    init_PyVerticalGradientColorSchemeType();
    init_PyRadialGradientColorSchemeType();

    PyHorizontalGradientColorSchemeType.tp_base = &PyColorSchemeType;
    PyVerticalGradientColorSchemeType.tp_base = &PyColorSchemeType;
    PyStaticColorSchemeType.tp_base = &PyColorSchemeType;
    PyRadialGradientColorSchemeType.tp_base = &PyColorSchemeType;

    if (PyType_Ready(&PyColorSchemeType) < 0) {
        throw std::runtime_error("Failed to initialize ColorScheme type");
    }
    if (PyType_Ready(&PyStaticColorSchemeType) < 0) {
        throw std::runtime_error("Failed to initialize StaticColorScheme type");
    }
    if (PyType_Ready(&PyHorizontalGradientColorSchemeType) < 0) {
        throw std::runtime_error("Failed to initialize HorizontalGradientColorScheme type");
    }
    if (PyType_Ready(&PyVerticalGradientColorSchemeType) < 0) {
        throw std::runtime_error("Failed to initialize VerticalGradientColorScheme type");
    }
    if (PyType_Ready(&PyRadialGradientColorSchemeType) < 0) {
        throw std::runtime_error("Failed to initialize RadialGradientColorScheme type");
    }

    Py_INCREF(&PyColorSchemeType);
    Py_INCREF(&PyStaticColorSchemeType);
    Py_INCREF(&PyHorizontalGradientColorSchemeType);
    Py_INCREF(&PyVerticalGradientColorSchemeType);
    Py_INCREF(&PyRadialGradientColorSchemeType);

    PyModule_AddObject(pymod, "ColorScheme", (PyObject*)&PyColorSchemeType);
    PyModule_AddObject(pymod, "StaticColorScheme", (PyObject*)&PyStaticColorSchemeType);
    PyModule_AddObject(pymod, "HorizontalGradientColorScheme", (PyObject*)&PyHorizontalGradientColorSchemeType);
    PyModule_AddObject(pymod, "VerticalGradientColorScheme", (PyObject*)&PyVerticalGradientColorSchemeType);
    PyModule_AddObject(pymod, "RadialGradientColorScheme", (PyObject*)&PyRadialGradientColorSchemeType);
}
