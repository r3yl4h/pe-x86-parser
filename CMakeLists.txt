cmake_minimum_required(VERSION 3.8)
project(pe-x86-parser)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories("C:/Program Files/Microsoft Visual Studio/2022/DIA SDK/include")

add_executable(pe-x86-parser
    "src/main.cpp"
    "src/parser.cpp"
    "src/exp.hpp"
    "src/x32/headpe.cpp"
    "src/x64/headpe.cpp"
    "src/section.cpp"
    "src/symbols.cpp"
    "src/iat.cpp"
    "src/edt.cpp"
        src/reloc.cpp
        src/arg.cpp
        src/except.cpp
        src/help.cpp
)

target_link_libraries(pe-x86-parser PRIVATE dbghelp)

