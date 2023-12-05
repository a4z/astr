include_guard(GLOBAL)


add_library(_DefaultWarnings INTERFACE)
target_compile_options(_DefaultWarnings
  INTERFACE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:AppleClang>>:
      -Wall -Wextra -pedantic
      -Wdeprecated
      -Wformat-security
      -Wimplicit-fallthrough
      -Wmissing-braces
      -Wmissing-field-initializers
      -Wnon-virtual-dtor
      -Wnull-dereference
      -Wold-style-cast
#      -Wpadded # want that only for protocols where memcp on stucts in used
      -Wparentheses
      -Wpointer-arith
      -Wredundant-decls
      -Wreturn-type
      -Wsequence-point
      -Wshadow
      -Wswitch
      -Wuninitialized
      -Wunused-function
      -Wunused-variable
      -Wunused-variable
      -Wconversion
      -Wsign-conversion
      -Wsign-promo
      -Wfloat-conversion
      -pthread
      >

    $<$<CXX_COMPILER_ID:Clang>: -ferror-limit=3>

    $<$<CXX_COMPILER_ID:GNU>: -Wduplicated-branches
                              -Wduplicated-cond
                              -Wlogical-op
                              -Wcast-align
                              # -Wno-missing-field-initializers
                              >

    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

# since cmake 3.24 we use COMPILE_WARNING_AS_ERROR
# option(WARN_ERROR "Thread warnings as errors" OFF)

# if(WARN_ERROR)
#   target_compile_options(_DefaultWarnings
#     INTERFACE
#       $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:AppleClang>>:-Werror>
#       $<$<CXX_COMPILER_ID:MSVC>:/WX>
#   )
# endif(WARN_ERROR)

add_library(default::warnings ALIAS _DefaultWarnings)
