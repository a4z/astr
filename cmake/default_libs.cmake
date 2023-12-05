include_guard(GLOBAL)

find_package (Threads)

add_library(_DefaultLibs INTERFACE)

target_link_libraries(_DefaultLibs
    INTERFACE Threads::Threads
)

add_library(default::libs ALIAS _DefaultLibs)
