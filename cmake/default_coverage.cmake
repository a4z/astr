include_guard(GLOBAL)

option(COVERAGE "Enable coverage reporting" OFF)

add_library(_DefaultCoverage INTERFACE)

if (COVERAGE)

    message("Enable code coverage")

    target_compile_options(_DefaultCoverage
        INTERFACE
        $<$<CXX_COMPILER_ID:GNU>: --coverage>

        $<$<CXX_COMPILER_ID:AppleClang>: --coverage>
    )

    target_link_options(_DefaultCoverage
        INTERFACE
        $<$<CXX_COMPILER_ID:GNU>: --coverage>

        $<$<CXX_COMPILER_ID:AppleClang>: --coverage>
    )

    set(COVERAGE_BRANCHES "--rc branch_coverage=1")
    set(COVERAGE_WARNINGS "--ignore-errors gcov")
    set(GENHTML_WARNINGS "")
    if(APPLE)
        set(COVERAGE_WARNINGS "--ignore-errors gcov --ignore-errors inconsistent --ignore-errors unused --ignore-errors range --ignore-errors empty,empty")
        set(GENHTML_WARNINGS "--ignore-errors inconsistent")
    endif()
    separate_arguments(COVERAGE_BRANCHES)
    separate_arguments(COVERAGE_WARNINGS)
    separate_arguments(GENHTML_WARNINGS)
    add_custom_target(coverage
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/coverage
        COMMAND lcov  --directory . --capture --output-file ${CMAKE_BINARY_DIR}/coverage/coverage.info ${COVERAGE_WARNINGS} ${COVERAGE_BRANCHES}
        COMMAND lcov --remove ${CMAKE_BINARY_DIR}/coverage/coverage.info '/usr/*' '*/tests/*' '*/_deps/*' '${CMAKE_SOURCE_DIR}/external/*' --output-file ${CMAKE_BINARY_DIR}/coverage/coverage.info.cleaned ${COVERAGE_WARNINGS} ${COVERAGE_BRANCHES}
        COMMAND genhtml --branch-coverage ${CMAKE_BINARY_DIR}/coverage/coverage.info.cleaned --output-directory ${CMAKE_BINARY_DIR}/coverage ${GENHTML_WARNINGS} ${COVERAGE_BRANCHES}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif(COVERAGE)

add_library(default::coverage ALIAS _DefaultCoverage)
