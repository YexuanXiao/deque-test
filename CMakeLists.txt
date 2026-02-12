cmake_minimum_required(VERSION 3.10)

project(deque)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/utf-8)
    add_compile_options(/WX)
else()
    add_compile_options(-Werror)
endif()

include_directories(deque)
include_directories(support)
add_compile_definitions(TEST_STD_VER=23)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_link_options(/NATVIS:${CMAKE_CURRENT_SOURCE_DIR}/deque/natvis.natvis)
endif()

function(number_to_padded_string NUM TARGET_LENGTH OUTPUT_VAR)
    string(REPEAT "0" ${TARGET_LENGTH} LEADING_ZEROS)
    string(LENGTH "${NUM}" CURRENT_LENGTH)
    math(EXPR PAD_LENGTH "${TARGET_LENGTH} - ${CURRENT_LENGTH}")
    if(PAD_LENGTH GREATER 0)
        string(SUBSTRING "${LEADING_ZEROS}" 0 ${PAD_LENGTH} PADDING)
        set(${OUTPUT_VAR} "${PADDING}${NUM}" PARENT_SCOPE)
    else()
        set(${OUTPUT_VAR} "${NUM}" PARENT_SCOPE)
    endif()
endfunction()

file(GLOB_RECURSE cpp_sources CONFIGURE_DEPENDS std/containers/sequences/deque/*.cpp)
set(counter 0)
foreach(source_file IN LISTS cpp_sources)
    get_filename_component(target_ext ${source_file} EXT)
    get_filename_component(file_name ${source_file} NAME)
    get_filename_component(target_name_wle ${source_file} NAME_WLE)
    file(RELATIVE_PATH target_directory ${CMAKE_CURRENT_SOURCE_DIR}/std/containers/sequences/deque ${source_file})
    string(REPLACE "/" "_" converted_path ${target_directory})
    string(REPLACE "deque." "" converted_path1 ${converted_path})
    string(REPLACE ".pass.cpp" "" converted_path2 ${converted_path1})
    number_to_padded_string(${counter} 2 counter_pad)
    set(target_name "${counter_pad}.${converted_path2}")
    if(target_ext STREQUAL ".pass.cpp")
        add_executable(${target_name} ${source_file})
        add_test(NAME ${target_name} COMMAND ${target_name})
    elseif(NOT target_ext STREQUAL ".verify.cpp")
        add_library(${target_name} STATIC ${source_file})
    endif()
    math(EXPR counter "${counter} + 1")
endforeach()

include(CheckCXXSourceCompiles)

set(CPP_STDLIB "unknown")

check_cxx_source_compiles("
#include <cstddef>
#ifdef __GLIBCXX__
int main() { return 0; }
#else
#error Not libstdc++
#endif
" USING_LIBSTDCXX)

if(USING_LIBSTDCXX)
    set(STDLIB "libstdc++")
endif()

check_cxx_source_compiles("
#include <cstddef>
#ifdef _LIBCPP_VERSION
int main() { return 0; }
#else
#error Not libc++
#endif
" USING_LIBCXX)

if(USING_LIBCXX)
    set(STDLIB "libc++")
endif()

check_cxx_source_compiles("
#include <cstddef>
#ifdef _MSVC_STL_UPDATE
int main() { return 0; }
#else
#error Not MSVC STL
#endif
" USING_MSVC_STL)

if(USING_MSVC_STL)
    set(STDLIB "STL")
endif()

if (NOT STDLIB STREQUAL "libc++")
    add_subdirectory(deque)
endif()
