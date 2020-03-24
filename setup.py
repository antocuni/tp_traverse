from setuptools import setup, Extension

setup(
    name="tp_traverse",
    ext_modules = [Extension('tp_traverse', ['tp_traverse.c'])],
)
