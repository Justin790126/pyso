# distutils: language = c

from cpython.ref cimport PyObject
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