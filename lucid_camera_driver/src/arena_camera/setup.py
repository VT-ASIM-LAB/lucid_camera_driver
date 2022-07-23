#!/usr/bin/env python

# NEEDED IF "catkin_python_setup" IS USED IN CMakeLists.txt

from distutils.core import setup
from catkin_pkg.python_setup import generate_distutils_setup

d = generate_distutils_setup(
    # #  don't do this unless you want a globally visible script
    # packages=[],
    # package_dir={}
)
maps = d
setup(**maps)