
cmake_minimum_required(VERSION 3.27)

project(astr VERSION 1.0.0 LANGUAGES CXX)

if(PROJECT_IS_TOP_LEVEL)
    # make git ignore the build directory
    file(WRITE ${CMAKE_BINARY_DIR}/.gitignore "*")
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_EXTENSIONS OFF)
    SET(CMAKE_COMPILE_WARNING_AS_ERROR ON) # turn off with --compile-no-warning-as-error
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
    include(setup_compiler)
    include(default_flags)

    enable_testing()
    include(testing)
    add_subdirectory(tests)

    option(ASTR_ADD_INSTALL "Add install target" ON)

    add_custom_target(
        clang-tidy
        COMMAND clang-tidy -p=${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}/include/**/*.hpp ${CMAKE_SOURCE_DIR}/tests/**/*.?pp --extra-arg=-std=c++${CMAKE_CXX_STANDARD}
    )

else()
    option(ASTR_ADD_INSTALL "Add install target" OFF)
endif()


add_library(astr INTERFACE)

target_sources(astr INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/a4z/astr.hpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/a4z/filename.hpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/a4z/typename.hpp>
)

target_include_directories(astr INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
add_library(a4z::astr ALIAS astr)



if (ASTR_ADD_INSTALL)

# include gnudirs and add installation of the header file of the astr library
    include(GNUInstallDirs)
    install(TARGETS astr EXPORT astrTargets)
    install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    install(EXPORT astrTargets
        FILE astrTargets.cmake
        NAMESPACE a4z::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/a4z
    )
    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/astrConfigVersion.cmake
        VERSION 1.0.0
        COMPATIBILITY AnyNewerVersion
    )
    configure_package_config_file(
        ${CMAKE_CURRENT_LIST_DIR}/cmake/astrConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/astrConfig.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/a4z
    )
    install(
        FILES
            ${CMAKE_CURRENT_BINARY_DIR}/astrConfig.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/astrConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/a4z
    )

endif()

