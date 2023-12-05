include_guard(GLOBAL)

# enable ccache only if it is there
find_program(CCACHE_BIN ccache)
if(CCACHE_BIN)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_BIN})
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_BIN})
  message("ccache binary foud, ccache enabled")
endif()

get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(NOT isMultiConfig)
  message("No multiconfig project")
  if(NOT CMAKE_BUILD_TYPE)
    message("No build type, fix it for you")
    SET(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
        FORCE )
  endif(NOT CMAKE_BUILD_TYPE)
else(NOT isMultiConfig)
  message("** Multi config project")
endif(NOT isMultiConfig)

# Off, we do not want to annoy potential packager
# option(WARN_ERROR "Thread warnings as errors. Default OFF" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_COMPILE_WARNING_AS_ERROR ON) # turn off with --compile-no-warning-as-error

if(APPLE AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # https://stackoverflow.com/questions/77153800/xcode-15-c-compilation-errors
  # TODO ...
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-ld_classic")
endif()



