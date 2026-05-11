#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <Python.h>
#include <iostream>
#include "pyshapes.h"
// #include "pycolorscheme.h"

struct PythonFixture {
    PythonFixture() { Py_Initialize(); }
    ~PythonFixture() { Py_Finalize(); }
};

TEST_CASE_METHOD(PythonFixture, "Initialize Python") {
    REQUIRE(Py_IsInitialized());
}

TEST_CASE("Debug Python path") {

    Py_Initialize();

    PyObject* sysPath = PySys_GetObject("path"); // borrowed reference

    REQUIRE(sysPath != nullptr);

    PyObject* repr = PyObject_Repr(sysPath);
    REQUIRE(repr != nullptr);

    const char* pathStr = PyUnicode_AsUTF8(repr);

    std::cout << "\nPython sys.path:\n"
              << pathStr
              << "\n";

    Py_DECREF(repr);

    Py_Finalize();
}

TEST_CASE_METHOD(PythonFixture,"Test create mock module") {
    static struct PyModuleDef mock_pyartkitcpp_module = {
        PyModuleDef_HEAD_INIT,
        "mock_pyartkitcpp",
        "Mock pyartkitcpp module for testing initColorSchemes",
        -1,
        NULL
    };

    PyObject* module = PyModule_Create(&mock_pyartkitcpp_module);

    REQUIRE(module != nullptr);

    Py_DECREF(module);
}

TEST_CASE_METHOD(PythonFixture,"Test initShapes") {

    static struct PyModuleDef mock_pyartkitcpp_module = {
        PyModuleDef_HEAD_INIT,
        "mock_pyartkitcpp",
        "Mock pyartkitcpp module for testing initShapes",
        -1,
        NULL
    };

    PyObject* module = PyModule_Create(&mock_pyartkitcpp_module);

    initShapes(module);

    REQUIRE(module != nullptr);

    Py_DECREF(module);
}

TEST_CASE_METHOD(PythonFixture,"Test initColorSchemes") {

    static struct PyModuleDef mock_pyartkitcpp_module = {
        PyModuleDef_HEAD_INIT,
        "mock_pyartkitcpp",
        "Mock pyartkitcpp module for testing initColorSchemes",
        -1,
        NULL
    };

    PyObject* module = PyModule_Create(&mock_pyartkitcpp_module);

    initColorSchemes(module);

    REQUIRE(module != nullptr);

    Py_DECREF(module);
}

TEST_CASE_METHOD(PythonFixture,"Import pyartkitcpp module") {
    PyObject* moduleName = PyUnicode_FromString("pyartkitcpp");
    PyObject* module = PyImport_Import(moduleName);

    REQUIRE(module != nullptr);

    Py_DECREF(moduleName);
    Py_DECREF(module);
}

TEST_CASE_METHOD(PythonFixture, "Create PyColor Object") {

    PyObject* moduleName = PyUnicode_FromString("pyartkitcpp");
    PyObject* module = PyImport_Import(moduleName);
    REQUIRE(module != nullptr);

    PyObject* colorClass = PyObject_GetAttrString(module, "Color");
    REQUIRE(colorClass != nullptr);

    // Call constructor: Color(...)
    PyObject* args = PyTuple_New(3);
    PyTuple_SetItem(args, 0, PyLong_FromLong(255));
    PyTuple_SetItem(args, 1, PyLong_FromLong(0));
    PyTuple_SetItem(args, 2, PyLong_FromLong(0));
    PyObject* obj = PyObject_CallObject(colorClass, args);

    REQUIRE(obj != nullptr);

    Py_DECREF(args);
    Py_DECREF(obj);
    Py_DECREF(colorClass);
    Py_DECREF(module);
    Py_DECREF(moduleName);
}

TEST_CASE_METHOD(PythonFixture, "Create PyCanvas Object") {

    PyObject* moduleName = PyUnicode_FromString("pyartkitcpp");
    PyObject* module = PyImport_Import(moduleName);
    REQUIRE(module != nullptr);

    PyObject* colorClass = PyObject_GetAttrString(module, "Color");
    REQUIRE(colorClass != nullptr);

    // Create a Color object for the background color
    PyObject* colorArgs = PyTuple_New(3);
    PyTuple_SetItem(colorArgs, 0, PyLong_FromLong(255)); //
    PyTuple_SetItem(colorArgs, 1, PyLong_FromLong(255));
    PyTuple_SetItem(colorArgs, 2, PyLong_FromLong(255));
    PyObject* backgroundColor = PyObject_CallObject(colorClass, colorArgs);
    REQUIRE(backgroundColor != nullptr);

    PyObject* canvas = PyObject_GetAttrString(module, "Canvas");
    REQUIRE(canvas != nullptr);

    // Call constructor: Canvas(...)
    PyObject* args = PyTuple_New(3);
    PyTuple_SetItem(args, 0, PyLong_FromLong(800));
    PyTuple_SetItem(args, 1, PyLong_FromLong(600));
    PyTuple_SetItem(args, 2, backgroundColor);
    PyObject* obj = PyObject_CallObject(canvas, args);

    REQUIRE(obj != nullptr);

    Py_DECREF(args);
    Py_DECREF(obj);
    Py_DECREF(canvas);
    Py_DECREF(module);
    Py_DECREF(moduleName);
}

TEST_CASE_METHOD(PythonFixture, "Create PyStaticColorScheme object") {

    PyObject* moduleName = PyUnicode_FromString("pyartkitcpp");
    PyObject* module = PyImport_Import(moduleName);
    REQUIRE(module != nullptr);

    PyObject* colorClass = PyObject_GetAttrString(module, "Color");
    REQUIRE(colorClass != nullptr);

    // Create a Color object for the StaticColorScheme
    PyObject* colorArgs = PyTuple_New(3);
    PyTuple_SetItem(colorArgs, 0, PyLong_FromLong(0));
    PyTuple_SetItem(colorArgs, 1, PyLong_FromLong(255));
    PyTuple_SetItem(colorArgs, 2, PyLong_FromLong(0));
    PyObject* color = PyObject_CallObject(colorClass, colorArgs);
    REQUIRE(color != nullptr);

    PyObject* colorScheme = PyObject_GetAttrString(module, "StaticColorScheme");
    REQUIRE(colorScheme != nullptr);

    // Call constructor: StaticColorScheme(...)
    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, color);
    PyObject* obj = PyObject_CallObject(colorScheme, args);

    REQUIRE(obj != nullptr);

    Py_DECREF(args);
    Py_DECREF(obj);
    Py_DECREF(colorScheme);
    Py_DECREF(module);
    Py_DECREF(moduleName);
}
