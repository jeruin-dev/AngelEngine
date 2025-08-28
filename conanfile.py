from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout

class Pkg(ConanFile):
    name = "myapp"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    requires = ["fmt/11.2.0"]  # ejemplo


    def layout(self):
        cmake_layout(self)


    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()
