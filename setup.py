#!/usr/bin/env python3
#
# ppack setup
#
# date: Mar 1 2021
# Maintainer: glozanoa <glozanoa@uni.pe>


from setuptools import setup, find_packages

VERSION = "v0.0.1"

f = open('README.md', 'r')
LONG_DESCRIPTION = f.read()
f.close()


setup(
    name='ppack_ama',
    version=VERSION,
    description='Parallel Password Analysis and Cracking Kit',
    long_description=LONG_DESCRIPTION,
    long_description_content_type='text/markdown',
    author='glozanoa',
    author_email='glozanoa@uni.pe',
    url='https://github.com/fpolit/ppack',
    license='GPL3',
    packages=find_packages(),
    include_package_data=True,
    package_data = {
        'ppack': ['src/*.cpp',
                  'include/*.hpp',
                  'CMakeLists.txt'],
    },
)
