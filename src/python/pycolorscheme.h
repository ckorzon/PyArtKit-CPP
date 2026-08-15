
#ifndef PYCOLORSCHEME_H
#define PYCOLORSCHEME_H

#include "pycolor.h"
#include "colorscheme.h"

#ifdef __cplusplus
extern "C" {
#endif

// PyColorSchemeObject (Abstract base for all color schemes)

// ToDo: Ideally, we want to be able to adjust the color for any scheme on the fly, so having a static scheme associated
// with a color scheme object is not ideal. It would be better to have an abstract method that retrieves the current color scheme, and then have the specific color scheme types implement that method to return their current scheme.
// This way, we can adjust the parameters of the color scheme (like the colors for a gradient) and have the getColorScheme method return the updated scheme without needing to create a new object.

typedef struct {
    PyObject_HEAD
    std::shared_ptr<ColorScheme> scheme;
} PyColorSchemeObject;

extern PyTypeObject PyColorSchemeType;
extern void init_PyColorSchemeType();
#define PyColorScheme_Check(op) PyObject_TypeCheck(op, &PyColorSchemeType)

// PyStaticColorSchemeObject
typedef struct {
    PyColorSchemeObject base;
} PyStaticColorSchemeObject;

extern PyTypeObject PyStaticColorSchemeType;
extern void init_PyStaticColorSchemeType();
#define PyStaticColorScheme_Check(op) PyObject_TypeCheck(op, &PyStaticColorSchemeType)

// PyHorizontalGradientColorSchemeObject
typedef struct {
    PyColorSchemeObject base;
} PyHorizontalGradientColorSchemeObject;
extern PyTypeObject PyHorizontalGradientColorSchemeType;
extern void init_PyHorizontalGradientColorSchemeType();
#define PyHorizontalGradientColorScheme_Check(op) PyObject_TypeCheck(op, &PyHorizontalGradientColorSchemeType)

// PyVerticalGradientColorSchemeObject
typedef struct {
    PyColorSchemeObject base;
} PyVerticalGradientColorSchemeObject;
extern PyTypeObject PyVerticalGradientColorSchemeType;
extern void init_PyVerticalGradientColorSchemeType();
#define PyVerticalGradientColorScheme_Check(op) PyObject_TypeCheck(op, &PyVerticalGradientColorSchemeType)

// PyRadialGradientColorSchemeObject
typedef struct {
    PyColorSchemeObject base;
} PyRadialGradientColorSchemeObject;
extern PyTypeObject PyRadialGradientColorSchemeType;
extern void init_PyRadialGradientColorSchemeType();
#define PyRadialGradientColorScheme_Check(op) PyObject_TypeCheck(op, &PyRadialGradientColorSchemeType)


void initColorSchemes(PyObject* pymod);

#ifdef __cplusplus
}
#endif

#endif // PYCOLORSCHEME_H
