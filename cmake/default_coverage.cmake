
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

endif(COVERAGE)

add_library(default::coverage ALIAS _DefaultCoverage)