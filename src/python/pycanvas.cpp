
#include "pycanvas.h"


static int PyCanvas_init(PyCanvasObject *self, PyObject *args, PyObject *kwargs) {

    static const char *kwlist[] = {"width", "height", "background_color", NULL};

    int width, height;
    PyObject* color_arg = nullptr;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii|O", const_cast<char **>(kwlist), &width, &height, &color_arg)) {
        return -1;
    }

    if (color_arg == nullptr) {
        self->canvas = std::make_unique<Canvas>(width, height);
        return 0;
    }

    if (!PyColor_Check(color_arg)) {
        PyErr_SetString(PyExc_TypeError, "background_color must be a Color object");
        return -1;
    }

    PyColorObject* color = reinterpret_cast<PyColorObject*>(color_arg);

    self->canvas = std::make_unique<Canvas>(width, height, *color->color);
    return 0;
}

static PyObject* PyCanvas_getWidth(PyCanvasObject *self, void *closure) {
    return PyLong_FromLong(self->canvas->getWidth());
}

static PyObject* PyCanvas_getHeight(PyCanvasObject *self, void *closure) {
    return PyLong_FromLong(self->canvas->getHeight());
}

static PyObject* PyCanvas_resize(PyCanvasObject *self, PyObject *args, PyObject *kwargs) {
    static const char *kwlist[] = {"new_width", "new_height", NULL};
    int new_width, new_height;
    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii", const_cast<char **>(kwlist), &new_width, &new_height)) {
        return NULL;
    }

    self->canvas->resize(new_width, new_height);
    Py_RETURN_NONE;
}

static PyObject* PyCanvas_setPixel(PyCanvasObject *self, PyObject *args, PyObject *kwargs) {
    
    static const char *kwlist[] = {"x", "y", "color", NULL};
    
    int x, y;
    PyObject* color_arg;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiO", const_cast<char **>(kwlist), &x, &y, &color_arg)) {
        return NULL;
    }

    if (!PyColor_Check(color_arg) && !PyColorScheme_Check(color_arg)) {
        PyErr_SetString(PyExc_TypeError, "color must be a Color or ColorScheme object");
        return NULL;
    }

    if (PyColorScheme_Check(color_arg)) {
        PyColorSchemeObject* colorScheme = reinterpret_cast<PyColorSchemeObject*>(color_arg);
        self->canvas->setPixel(x, y, colorScheme->scheme.get());
        Py_RETURN_NONE;
    }

    PyColorObject* color = reinterpret_cast<PyColorObject*>(color_arg);
    self->canvas->setPixel(x, y, color->color.get());
    Py_RETURN_NONE;
}

static PyObject* PyCanvas_addShape(PyCanvasObject* self, PyObject* args, PyObject *kwargs) {

    static const char *kwlist[] = {"shape", "fill_color", "border_color", NULL};

    PyObject* shape_obj;
    PyObject* fill_obj;
    PyObject* border_obj;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OOO", const_cast<char **>(kwlist), &shape_obj, &fill_obj, &border_obj)) {
        return nullptr;
    }

    if (!PyShape_Check(shape_obj)) {
        PyErr_SetString(PyExc_TypeError, "shape must be a Shape");
        return nullptr;
    }

    bool bothColorScheme = PyColorScheme_Check(border_obj) && PyColorScheme_Check(fill_obj);
    bool bothColor = PyColor_Check(border_obj) && PyColor_Check(fill_obj);

    if (!bothColorScheme && !bothColor) {
        PyErr_SetString(PyExc_TypeError, "border and fill must both be Color or both be ColorScheme objects");
        return nullptr;
    }

    PyShapeObject* pyShape = reinterpret_cast<PyShapeObject*>(shape_obj);

    if (bothColor) {
        PyColorObject* border = reinterpret_cast<PyColorObject*>(border_obj);
        PyColorObject* fill   = reinterpret_cast<PyColorObject*>(fill_obj);
        self->canvas->addShape(*pyShape->shape, fill->color.get(), border->color.get());
    } else {
        PyColorSchemeObject* border = reinterpret_cast<PyColorSchemeObject*>(border_obj);
        PyColorSchemeObject* fill   = reinterpret_cast<PyColorSchemeObject*>(fill_obj);
        self->canvas->addShape(*pyShape->shape, fill->scheme.get(), border->scheme.get());
    }

    Py_RETURN_NONE;
}

static PyObject* PyCanvas_toPng(PyCanvasObject *self, PyObject *args, PyObject *kwargs) {
    
    static const char *kwlist[] = {"filename", NULL};
    
    const char* filename;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s", const_cast<char **>(kwlist), &filename)) {
        return NULL;
    }

    self->canvas->toPNG(filename);
    Py_RETURN_NONE;
}

static PyGetSetDef PyCanvas_getseters[] = {
    {"width", (getter)PyCanvas_getWidth, NULL, "Get the width of the canvas", NULL},
    {"height", (getter)PyCanvas_getHeight, NULL, "Get the height of the canvas", NULL},
    {NULL}
};

static PyMethodDef PyCanvas_methods[] = {
    {"resize", (PyCFunction)PyCanvas_resize, METH_VARARGS | METH_KEYWORDS, "Resize the canvas"},
    {"set_pixel", (PyCFunction)PyCanvas_setPixel, METH_VARARGS | METH_KEYWORDS, "Set a pixel on the canvas"},
    {"to_png", (PyCFunction)PyCanvas_toPng, METH_VARARGS | METH_KEYWORDS, "Save the canvas as a PNG file"},
    {"add_shape", (PyCFunction)PyCanvas_addShape, METH_VARARGS | METH_KEYWORDS, "Draw a Shape on the canvas"},
    {NULL}
};

PyTypeObject PyCanvasType = {
    PyVarObject_HEAD_INIT(nullptr, 0)
};

void init_PyCanvasType() {
    PyCanvasType.tp_name = "canvas.Canvas";
    PyCanvasType.tp_basicsize = sizeof(PyCanvasObject);
    PyCanvasType.tp_itemsize = 0;
    PyCanvasType.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
    PyCanvasType.tp_new = PyType_GenericNew;
    PyCanvasType.tp_init = (initproc)PyCanvas_init;
    PyCanvasType.tp_methods = PyCanvas_methods;
    PyCanvasType.tp_getset = PyCanvas_getseters;
    PyCanvasType.tp_doc = 
        "Canvas(width: int, height: int, background_color=None)\n"
        "--\n\n"
        "Canvas class for drawing pixel art with support for directly setting pixels or adding shapes with specified fill and border colors or color schemes.";
}
