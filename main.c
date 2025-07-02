#include <Python.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    PyObject *pModule, *pFunc, *pValue;

    // Initialize Python interpreter
    Py_Initialize();

    // Add current directory to sys.path so Python can find libtest.so
    PyRun_SimpleString("import sys; sys.path.insert(0, '.')");

    // Import libtest
    pModule = PyImport_ImportModule("libtest");
    if (!pModule) {
        PyErr_Print();
        fprintf(stderr, "Failed to load libtest\n");
        return 1;
    }

    // Call get_foo
    pFunc = PyObject_GetAttrString(pModule, "get_foo");
    if (pFunc && PyCallable_Check(pFunc)) {
        pValue = PyObject_CallObject(pFunc, NULL);
        if (pValue) {
            printf("get_foo returned: %s\n", PyUnicode_AsUTF8(pValue));
            Py_DECREF(pValue);
        } else {
            PyErr_Print();
        }
        Py_DECREF(pFunc);
    } else {
        PyErr_Print();
    }

    // Call get_bar
    pFunc = PyObject_GetAttrString(pModule, "get_bar");
    if (pFunc && PyCallable_Check(pFunc)) {
        pValue = PyObject_CallObject(pFunc, NULL);
        if (pValue) {
            printf("get_bar returned: %s\n", PyUnicode_AsUTF8(pValue));
            Py_DECREF(pValue);
        } else {
            PyErr_Print();
        }
        Py_DECREF(pFunc);
    } else {
        PyErr_Print();
    }

    Py_DECREF(pModule);

    Py_Finalize();
    return 0;
}