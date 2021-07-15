cmake_minimum_required(VERSION 3.9...3.20)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(JConverter-shell
    VERSION 1.0.0
    DESCRIPTION "Converts between different units"
    LANGUAGES CXX)

add_executable(JConverter-shell jconverter-shell.cpp convertfromstrings.cpp)

target_compile_features(JConverter-shell PUBLIC cxx_std_17)
set_target_properties(JConverter-shell PROPERTIES CXX_EXTENSIONS OFF)

target_compile_options(JConverter-shell PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded>
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic -Wno-padded>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

if(Qt5_FOUND)
    project(JConverter
        VERSION 0.0.1
        DESCRIPTION "Converts between different units"
        LANGUAGES CXX)

    add_executable(JConverter jconverter-gui.cpp convertfromstrings.cpp)
    target_compile_features(JConverter PUBLIC cxx_std_17)
    set_target_properties(JConverter PROPERTIES
        CXX_EXTENSIONS OFF
        POSITION_INDEPENDENT_CODE ON)
    target_compile_options(JConverter PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic>
        $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->)
    target_link_libraries(JConverter Qt5::Widgets)
    install(TARGETS JConverter RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
endif()

install(TARGETS JConverter-shell RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
