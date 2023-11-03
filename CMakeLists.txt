cmake_minimum_required(VERSION 3.21)

project(mciexample VERSION 1.0.0 LANGUAGES CXX)

add_executable(mci main.cpp)

set_target_properties(mci PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_link_libraries(mci Winmm.lib)

target_compile_features(mci PUBLIC cxx_std_17)

target_compile_options(mci PUBLIC /utf-8)

install(TARGETS mci DESTINATION ${CMAKE_CURRENT_LIST_DIR}/install)
