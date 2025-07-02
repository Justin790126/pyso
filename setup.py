from setuptools import setup
from Cython.Build import cythonize

setup(
    name="libtest",
    ext_modules=cythonize("libtest.pyx"),
    zip_safe=False,
)