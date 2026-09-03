from setuptools import find_packages
from setuptools import setup

setup(
    name='robot_communication',
    version='0.0.0',
    packages=find_packages(
        include=('robot_communication', 'robot_communication.*')),
)
