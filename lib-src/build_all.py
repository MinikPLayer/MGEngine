import os
import shutil

class Configuration:
    def __init__(self, name, generator, c_compiler = None, cpp_compiler = None):
        self.name = name
        self.generator = generator
        self.c_compiler = c_compiler
        self.cpp_compiler = cpp_compiler

CONFIGURATIONS = [
    Configuration('LLVM', generator='Ninja', c_compiler='clang', cpp_compiler='clang++'),
]
LIBRARIES = ['glm', 'assimp', 'zlib', 'glfw']

BASE_DIR = os.path.dirname(__file__)
INSTALL_PREFIX_BASE = os.path.join(BASE_DIR, '../lib')



if os.path.exists(INSTALL_PREFIX_BASE):
    shutil.rmtree(INSTALL_PREFIX_BASE)

# Find all directories in the current working directory
for d in LIBRARIES:
    for config in CONFIGURATIONS:
        build_dir_path = os.path.join(BASE_DIR, d, 'build_' + config.name.lower())
        install_dir_path = os.path.join(INSTALL_PREFIX_BASE, config.name.lower())
        if os.path.exists(build_dir_path):
            shutil.rmtree(build_dir_path)

        os.makedirs(build_dir_path)

        # Run cmake
        os.chdir(build_dir_path)
        cmake_command = f'cmake -G "{config.generator}" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX={install_dir_path}'
        if config.c_compiler:
            cmake_command += f' "-DCMAKE_C_COMPILER={config.c_compiler}"'
        if config.cpp_compiler:
            cmake_command += f' "-DCMAKE_CXX_COMPILER={config.cpp_compiler}"'

        ret = os.system(cmake_command + f' ..')
        if ret != 0:
            raise RuntimeError(f'CMake configuration failed for {d} with {config}')
        
        # Build and install
        ret = os.system(f'cmake --build . --config Release --target install')
        if ret != 0:
            raise RuntimeError(f'Build or installation failed for {d} with {config}')