include_guard(GLOBAL)

include(default_warnings)
include(default_libs)
include(default_coverage)

add_library(_DefaultFlags INTERFACE)

target_link_libraries(_DefaultFlags
    INTERFACE default::libs default::warnings default::coverage
)

# TODO , this Windows part is of course totally untested
# and it does not work if the dependencies are not adjusted accordently,
# todo , if this is wanted, a custom tripplet is needed
# target_compile_options(_DefaultFlags
#   INTERFACE
#     $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>: /MTd>
#     $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>: /MT>
# )
add_library(default::flags ALIAS _DefaultFlags)


