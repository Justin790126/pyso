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

    // Call process_list([1, 2, 3])
    pFunc = PyObject_GetAttrString(pModule, "process_list");
    if (pFunc && PyCallable_Check(pFunc)) {
        PyObject *pList = PyList_New(3);
        PyList_SetItem(pList, 0, PyLong_FromLong(1));
        PyList_SetItem(pList, 1, PyLong_FromLong(2));
        PyList_SetItem(pList, 2, PyLong_FromLong(3));
        PyObject *pArgs = PyTuple_Pack(1, pList);
        pValue = PyObject_CallObject(pFunc, pArgs);
        if (pValue) {
            printf("process_list([1,2,3]) returned: %ld\n", PyLong_AsLong(pValue));
            Py_DECREF(pValue);
        } else {
            PyErr_Print();
        }
        Py_DECREF(pArgs);
        Py_DECREF(pList);
        Py_DECREF(pFunc);
    } else {
        PyErr_Print();
    }

    // Call process_dict({'a': 1, 'b': 2})
    pFunc = PyObject_GetAttrString(pModule, "process_dict");
    if (pFunc && PyCallable_Check(pFunc)) {
        PyObject *pDict = PyDict_New();
        PyDict_SetItemString(pDict, "a", PyLong_FromLong(1));
        PyDict_SetItemString(pDict, "b", PyLong_FromLong(2));
        PyObject *pArgs = PyTuple_Pack(1, pDict);
        pValue = PyObject_CallObject(pFunc, pArgs);
        if (pValue) {
            printf("process_dict({'a':1,'b':2}) returned keys: ");
            Py_ssize_t len = PyList_Size(pValue);
            for (Py_ssize_t i = 0; i < len; ++i) {
                PyObject *item = PyList_GetItem(pValue, i);
                printf("%s ", PyUnicode_AsUTF8(item));
            }
            printf("\n");
            Py_DECREF(pValue);
        } else {
            PyErr_Print();
        }
        Py_DECREF(pArgs);
        Py_DECREF(pDict);
        Py_DECREF(pFunc);
    } else {
        PyErr_Print();
    }

    // Call process_class(foo.foo())
    pFunc = PyObject_GetAttrString(pModule, "process_class");
    if (pFunc && PyCallable_Check(pFunc)) {
        PyObject *fooModule = PyImport_ImportModule("foo");
        if (fooModule) {
            PyObject *fooFunc = PyObject_GetAttrString(fooModule, "foo");
            if (fooFunc && PyCallable_Check(fooFunc)) {
                PyObject *fooObj = PyObject_CallObject(fooFunc, NULL);
                if (fooObj) {
                    PyObject *pArgs = PyTuple_Pack(1, fooObj);
                    pValue = PyObject_CallObject(pFunc, pArgs);
                    if (pValue) {
                        printf("process_class(foo.foo()) returned: %s\n", PyUnicode_AsUTF8(pValue));
                        Py_DECREF(pValue);
                    } else {
                        PyErr_Print();
                    }
                    Py_DECREF(pArgs);
                    Py_DECREF(fooObj);
                } else {
                    PyErr_Print();
                }
                Py_DECREF(fooFunc);
            } else {
                PyErr_Print();
            }
            Py_DECREF(fooModule);
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