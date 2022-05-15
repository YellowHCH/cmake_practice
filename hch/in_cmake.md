# cmake note  
[cmake-examples](https://github.com/ttroy50/cmake-examples)
## command
### `cmake_minimum_required(VERSION 3.5)`
To specify the required min cmake version.
### `project (project_name)`
A CMake build can include a project name to make referencing certain variables easier when using multiple projects.  
We can get <project_name> from **${PROJECT_NAME}** variable once project() cmd had been called.
### `add_executable(exec_name SRC_LIST)`
An executable <exec_name> should build from source files as <SRC_LIST>.
### `set()`
[cmake set cmd usage](https://cmake.org/cmake/help/latest/command/set.html)  
e.g. `set(SOURCES
    src/Hello.cpp
    src/main.cpp
)`
### `target_include_directories()` && `include_directories`
`target_include_directories(target
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)`  
key word **PRIVATE\INTERFACE\PUBLIC** [Ref](https://zhuanlan.zhihu.com/p/82244559)  
PRIVATE - the directory is added to this target’s include directorie  
INTERFACE - the directory is added to the include directories for any targets that link this library.  
PUBLIC - As above, it is included in this library and also any targets that link this library.
### `make VERBOSE=1`
To show the make debug info
### `add_library()`
`add_library(hello_library STATIC
    src/Hello.cpp
)`
### `target_link_libraries()`
`target_link_libraries( hello_binary
    PRIVATE
        hello_library
)`
This tells CMake to link the hello_library against the hello_binary executable during link time.  
It will also propagate any include directories with PUBLIC or INTERFACE scope from the linked library target.
### 'add_library()'
`add_library(hello_library SHARED
    src/Hello.cpp
)`
`add_library(hello::library ALIAS hello_library)` set alias for lib
### `install()`
`install (TARGETS cmake_examples_inst_bin
    DESTINATION bin)`
DCMAKE_INSTALL_PREFIX=path_to_install_prefix
We could specify the default install prefix dir in CMakeList.txt. 
## variables
### CMAKE_SOURCE_DIR
The root source dir. Which contain the **top level** CMkaeList.txt file.
### CMAKE_CURRENT_SOURCE_DIR
The current source directory if using sub-projects and directories.
### PROJECT_SOURCE_DIR
The source directory of the current cmake project. Which contain the **most recent project()** cmd. 
### CMAKE_BINARY_DIR
Ref to **CMAKE_SOURCE_DIR**, in build dir.
### CMAKE_CURRENT_BINARY_DIR
Ref to **CMAKE_CURRENT_SOURCE_DIR**, in build dir.
### PROJECT_BINARY_DIR
Ref to **PROJECT_SOURCE_DIR**, in build dir.
### CMAKE_BUILD_TYPE
set debug or release or others type. `set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)`
### CMAKE_CXX_FLAGS
set default C++ flag
`set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)`
## Tips
### In-Place Build or Out-of-Source Build
#### In-Place Build
cmake build in source code, generate all the temporary the same dir as thn source code. Just run `cmake .` in the root source dir.
#### Out-of-Source Build
`cmake -B<path_to_build_files>` or `cmake <path_to_root_dir>` at build files dir
