from setuptools import find_packages, setup
import os
from glob import glob

package_name = 'cartographer_bringup'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob(os.path.join('launch', '*.*'))),
        (os.path.join('share', package_name, 'params'), glob(os.path.join('params', '*.*'))),
        (os.path.join('share', package_name, 'maps'), glob(os.path.join('maps', '*.*'))),
        (os.path.join('share', package_name, 'rviz'), glob(os.path.join('rviz', '*.rviz*'))),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='yahboom',
    maintainer_email='yahboom@todo.todo',
    description='Cartographer bringup package for mapping and localization',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            # 已删除所有无关节点，如果你以后添加新的 Python 节点，在这里添加
        ],
    },
)