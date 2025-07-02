# cython: language_level=3
# distutils: language = c
from cpython.ref cimport PyObject
from cpython.list cimport PyList_Check, PyList_Size
from cpython.dict cimport PyDict_Check
from libc.stdlib cimport malloc, free
import sys

# Import Python modules from src/
sys.path.insert(0, "src")
import foo
import bar

def get_foo():
    return foo.foo()

def get_bar():
    return bar.bar()

def process_list(py_list):
    """
    Accepts a Python list and returns its length.
    """
    if not PyList_Check(py_list):
        raise TypeError("Expected a Python list")
    return PyList_Size(py_list)

def process_dict(py_dict):
    """
    Accepts a Python dict and returns the list of keys.
    """
    if not PyDict_Check(py_dict):
        raise TypeError("Expected a Python dict")
    return list(py_dict.keys())

def process_class(obj):
    """
    Accepts a Python class instance and returns its class name.
    """
    return obj.__class__.__name__